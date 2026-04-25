#include "ChunkManager.h"
#include "Chunk.h"
#include "ChunkSettings.h"
#include "KismetProceduralMeshLibrary.h"
#include "Engine/World.h"

void UChunkManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UChunkManager::Deinitialize()
{
    ActiveChunks.Empty();
    Super::Deinitialize();
}

void UChunkManager::Tick(float DeltaTime)
{
    // Every frame, check if we need to spawn something from the queue
    if (SpawnQueue.Num() > 0)
    {
        FIntPoint NextCoord = SpawnQueue[0];
        SpawnQueue.RemoveAt(0);
        SpawnChunk(NextCoord); // Move your existing SpawnActor logic here
    }

    // Only check for new chunks every 0.5 seconds
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

    // 1. Get the Player Position
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC || !PC->GetPawn()) return;

    FVector PlayerLocation = PC->GetPawn()->GetActorLocation();

    // Convert World Position to Chunk Coordinates
    // ChunkSizeInUnits = Size * Scale
    float ChunkWidth = CurrentSettings->Size.X * CurrentSettings->Scale;
    float ChunkHeight = CurrentSettings->Size.Y * CurrentSettings->Scale;

    int32 CurrentX = FMath::FloorToInt(PlayerLocation.X / ChunkWidth);
    int32 CurrentY = FMath::FloorToInt(PlayerLocation.Y / ChunkHeight);
    FIntPoint CurrentChunkCoord(CurrentX, CurrentY);

    // Only update if the player moved to a new chunk
    if (CurrentChunkCoord == LastPlayerChunkCoord) return;
    LastPlayerChunkCoord = CurrentChunkCoord;

    // Spiral/Square check around the player
    int32 Radius = CurrentSettings->RenderDistance;

    for (int32 x = -Radius; x <= Radius; x++)
    {
        for (int32 y = -Radius; y <= Radius; y++)
        {
            FIntPoint TargetCoord = CurrentChunkCoord + FIntPoint(x, y);
            SpawnChunk(TargetCoord);
        }
    }

    // Despawn chunks too far away
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
        AChunk* ChunkToDestroy = ActiveChunks[Coord];
        if (ChunkToDestroy) ChunkToDestroy->Destroy();
        ActiveChunks.Remove(Coord);
    }
}

void UChunkManager::SpawnChunk(FIntPoint Coord)
{
    if (!CurrentSettings || !GetWorld() || ActiveChunks.Contains(Coord) || LoadingChunks.Contains(Coord)) return;

    LoadingChunks.Add(Coord);

    // Capture settings into local variables for thread safety
    FIntPoint LocalSize = CurrentSettings->Size;
    float LocalScale = CurrentSettings->Scale;
    float LocalZMult = CurrentSettings->ZMultiplier;
    float LocalNoiseScale = CurrentSettings->NoiseScale;
    UMaterialInterface* LocalMaterial = CurrentSettings->ChunkMaterial;

    // Start Background Thread Task
    AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, Coord, LocalSize, LocalScale, LocalZMult, LocalNoiseScale, LocalMaterial]()
        {
            // Create the data here on the background thread
            FChunkMeshData GeneratedData;

            // Run the math
            GenerateMeshDataAsync(Coord, GeneratedData, LocalSize, LocalScale, LocalZMult, LocalNoiseScale);

            // Calculate Tangents
            UKismetProceduralMeshLibrary::CalculateTangentsForMesh(
                GeneratedData.Vertices, GeneratedData.Triangles, GeneratedData.UV0,
                GeneratedData.Normals, GeneratedData.Tangents
            );

            // Move back to Game Thread to spawn the Actor
            AsyncTask(ENamedThreads::GameThread, [this, Coord, GeneratedData, LocalSize, LocalScale, LocalMaterial]()
                {
                    if (!GetWorld()) return;

                    // Calculate spawn position
                    FVector SpawnLocation = FVector(Coord.X * LocalSize.X * LocalScale, Coord.Y * LocalSize.Y * LocalScale, 0);

                    FActorSpawnParameters Params;
                    AChunk* NewChunk = GetWorld()->SpawnActor<AChunk>(AChunk::StaticClass(), SpawnLocation, FRotator::ZeroRotator, Params);

                    if (NewChunk)
                    {
                        ActiveChunks.Add(Coord, NewChunk);

                        // Render the chunk with the data we generated
                        NewChunk->RenderChunk(GeneratedData, LocalMaterial);

                        // Teleport player if this is the origin chunk
                        if (Coord == FIntPoint(0, 0))
                        {
                            PlacePlayerOnGround();
                        }
                    }

                    LoadingChunks.Remove(Coord);
                });
        });
}

