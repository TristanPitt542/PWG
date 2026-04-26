#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ChunkMeshData.h"
#include "ChunkManager.generated.h"

class AChunk;
class UChunkSettings;

UCLASS()
class PWG_API UChunkManager : public UTickableWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UChunkManager, STATGROUP_Tickables); }

    UFUNCTION(BlueprintCallable, Category = "Terrain")
    void LoadTerrainSettings(UChunkSettings* NewSettings);

private:
    void UpdateChunks();
    void SpawnChunk(FIntPoint Coord);
    void PlacePlayerOnGround();

    // Ensure 7 arguments
    void GenerateMeshDataAsync(FIntPoint Coord, FChunkMeshData& OutData, FIntPoint Size, float Scale, float ZMult, float NoiseScale, float UVScale);

    static float GetFractalNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity);
    static float GetRigidNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity);

    UPROPERTY()
    UChunkSettings* CurrentSettings;

    UPROPERTY()
    TMap<FIntPoint, AChunk*> ActiveChunks;

    TSet<FIntPoint> LoadingChunks;
    TArray<FIntPoint> SpawnQueue;

    FIntPoint LastPlayerChunkCoord = FIntPoint(-999999, -999999);
    float TickTimer = 0.0f;
};