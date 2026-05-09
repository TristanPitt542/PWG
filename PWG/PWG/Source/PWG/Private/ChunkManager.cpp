#include "ChunkManager.h"
#include "Chunk.h"
#include "ChunkSettings.h"
#include "KismetProceduralMeshLibrary.h"
#include "Engine/World.h"
#include "Async/Async.h"

void UChunkManager::Initialize(FSubsystemCollectionBase& Collection) { Super::Initialize(Collection); }

void UChunkManager::Deinitialize()
{
    ActiveChunks.Empty();
    Super::Deinitialize();
}

void UChunkManager::Tick(float DeltaTime)
{
    if (SpawnQueue.Num() > 0)
    {
        FIntPoint NextCoord = SpawnQueue[0];
        SpawnQueue.RemoveAt(0);
        if (!ActiveChunks.Contains(NextCoord) && !LoadingChunks.Contains(NextCoord))
        {
            SpawnChunk(NextCoord);
        }
    }

    TickTimer += DeltaTime;
    if (TickTimer >= 0.5f)
    {
        UpdateChunks();
        TickTimer = 0.0f;
    }
}

void UChunkManager::LoadTerrainSettings(UChunkSettings* NewSettings)
{
    if (!NewSettings) return;
    CurrentSettings = NewSettings;
    UpdateChunks();
}

void UChunkManager::UpdateChunks()
{
    if (!CurrentSettings || !GetWorld()) return;

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC || !PC->GetPawn()) return;

    FVector PlayerLocation = PC->GetPawn()->GetActorLocation();
    float ChunkWidth = CurrentSettings->Size.X * CurrentSettings->Scale;
    float ChunkHeight = CurrentSettings->Size.Y * CurrentSettings->Scale;

    int32 CurrentX = FMath::FloorToInt(PlayerLocation.X / ChunkWidth);
    int32 CurrentY = FMath::FloorToInt(PlayerLocation.Y / ChunkHeight);
    FIntPoint CurrentChunkCoord(CurrentX, CurrentY);

    if (CurrentChunkCoord == LastPlayerChunkCoord) return;
    LastPlayerChunkCoord = CurrentChunkCoord;

    int32 Radius = CurrentSettings->RenderDistance;
    for (int32 x = -Radius; x <= Radius; x++)
    {
        for (int32 y = -Radius; y <= Radius; y++)
        {
            FIntPoint TargetCoord = CurrentChunkCoord + FIntPoint(x, y);
            if (!ActiveChunks.Contains(TargetCoord) && !LoadingChunks.Contains(TargetCoord))
            {
                SpawnQueue.AddUnique(TargetCoord);
            }
        }
    }

    TArray<FIntPoint> OutOfRangeCoords;
    for (auto& Elem : ActiveChunks)
    {
        if (FMath::Abs(Elem.Key.X - CurrentChunkCoord.X) > Radius + 1 ||
            FMath::Abs(Elem.Key.Y - CurrentChunkCoord.Y) > Radius + 1)
        {
            OutOfRangeCoords.Add(Elem.Key);
        }
    }

    for (FIntPoint Coord : OutOfRangeCoords)
    {
        if (AChunk* ChunkToDestroy = ActiveChunks[Coord]) ChunkToDestroy->Destroy();
        ActiveChunks.Remove(Coord);
    }
}