void UChunkManager::PlacePlayerOnGround()
{
APlayerController* PC = GetWorld()->GetFirstPlayerController();
if (!PC || !PC->GetPawn()) return;

AActor* PlayerPawn = PC->GetPawn();

// 1. Define Start and End points for the trace
// We start high up and trace down towards the center of the world
FVector TraceStart(0.0f, 0.0f, 20000.0f);
FVector TraceEnd(0.0f, 0.0f, -20000.0f);

FHitResult Hit;
FCollisionQueryParams QueryParams;
QueryParams.AddIgnoredActor(PlayerPawn); // Don't hit the player themselves

// 2. Perform the Line Trace
if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
{
    // 3. Move the player to the impact point + 100 units up
    FVector NewLocation = Hit.ImpactPoint + FVector(0, 0, 150.0f);
    PlayerPawn->SetActorLocation(NewLocation);
}
}

float UChunkManager::GetFractalNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity)
{
    float Total = 0.0f;
    float Frequency = 1.0f;
    float Amplitude = 1.0f;
    float MaxValue = 0.0f;

    float NoiseVal = FMath::PerlinNoise2D(FVector2D(X, Y));
    NoiseVal = 1.0f - FMath::Abs(NoiseVal);
    NoiseVal *= NoiseVal;

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
    float Total = 0.0f;
    float Frequency = 1.0f;
    float Amplitude = 1.0f;
    float Weight = 1.0f; // This will dampen the higher-frequency spikes

    for (int i = 0; i < Octaves; i++)
    {
        // Get raw noise and make it rigid
        float NoiseVal = 1.0f - FMath::Abs(FMath::PerlinNoise2D(FVector2D(X * Frequency, Y * Frequency)));

        // Apply the weight from the previous octave
        // This prevents "floating" spikes and forces detail into the ridges
        NoiseVal *= Weight;

        // Update weight for the next octave
        Weight = FMath::Clamp(NoiseVal * Persistence, 0.0f, 1.0f);

        Total += NoiseVal * Amplitude;

        Amplitude *= Persistence;
        Frequency *= Lacunarity;
    }
    return Total;
}

void UChunkManager::GenerateMeshData(FIntPoint Coord, FChunkMeshData& OutData)
{
    if (!CurrentSettings) return;

    const int32 XSize = CurrentSettings->Size.X;
    const int32 YSize = CurrentSettings->Size.Y;
    const float Scale = CurrentSettings->Scale;

    for (int32 y = 0; y <= YSize; y++)
    {
        for (int32 x = 0; x <= XSize; x++)
        {
            // Calculate Global Coordinates for seamless noise
            float GlobalX = (Coord.X * XSize + x) * CurrentSettings->NoiseScale;
            float GlobalY = (Coord.Y * YSize + y) * CurrentSettings->NoiseScale;

            float RawNoise = GetFractalNoise(GlobalX, GlobalY, 8, 0.5f, 2.0f); // Increased octaves to 8 for detail

            // Remap to 0-1
            float NormalizedNoise = (RawNoise + 1.0f) * 0.5f;

            // 1. Create a "Mask" for plains (low frequency noise)
            float LowFreq = (FMath::PerlinNoise2D(FVector2D(GlobalX * 0.2f, GlobalY * 0.2f)) + 1.0f) * 0.5f;

            // 2. Apply Power to the fractal noise
            // We use a high power (e.g., 4.0) to flatten valleys
            float MountainShape = FMath::Pow(NormalizedNoise, 4.0f);

            // 3. Blend based on the mask
            // This gives you flat areas (plains) and tall areas (mountains)
            float FinalHeight = FMath::Lerp(MountainShape * 0.05f, MountainShape, LowFreq);

            float Z = FinalHeight * CurrentSettings->ZMultiplier;

            OutData.Vertices.Add(FVector(x * Scale, y * Scale, Z));

            float WorldU = (Coord.X * XSize + x) * CurrentSettings->UVScale;
            float WorldV = (Coord.Y * YSize + y) * CurrentSettings->UVScale;

            OutData.UV0.Add(FVector2D(WorldU, WorldV));

            OutData.Normals.Add(FVector(0, 0, 1));
        }
    }

    // Generate Vertices
    for (int32 y = 0; y <= YSize; y++)
    {
        for (int32 x = 0; x <= XSize; x++)
        {
            float GlobalX = (Coord.X * XSize + x) * CurrentSettings->NoiseScale;
            float GlobalY = (Coord.Y * YSize + y) * CurrentSettings->NoiseScale;

            float NoiseValue = FMath::PerlinNoise2D(FVector2D(GlobalX, GlobalY));
            float Z = NoiseValue * CurrentSettings->ZMultiplier;

            OutData.Vertices.Add(FVector(x * Scale, y * Scale, Z));
            OutData.UV0.Add(FVector2D(x, y));
            OutData.Normals.Add(FVector(0, 0, 1));
        }
    }

    // Generate Triangles
    for (int32 y = 0; y < YSize; y++)
    {
        for (int32 x = 0; x < XSize; x++)
        {
            int32 i = x + (y * (XSize + 1));

            OutData.Triangles.Add(i);
            OutData.Triangles.Add(i + XSize + 1);
            OutData.Triangles.Add(i + 1);

            OutData.Triangles.Add(i + 1);
            OutData.Triangles.Add(i + XSize + 1);
            OutData.Triangles.Add(i + XSize + 2);
        }
    }
}

