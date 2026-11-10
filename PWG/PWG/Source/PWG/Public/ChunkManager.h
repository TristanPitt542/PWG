#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ChunkManager.generated.h"

class AChunk;
class UChunkSettings;

/**
 * Manages spatial terrain streaming, asynchronous worker thread task graphs, 
 * actor reuse pooling, and player spawn placement within the world.
 */
UCLASS()
class PWG_API UChunkManager : public UTickableWorldSubsystem
{
    GENERATED_BODY()

public:
    // --- Subsystem Lifecycle & Tick Overrides ---
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual void OnWorldBeginPlay(UWorld& InWorld) override;
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UChunkManager, STATGROUP_Tickables); }

    // --- Public API ---
    // Loads terrain configuration settings and triggers an immediate spatial update evaluation
    UFUNCTION(BlueprintCallable, Category = "Terrain")
    void LoadTerrainSettings(UChunkSettings* NewSettings);
    
    // Spawns or pulls a chunk actor for the specified grid coordinate
    void SpawnChunk(FIntPoint Coord);

protected:
    // --- Core Spatial Logic ---
    // Evaluates player camera position, handles frustum/distance culling, and manages streaming queues
    void UpdateChunks();
    
    // Performs raycast validation to safely drop the player onto flat terrain upon initial spawn
    void PlacePlayerOnGround();

    // --- Asynchronous Generation Pipeline ---
    // Executes off-thread FBM noise evaluations, gradient normal lookups, and vertex buffer construction
    void GenerateMeshDataAsync(FIntPoint Coord, struct FChunkMeshData& OutData, FIntPoint Size, float Scale, float ZMult, float NoiseScale, float UVScale);

    // --- Noise & Mathematical Utilities ---
    float GetFractalNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity);
    float GetRigidNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity);
    float GetPerlinNoise(float X, float Y, float Scale);

private:
    // --- State Management & Streaming Containers ---
    UPROPERTY()
    UChunkSettings* CurrentSettings;

    // Actor pool for recycling chunk actors to eliminate runtime garbage collection overhead
    UPROPERTY()
    TArray<AChunk*> ChunkPool;

    // Map tracking currently rendered and active chunks indexed by spatial grid coordinates
    UPROPERTY()
    TMap<FIntPoint, AChunk*> ActiveChunks;

    // Sets and queues preventing duplicate async requests and smoothing out instantiation cost over frames
    TSet<FIntPoint> LoadingChunks;
    TArray<FIntPoint> SpawnQueue;

    FIntPoint LastPlayerChunkCoord;
    float TickTimer = 0.0f;
    bool bInitialSpawnComplete = false;
};