void UChunkManager::SpawnChunk(FIntPoint Coord)
{
    if (!CurrentSettings || !GetWorld() || ActiveChunks.Contains(Coord) || LoadingChunks.Contains(Coord)) return;

    LoadingChunks.Add(Coord);

    // Capture settings from the Data Asset
    FIntPoint LocalSize = CurrentSettings->Size;
    float LocalScale = CurrentSettings->Scale;
    float LocalZMult = CurrentSettings->ZMultiplier;
    float LocalNoiseScale = CurrentSettings->NoiseScale;
    float LocalUVScale = CurrentSettings->UVScale;
    UMaterialInterface* LocalMaterial = CurrentSettings->ChunkMaterial;

    // Ensure this is typed correctly
    TSubclassOf<AChunk> LocalChunkClass = CurrentSettings->ChunkClass;

    TWeakObjectPtr<UChunkManager> WeakThis(this);

    // FIRST LAMBDA: Added LocalChunkClass to the capture list
    AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [WeakThis, Coord, LocalSize, LocalScale, LocalZMult, LocalNoiseScale, LocalUVScale, LocalMaterial, LocalChunkClass]()
        {
            FChunkMeshData GeneratedData;

            if (WeakThis.IsValid())
            {
                WeakThis->GenerateMeshDataAsync(Coord, GeneratedData, LocalSize, LocalScale, LocalZMult, LocalNoiseScale, LocalUVScale);

                UKismetProceduralMeshLibrary::CalculateTangentsForMesh(
                    GeneratedData.Vertices,
                    GeneratedData.Triangles,
                    GeneratedData.UV0,
                    GeneratedData.Normals,
                    GeneratedData.Tangents
                );
            }

            // SECOND LAMBDA: Added LocalChunkClass to this capture list too!
            AsyncTask(ENamedThreads::GameThread, [WeakThis, Coord, GeneratedData, LocalSize, LocalScale, LocalMaterial, LocalChunkClass]()
                {
                    if (!WeakThis.IsValid() || !WeakThis->GetWorld() || !LocalChunkClass) return;

                    FVector SpawnLocation = FVector::ZeroVector;

                    FActorSpawnParameters Params;
                    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                    // Now LocalChunkClass is visible here
                    AChunk* NewChunk = WeakThis->GetWorld()->SpawnActor<AChunk>(LocalChunkClass, SpawnLocation, FRotator::ZeroRotator, Params);

                    if (NewChunk)
                    {
                        WeakThis->ActiveChunks.Add(Coord, NewChunk);
                        NewChunk->RenderChunk(GeneratedData, LocalMaterial);

                        if (Coord == FIntPoint(0, 0)) WeakThis->PlacePlayerOnGround();
                    }

                    WeakThis->LoadingChunks.Remove(Coord);
                });
        });
}

