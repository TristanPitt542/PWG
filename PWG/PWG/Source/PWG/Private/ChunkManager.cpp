#include "ChunkManager.h"
#include "Chunk.h"
#include "ChunkSettings.h"
#include "ChunkMeshData.h"
#include "ProceduralMeshComponent.h"
#include "PCGComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Engine/World.h"
#include "Async/Async.h"
#include "GameFramework/PlayerController.h" // For PlacePlayerOnGround

void UChunkManager::Initialize(FSubsystemCollectionBase& Collection)
{ 
    Super::Initialize(Collection);
}

void UChunkManager::Deinitialize()
{
    ActiveChunks.Empty();
    Super::Deinitialize();
}

void UChunkManager::OnWorldBeginPlay(UWorld& InWorld)
{
    // Note: Do NOT call Super::BeginPlay() here, 
    // Super::OnWorldBeginPlay(InWorld) is fine but often unnecessary for subsystems.

    if (!CurrentSettings) return;

    TSubclassOf<AChunk> LocalChunkClass = CurrentSettings->ChunkClass;
    if (!LocalChunkClass) return;

    int32 SideLength = (CurrentSettings->RenderDistance * 2) + 1;
    int32 TotalExpectedChunks = SideLength * SideLength;

    ChunkPool.Reserve(TotalExpectedChunks);

    for (int32 i = 0; i < TotalExpectedChunks; i++)
    {
        FActorSpawnParameters Params;
        // Use InWorld instead of GetWorld() for clarity in the subsystem
        AChunk* NewChunk = InWorld.SpawnActor<AChunk>(LocalChunkClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);

        if (NewChunk)
        {
            NewChunk->SetActorHiddenInGame(true);
            NewChunk->SetActorEnableCollision(false);
            ChunkPool.Add(NewChunk);
        }
    }
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
        if (AChunk* ChunkToRecycle = ActiveChunks[Coord])
        {
            // Add this line to clear trees/rocks immediately
            ChunkToRecycle->GetPCGComponent()->Cleanup();

            ChunkToRecycle->SetActorHiddenInGame(true);
            ChunkToRecycle->SetActorEnableCollision(false);
            ChunkToRecycle->SetActorTickEnabled(false);
            ChunkToRecycle->GetProceduralMesh()->ClearAllMeshSections();

            ChunkPool.Add(ChunkToRecycle);
        }
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

    TSubclassOf<AChunk> LocalChunkClass = CurrentSettings->ChunkClass;

    TWeakObjectPtr<UChunkManager> WeakThis(this);

    // FIRST LAMBDA: Added LocalChunkClass to the capture list
    AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [WeakThis, Coord, LocalSize, LocalScale, LocalZMult, LocalNoiseScale, LocalUVScale, LocalMaterial, LocalChunkClass]()
        {
            FChunkMeshData GeneratedData;

            if (WeakThis.IsValid())
            {
                WeakThis->GenerateMeshDataAsync(Coord, GeneratedData, LocalSize, LocalScale, LocalZMult, LocalNoiseScale, LocalUVScale);

            }

            AsyncTask(ENamedThreads::GameThread, [WeakThis, Coord, GeneratedData, LocalSize, LocalScale, LocalMaterial, LocalChunkClass]()
                {
                    if (!WeakThis.IsValid() || !WeakThis->GetWorld() || !LocalChunkClass) return;

                    AChunk* NewChunk = nullptr;

                    // Pooling Logic
                    if (WeakThis->ChunkPool.Num() > 0)
                    {
                        NewChunk = WeakThis->ChunkPool.Pop();
                        NewChunk->SetActorHiddenInGame(false);
                        NewChunk->SetActorEnableCollision(true);
                        NewChunk->SetActorTickEnabled(true);
                        NewChunk->SetActorLocation(FVector::ZeroVector);
                    }
                    else
                    {
                        FActorSpawnParameters Params;
                        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                        NewChunk = WeakThis->GetWorld()->SpawnActor<AChunk>(LocalChunkClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
                    }

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
    // CLEAR BUFFERS
    OutData.Clear();

    // HEIGHTMAP SAMPLING (Skirt)
    TArray<float> HeightMap;
    int32 SampleSizeX = Size.X + 3;
    int32 SampleSizeY = Size.Y + 3;
    HeightMap.SetNumUninitialized(SampleSizeX * SampleSizeY);

    // Precise world-space anchor for this chunk in "noise units"
    double WorldAnchorX = (double)Coord.X * (double)Size.X;
    double WorldAnchorY = (double)Coord.Y * (double)Size.Y;

    for (int32 y = -1; y <= Size.Y + 1; y++)
    {
        for (int32 x = -1; x <= Size.X + 1; x++)
        {
            double SampleX = (WorldAnchorX + (double)x) * (double)NoiseScale;
            double SampleY = (WorldAnchorY + (double)y) * (double)NoiseScale;

            float RawNoise = GetFractalNoise((float)SampleX, (float)SampleY, 8, 0.5f, 2.0f);
            float NormalizedNoise = (RawNoise + 1.0f) * 0.5f;
            float FinalHeight = FMath::Pow(NormalizedNoise, 4.0f) * ZMult;

            int32 Index = (x + 1) + (y + 1) * SampleSizeX;
            HeightMap[Index] = FinalHeight;
        }
    }

    // GENERATE MESH DATA
    for (int32 y = 0; y <= Size.Y; y++)
    {
        for (int32 x = 0; x <= Size.X; x++)
        {
            int32 HMIndex = (x + 1) + (y + 1) * SampleSizeX;

            // Vertex Position: Using absolute world coordinates ensures alignment
            float VertX = (float)(WorldAnchorX + (double)x) * Scale;
            float VertY = (float)(WorldAnchorY + (double)y) * Scale;
            OutData.Vertices.Add(FVector(VertX, VertY, HeightMap[HMIndex]));

            // UVs: Use Global coordinates to prevent texture wrapping seams
            float GlobalUVX = (float)(WorldAnchorX + (double)x) * UVScale;
            float GlobalUVY = (float)(WorldAnchorY + (double)y) * UVScale;
            OutData.UV0.Add(FVector2D(GlobalUVX, GlobalUVY));

            // 4. SEAMLESS NORMALS
            // We sample the heightmap at [x-1, x+1, y-1, y+1]
            // Because we sampled a skirt, these lookups are always valid even at the edges.
            float H_L = HeightMap[HMIndex - 1];
            float H_R = HeightMap[HMIndex + 1];
            float H_D = HeightMap[HMIndex - SampleSizeX];
            float H_U = HeightMap[HMIndex + SampleSizeX];

            // Crucial: The "2.0f * Scale" matches the distance between H_L and H_R
            FVector SlopeX(2.0f * Scale, 0.0f, H_R - H_L);
            FVector SlopeY(0.0f, 2.0f * Scale, H_U - H_D);
            
            FVector Normal = FVector::CrossProduct(SlopeX, SlopeY).GetSafeNormal();
            OutData.Normals.Add(Normal);

            FVector TangentX = SlopeX.GetSafeNormal();
            OutData.Tangents.Add(FProcMeshTangent(TangentX, false));
        }
    }

    // TRIANGULATION
    for (int32 y = 0; y < Size.Y; y++)
    {
        for (int32 x = 0; x < Size.X; x++)
        {
            int32 i = x + (y * (Size.X + 1));

            bool bAlternate = (Coord.X * Size.X + x + Coord.Y * Size.Y + y) % 2 == 0;

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

float UChunkManager::GetPerlinNoise(float X, float Y, float Scale)
{
    return FMath::PerlinNoise2D(FVector2D(X * Scale, Y * Scale));
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