#include "ChunkManager.h"
#include "Chunk.h"
#include "ChunkSettings.h"
#include "ChunkMeshData.h"
#include "ProceduralMeshComponent.h"
#include "PCGComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Engine/World.h"
#include "Async/Async.h"
#include "GameFramework/PlayerController.h"

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
    if (!CurrentSettings) return;

    TSubclassOf<AChunk> LocalChunkClass = CurrentSettings->ChunkClass;
    if (!LocalChunkClass) return;

    // Pre-allocate the actor pool based on the maximum viewport grid coverage
    // SideLength accounts for negative/positive render distance bounds + center
    int32 SideLength = (CurrentSettings->RenderDistance * 2) + 1;
    int32 TotalExpectedChunks = SideLength * SideLength;

    ChunkPool.Reserve(TotalExpectedChunks);

    for (int32 i = 0; i < TotalExpectedChunks; i++)
    {
        FActorSpawnParameters Params;
        AChunk* NewChunk = InWorld.SpawnActor<AChunk>(LocalChunkClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);

        if (NewChunk)
        {
            // Warm up the pool: hide and disable physics/collision until acquisition
            NewChunk->SetActorHiddenInGame(true);
            NewChunk->SetActorEnableCollision(false);
            ChunkPool.Add(NewChunk);
        }
    }
}

void UChunkManager::Tick(float DeltaTime)
{
    // Process one chunk spawn per frame to amortize cost and prevent game thread hitching
    if (SpawnQueue.Num() > 0)
    {
        FIntPoint NextCoord = SpawnQueue[0];
        SpawnQueue.RemoveAt(0);
        if (!ActiveChunks.Contains(NextCoord) && !LoadingChunks.Contains(NextCoord))
        {
            SpawnChunk(NextCoord);
        }
    }

    // Throttle distance/frustum evaluation to 2Hz to optimize CPU overhead
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

    FVector PlayerLoc = PC->GetPawn()->GetActorLocation();

    // Grab view frustum details for directional culling
    FVector CameraLocation;
    FRotator CameraRotation;
    PC->GetPlayerViewPoint(CameraLocation, CameraRotation);
    FVector CameraForward = CameraRotation.Vector();

    float ChunkDim = CurrentSettings->Size.X * CurrentSettings->Scale;
    int32 CenterX = FMath::FloorToInt(PlayerLoc.X / ChunkDim);
    int32 CenterY = FMath::FloorToInt(PlayerLoc.Y / ChunkDim);
    FIntPoint CurrentCoord(CenterX, CenterY);

    int32 Radius = CurrentSettings->RenderDistance;
    TSet<FIntPoint> ChunksToKeep;

    // Safety bubble ensures immediate surrounding chunks load regardless of camera orientation (prevents pop-in)
    float SafetyRadiusSq = FMath::Square(ChunkDim * 2.1f);

    for (int32 x = -Radius; x <= Radius; x++)
    {
        for (int32 y = -Radius; y <= Radius; y++)
        {
            FIntPoint TargetCoord = CurrentCoord + FIntPoint(x, y);

            FVector ChunkWorldPos(TargetCoord.X * ChunkDim, TargetCoord.Y * ChunkDim, PlayerLoc.Z);
            FVector DirToChunk = (ChunkWorldPos - CameraLocation).GetSafeNormal();

            float Dot = FVector::DotProduct(CameraForward, DirToChunk);
            float DistSq = FVector::DistSquared(PlayerLoc, ChunkWorldPos);

            bool bInSafetyBubble = DistSq <= SafetyRadiusSq;
            bool bInCameraCone = Dot > 0.1f; // Frustum threshold check

            if (bInSafetyBubble || bInCameraCone)
            {
                ChunksToKeep.Add(TargetCoord);

                if (!ActiveChunks.Contains(TargetCoord) && !LoadingChunks.Contains(TargetCoord))
                {
                    SpawnQueue.AddUnique(TargetCoord);
                }
            }
        }
    }

    // Cull active chunks falling outside the retention set
    TArray<FIntPoint> ToRecycle;
    for (auto& Pair : ActiveChunks)
    {
        if (!ChunksToKeep.Contains(Pair.Key))
        {
            // Teardown procedural foliage/instances via PCG before recycling
            UPCGComponent* PCGComp = Pair.Value->FindComponentByClass<UPCGComponent>();
            if (PCGComp)
            {
                PCGComp->Cleanup();
            }

            Pair.Value->SetActorEnableCollision(false);
            Pair.Value->SetActorTickEnabled(false);
            Pair.Value->SetActorHiddenInGame(true);

            ToRecycle.Add(Pair.Key);
        }
    }

    for (const FIntPoint& Coord : ToRecycle)
    {
        AChunk* RecycledChunk = ActiveChunks[Coord];
        if (RecycledChunk)
        {
            UPCGComponent* PCGComp = RecycledChunk->FindComponentByClass<UPCGComponent>();
            if (PCGComp)
            {
                PCGComp->Cleanup();
            }

            RecycledChunk->SetActorHiddenInGame(true);
            ChunkPool.Add(RecycledChunk);
        }
        ActiveChunks.Remove(Coord);
    }
}