void UChunkManager::GenerateMeshDataAsync(FIntPoint Coord, FChunkMeshData& OutData, FIntPoint Size, float Scale, float ZMult, float NoiseScale)
{
    // lear Previous Data
    OutData.Vertices.Empty();
    OutData.UV0.Empty();
    OutData.Normals.Empty();
    OutData.Triangles.Empty();

    // Pre Calculate raw height
    const int32 BufferWidth = Size.X + 3;
    const int32 BufferHeight = Size.Y + 3;
    TArray<float> RawHeights;
    RawHeights.SetNum(BufferWidth * BufferHeight);

    for (int32 y = 0; y < BufferHeight; y++)
    {
        for (int32 x = 0; x < BufferWidth; x++)
        {
            // Global coordinates offset to account for the buffer padding
            float GlobalX = (Coord.X * Size.X + x - 1) * NoiseScale;
            float GlobalY = (Coord.Y * Size.Y + y - 1) * NoiseScale;

            // Biome Selector: Small multiplier (0.01 - 0.1) creates large biome regions
            float BiomeAlpha = (FMath::PerlinNoise2D(FVector2D(GlobalX * 0.1f, GlobalY * 0.1f)) + 1.0f) * 0.5f;

            // Terrain Generators
            float PlainsH = (FMath::PerlinNoise2D(FVector2D(GlobalX, GlobalY)) + 1.0f) * 0.5f * 0.1f;
            float MountainH = GetRigidNoise(GlobalX, GlobalY, 6, 0.5f, 2.0f);

            // Blend based on mask
            float BlendW = FMath::SmoothStep(0.4f, 0.6f, BiomeAlpha);
            RawHeights[x + (y * BufferWidth)] = FMath::Lerp(PlainsH, MountainH, BlendW);
        }
    }

    // Generate Smoothed Vertices
    for (int32 y = 1; y <= Size.Y + 1; y++)
    {
        for (int32 x = 1; x <= Size.X + 1; x++)
        {
            float Total = 0.0f;
            int32 Count = 0;

            // 3x3 Smoothing Kernel
            for (int32 ny = -1; ny <= 1; ny++)
            {
                for (int32 nx = -1; nx <= 1; nx++)
                {
                    int32 SampleX = x + nx;
                    int32 SampleY = y + ny;

                    // Bounds check to prevent the crash you encountered
                    if (RawHeights.IsValidIndex(SampleX + (SampleY * BufferWidth)))
                    {
                        Total += RawHeights[SampleX + (SampleY * BufferWidth)];
                        Count++;
                    }
                }
            }

            float SmoothedHeight = (Count > 0) ? (Total / (float)Count) : 0.0f;
            float FinalZ = SmoothedHeight * ZMult;

            // Add Vertex Data
            int32 LX = x - 1;
            int32 LY = y - 1;
            OutData.Vertices.Add(FVector(LX * Scale, LY * Scale, FinalZ));

            // World-Space UVs (prevent tiling artifacts)
            float WorldU = (Coord.X * Size.X + LX) * 0.1f;
            float WorldV = (Coord.Y * Size.Y + LY) * 0.1f;
            OutData.UV0.Add(FVector2D(WorldU, WorldV));

            OutData.Normals.Add(FVector(0, 0, 1));
        }
    }

    // Generate Triangles Alternating to Create Diamond Pattern
    for (int32 y = 0; y < Size.Y; y++)
    {
        for (int32 x = 0; x < Size.X; x++)
        {
            int32 Row = Size.X + 1;
            int32 i = x + (y * Row);

            // Checkerboard pattern for triangulation
            bool bFlipDiagonal = (x + y) % 2 == 0;

            if (bFlipDiagonal)
            {
                OutData.Triangles.Add(i);
                OutData.Triangles.Add(i + Row);
                OutData.Triangles.Add(i + Row + 1);

                OutData.Triangles.Add(i);
                OutData.Triangles.Add(i + Row + 1);
                OutData.Triangles.Add(i + 1);
            }
            else
            {
                OutData.Triangles.Add(i);
                OutData.Triangles.Add(i + Row);
                OutData.Triangles.Add(i + 1);

                OutData.Triangles.Add(i + 1);
                OutData.Triangles.Add(i + Row);
                OutData.Triangles.Add(i + Row + 1);
            }
        }
    }
}

void UChunkManager::FinalizeChunk(FIntPoint Coord, FChunkMeshData& Data)
{
    if (AChunk** ChunkPtr = ActiveChunks.Find(Coord))
    {
        if (*ChunkPtr)
        {
            UKismetProceduralMeshLibrary::CalculateTangentsForMesh(
                Data.Vertices,
                Data.Triangles,
                Data.UV0,
                Data.Normals,
                Data.Tangents
            );

            (*ChunkPtr)->RenderChunk(Data, CurrentSettings->ChunkMaterial);
        }
    }
}