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

    // Capture settings
    FIntPoint LocalSize = CurrentSettings->Size;
    float LocalScale = CurrentSettings->Scale;
    float LocalZMult = CurrentSettings->ZMultiplier;
    float LocalNoiseScale = CurrentSettings->NoiseScale;
    float LocalUVScale = CurrentSettings->UVScale;
    UMaterialInterface* LocalMaterial = CurrentSettings->ChunkMaterial;

    TWeakObjectPtr<UChunkManager> WeakThis(this);

    AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [WeakThis, Coord, LocalSize, LocalScale, LocalZMult, LocalNoiseScale, LocalUVScale, LocalMaterial]()
        {
            FChunkMeshData GeneratedData;

            if (WeakThis.IsValid())
            {
                WeakThis->GenerateMeshDataAsync(Coord, GeneratedData, LocalSize, LocalScale, LocalZMult, LocalNoiseScale, LocalUVScale);

                // CRITICAL FOR AUTO-MATERIAL: 
                // CalculateTangentsForMesh handles the Normals and Tangents required for slope-blending.
                UKismetProceduralMeshLibrary::CalculateTangentsForMesh(
                    GeneratedData.Vertices,
                    GeneratedData.Triangles,
                    GeneratedData.UV0,
                    GeneratedData.Normals,
                    GeneratedData.Tangents
                );
            }

            AsyncTask(ENamedThreads::GameThread, [WeakThis, Coord, GeneratedData, LocalSize, LocalScale, LocalMaterial]()
                {
                    if (!WeakThis.IsValid() || !WeakThis->GetWorld()) return;

                    FVector SpawnLocation = FVector(
                        static_cast<float>(Coord.X * LocalSize.X) * LocalScale,
                        static_cast<float>(Coord.Y * LocalSize.Y) * LocalScale,
                        0
                    );

                    FActorSpawnParameters Params;
                    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                    AChunk* NewChunk = WeakThis->GetWorld()->SpawnActor<AChunk>(AChunk::StaticClass(), SpawnLocation, FRotator::ZeroRotator, Params);

                    if (NewChunk)
                    {
                        WeakThis->ActiveChunks.Add(Coord, NewChunk);

                        // Ensure your AChunk::RenderChunk function calls 
                        // CreateMeshSection with 'bCreateCollision' and 'bSRGB' correctly.
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
    OutData.Normals.Empty(); // Ensure this is empty for CalculateTangents to fill
    OutData.Tangents.Empty();
    OutData.Instances.Empty();

    FRandomStream RS(Coord.X * 1000 + Coord.Y);

    for (int32 y = 0; y <= Size.Y; y++)
    {
        for (int32 x = 0; x <= Size.X; x++)
        {
            float GlobalX = (static_cast<float>(Coord.X * Size.X) + x) * NoiseScale;
            float GlobalY = (static_cast<float>(Coord.Y * Size.Y) + y) * NoiseScale;

            float RawNoise = GetFractalNoise(GlobalX, GlobalY, 8, 0.5f, 2.0f);
            float NormalizedNoise = (RawNoise + 1.0f) * 0.5f;

            // Masking Mountains
            float LowFreq = (FMath::PerlinNoise2D(FVector2D(GlobalX * 0.2f, GlobalY * 0.2f)) + 1.0f) * 0.5f;
            float MountainShape = FMath::Pow(NormalizedNoise, 4.0f);
            float FinalHeight = FMath::Lerp(MountainShape * 0.05f, MountainShape, LowFreq);

            float Z = FinalHeight * ZMult;
            OutData.Vertices.Add(FVector(x * Scale, y * Scale, Z));

            // UVs need to be World-Space for the material to tile across chunks
            float U = (static_cast<float>(Coord.X * Size.X) + x) * UVScale;
            float V = (static_cast<float>(Coord.Y * Size.Y) + y) * UVScale;
            OutData.UV0.Add(FVector2D(U, V));

            // Instances (Trees/Rocks)
            if (FinalHeight < 0.12f && RS.FRandRange(0.f, 1.f) > 0.985f)
            {
                FInstanceData NewAsset;
                NewAsset.TypeIndex = 0;
                NewAsset.Transform = FTransform(FRotator(0, RS.FRandRange(0, 360), 0), FVector(x * Scale, y * Scale, Z), FVector(RS.FRandRange(0.8f, 1.4f)));
                OutData.Instances.Add(NewAsset);
            }
        }
    }

    // Grid Triangulation
    for (int32 y = 0; y < Size.Y; y++)
    {
        for (int32 x = 0; x < Size.X; x++)
        {
            int32 BottomLeft = x + (y * (Size.X + 1));
            int32 BottomRight = BottomLeft + 1;
            int32 TopLeft = x + ((y + 1) * (Size.X + 1));
            int32 TopRight = TopLeft + 1;

            // Using consistent winding order for better normal calculation
            OutData.Triangles.Add(BottomLeft);
            OutData.Triangles.Add(TopLeft);
            OutData.Triangles.Add(BottomRight);

            OutData.Triangles.Add(BottomRight);
            OutData.Triangles.Add(TopLeft);
            OutData.Triangles.Add(TopRight);
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