void UChunkManager::SpawnChunk(FIntPoint Coord)
{
    if (!CurrentSettings || !GetWorld() || ActiveChunks.Contains(Coord) || LoadingChunks.Contains(Coord)) return;

    LoadingChunks.Add(Coord);

    // Copy data asset properties by value to guarantee thread safety on background tasks
    FIntPoint LocalSize = CurrentSettings->Size;
    float LocalScale = CurrentSettings->Scale;
    float LocalZMult = CurrentSettings->ZMultiplier;
    float LocalNoiseScale = CurrentSettings->NoiseScale;
    float LocalUVScale = CurrentSettings->UVScale;
    UMaterialInterface* LocalMaterial = CurrentSettings->ChunkMaterial;
    TSubclassOf<AChunk> LocalChunkClass = CurrentSettings->ChunkClass;

    TWeakObjectPtr<UChunkManager> WeakThis(this);

    // Offload heavy FBM noise and vertex mathematical calculations to worker threads
    AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [WeakThis, Coord, LocalSize, LocalScale, LocalZMult, LocalNoiseScale, LocalUVScale, LocalMaterial, LocalChunkClass]()
        {
            FChunkMeshData GeneratedData;

            if (WeakThis.IsValid())
            {
                WeakThis->GenerateMeshDataAsync(Coord, GeneratedData, LocalSize, LocalScale, LocalZMult, LocalNoiseScale, LocalUVScale);
            }

            // Route back to Game Thread to apply render data and manage actor/component lifecycles safely
            AsyncTask(ENamedThreads::GameThread, [WeakThis, Coord, GeneratedData, LocalSize, LocalScale, LocalMaterial, LocalChunkClass]()
                {
                    if (!WeakThis.IsValid() || !WeakThis->GetWorld() || !LocalChunkClass) return;

                    AChunk* NewChunk = nullptr;

                    // Pull from pool or instantiate fallback actor if pool is exhausted
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
                        NewChunk->RenderChunk(GeneratedData, LocalMaterial, Coord);

                        // Bootstrap center origin chunk and drop player onto valid terrain surface
                        if (Coord == FIntPoint(0, 0) && !WeakThis->bInitialSpawnComplete)
                        {
                            UProceduralMeshComponent* PMC = NewChunk->FindComponentByClass<UProceduralMeshComponent>();
                            if (PMC)
                            {
                                PMC->UpdateBounds();
                                PMC->RecreatePhysicsState();
                            }

                            WeakThis->PlacePlayerOnGround();
                            WeakThis->bInitialSpawnComplete = true;
                        }
                    }

                    WeakThis->LoadingChunks.Remove(Coord);
                });
        });
}

void UChunkManager::GenerateMeshDataAsync(FIntPoint Coord, FChunkMeshData& OutData, FIntPoint Size, float Scale, float ZMult, float NoiseScale, float UVScale)
{
    OutData.Clear();

    // Allocate heightmap buffer with a +3 border skirt for robust neighbor cross-product normal evaluation
    TArray<float> HeightMap;
    int32 SampleSizeX = Size.X + 3;
    int32 SampleSizeY = Size.Y + 3;
    HeightMap.SetNumUninitialized(SampleSizeX * SampleSizeY);

    double WorldAnchorX = (double)Coord.X * (double)Size.X;
    double WorldAnchorY = (double)Coord.Y * (double)Size.Y;

    // Sample FBM noise across mesh grid + padding
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

    // Populate vertex attributes using absolute world positioning to guarantee seamless chunk borders
    for (int32 y = 0; y <= Size.Y; y++)
    {
        for (int32 x = 0; x <= Size.X; x++)
        {
            int32 HMIndex = (x + 1) + (y + 1) * SampleSizeX;

            float VertX = (float)(WorldAnchorX + (double)x) * Scale;
            float VertY = (float)(WorldAnchorY + (double)y) * Scale;
            OutData.Vertices.Add(FVector(VertX, VertY, HeightMap[HMIndex]));

            // Global UV projection space prevents texture wrapping seams between adjacent chunks
            float GlobalUVX = (float)(WorldAnchorX + (double)x) * UVScale;
            float GlobalUVY = (float)(WorldAnchorY + (double)y) * UVScale;
            OutData.UV0.Add(FVector2D(GlobalUVX, GlobalUVY));

            // Central difference lookup from padding skirt for smooth lighting normals
            float H_L = HeightMap[HMIndex - 1];
            float H_R = HeightMap[HMIndex + 1];
            float H_D = HeightMap[HMIndex - SampleSizeX];
            float H_U = HeightMap[HMIndex + SampleSizeX];

            FVector SlopeX(2.0f * Scale, 0.0f, H_R - H_L);
            FVector SlopeY(0.0f, 2.0f * Scale, H_U - H_D);
            
            FVector Normal = FVector::CrossProduct(SlopeX, SlopeY).GetSafeNormal();
            OutData.Normals.Add(Normal);

            FVector TangentX = SlopeX.GetSafeNormal();
            OutData.Tangents.Add(FProcMeshTangent(TangentX, false));
        }
    }

    // Construct index buffer with alternating triangle diagonals to eliminate grid visual repetition artifacts
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

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(PC->GetPawn());
    Params.bTraceComplex = true;

    const int32 MaxAttempts = 20;
    const float SearchRadius = CurrentSettings->Size.X * CurrentSettings->Scale * 0.4f;
    const float FlatnessThreshold = 0.95f; // Dot product constraint ensuring surface isn't too steep

    for (int32 i = 0; i < MaxAttempts; i++)
    {
        FVector2D Offset = (i == 0) ? FVector2D::ZeroVector : FMath::RandPointInCircle(SearchRadius);
        FVector Start(Offset.X, Offset.Y, 50000.f);
        FVector End(Offset.X, Offset.Y, -50000.f);

        FHitResult Hit;
        if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
        {
            float Upness = FVector::DotProduct(Hit.ImpactNormal, FVector::UpVector);

            if (Upness >= FlatnessThreshold)
            {
                FVector SafeSpawnLocation = Hit.ImpactPoint + FVector(0.f, 0.f, 150.f);
                PC->GetPawn()->SetActorLocation(SafeSpawnLocation, false, nullptr, ETeleportType::ResetPhysics);
                PC->SetControlRotation(FRotator::ZeroRotator);
                return;
            }
        }
    }
}