void UChunkManager::GenerateMeshDataAsync(FIntPoint Coord, FChunkMeshData& OutData, FIntPoint Size, float Scale, float ZMult, float NoiseScale, float UVScale)
{
    OutData.Vertices.Empty();
    OutData.Triangles.Empty();
    OutData.UV0.Empty();
    OutData.Normals.Empty();
    OutData.Tangents.Empty();
    OutData.Instances.Empty();

    // 1. Create a HeightMap buffer with a 1-pixel skirt (+1 on all sides)
    // SampleSize needs to accommodate: Size + 1 (for the end vertex) + 2 (for the skirt)
    TArray<float> HeightMap;
    int32 SampleSizeX = Size.X + 3;
    int32 SampleSizeY = Size.Y + 3;
    HeightMap.SetNumUninitialized(SampleSizeX * SampleSizeY);

    // 2. Fill the HeightMap (including the invisible skirt)
    for (int32 y = -1; y <= Size.Y + 1; y++)
    {
        for (int32 x = -1; x <= Size.X + 1; x++)
        {
            // Use doubles for world-coordinate math to prevent floating point jitter at distance
            double WorldX = ((double)Coord.X * (double)Size.X) + (double)x;
            double WorldY = ((double)Coord.Y * (double)Size.Y) + (double)y;

            float GlobalX = (float)WorldX * NoiseScale;
            float GlobalY = (float)WorldY * NoiseScale;

            // Use the exact same noise logic for every sample
            float RawNoise = GetFractalNoise(GlobalX, GlobalY, 8, 0.5f, 2.0f);
            float NormalizedNoise = (RawNoise + 1.0f) * 0.5f;
            float MountainShape = FMath::Pow(NormalizedNoise, 4.0f);
            float FinalHeight = MountainShape * ZMult;

            // Map the range [-1, Size+1] to [0, Size+2] for the array
            int32 Index = (x + 1) + (y + 1) * SampleSizeX;
            HeightMap[Index] = FinalHeight;
        }
    }

    // 3. Generate Visible Mesh Data
    for (int32 y = 0; y <= Size.Y; y++)
    {
        for (int32 x = 0; x <= Size.X; x++)
        {
            // Center sample index in the HeightMap
            int32 HMIndex = (x + 1) + (y + 1) * SampleSizeX;
            float Z = HeightMap[HMIndex];

            // Position: All chunks spawned at (0,0,0) world origin to avoid precision gaps
            float VertexX = (static_cast<float>(Coord.X * Size.X) + x) * Scale;
            float VertexY = (static_cast<float>(Coord.Y * Size.Y) + y) * Scale;
            OutData.Vertices.Add(FVector(VertexX, VertexY, Z));

            // UVs: Consistent world-space mapping
            OutData.UV0.Add(FVector2D(((float)Coord.X * Size.X + x) * UVScale, ((float)Coord.Y * Size.Y + y) * UVScale));

            // 4. SEAMLESS NORMALS: Using the skirt neighbors
            float H_L = HeightMap[HMIndex - 1];               // Left (x-1)
            float H_R = HeightMap[HMIndex + 1];               // Right (x+1)
            float H_D = HeightMap[HMIndex - SampleSizeX];     // Down (y-1)
            float H_U = HeightMap[HMIndex + SampleSizeX];     // Up (y+1)

            // Calculate slopes (Tangent and Bitangent)
            FVector SlopeX(2.0f * Scale, 0.0f, H_R - H_L);
            FVector SlopeY(0.0f, 2.0f * Scale, H_U - H_D);

            // The cross product ensures the normal is perfectly perpendicular to the slope
            FVector Normal = FVector::CrossProduct(SlopeY, SlopeX).GetSafeNormal();
            OutData.Normals.Add(Normal);

            // Standardize Tangent for the normal map to work correctly
            OutData.Tangents.Add(FProcMeshTangent(SlopeX.GetSafeNormal(), false));
        }
    }

    // 5. Grid Triangulation
    for (int32 y = 0; y < Size.Y; y++)
    {
        for (int32 x = 0; x < Size.X; x++)
        {
            int32 i = x + (y * (Size.X + 1));

            // Alternating diagonals helps break up the "grid" tiling look visually
            bool bAlternate = (x + y) % 2 == 0;
            if (bAlternate)
            {
                OutData.Triangles.Append({ i, i + Size.X + 1, i + Size.X + 2, i, i + Size.X + 2, i + 1 });
            }
            else
            {
                OutData.Triangles.Append({ i, i + Size.X + 1, i + 1, i + 1, i + Size.X + 1, i + Size.X + 2 });
            }
        }
    }
}

float UChunkManager::GetFractalNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity)
{
    float Total = 0.0f, Frequency = 1.0f, Amplitude = 1.0f, MaxValue = 0.0f;
    for (int i = 0; i < Octaves; i++)
    {
        Total += FMath::PerlinNoise2D(FVector2D(X * Frequency, Y * Frequency)) * Amplitude;
        MaxValue += Amplitude;
        Amplitude *= Persistence;
        Frequency *= Lacunarity;
    }
    return Total / MaxValue;
}

float UChunkManager::GetRigidNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity)
{
    float Total = 0.0f, Frequency = 1.0f, Amplitude = 1.0f, Weight = 1.0f;
    for (int i = 0; i < Octaves; i++)
    {
        float NoiseVal = 1.0f - FMath::Abs(FMath::PerlinNoise2D(FVector2D(X * Frequency, Y * Frequency)));
        NoiseVal *= Weight;
        Weight = FMath::Clamp(NoiseVal * Persistence, 0.0f, 1.0f);
        Total += NoiseVal * Amplitude;
        Amplitude *= Persistence;
        Frequency *= Lacunarity;
    }
    return Total;
}

void UChunkManager::PlacePlayerOnGround()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC || !PC->GetPawn()) return;

    FHitResult Hit;
    FVector Start(0, 0, 20000.f), End(0, 0, -20000.f);
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(PC->GetPawn());

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
    {
        PC->GetPawn()->SetActorLocation(Hit.ImpactPoint + FVector(0, 0, 150.f));
    }
}