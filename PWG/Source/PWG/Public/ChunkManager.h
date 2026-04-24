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
    virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UChunkManager, STATGROUP_Tickables); }

    UFUNCTION(BlueprintCallable, Category = "Terrain")
    void LoadTerrainSettings(UChunkSettings* NewSettings);

    void UpdateChunks();
    void SpawnChunk(FIntPoint Coord);
    void GenerateMeshData(FIntPoint Coord, FChunkMeshData& OutData);
    void FinalizeChunk(FIntPoint Coord, FChunkMeshData& Data);

private:

    void GenerateMeshDataAsync(FIntPoint Coord, FChunkMeshData& OutData, FIntPoint Size, float Scale, float ZMult, float NoiseScale);
    void PlacePlayerOnGround();
    float GetFractalNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity);
    float GetRigidNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity);

    FIntPoint LastPlayerChunkCoord = FIntPoint(-999, -999);

    TArray<FIntPoint> SpawnQueue;

    float TickTimer = 0.0f;
    UPROPERTY(EditAnywhere, Category = "Terrain")
    UChunkSettings* CurrentSettings;

    UPROPERTY()
    TMap<FIntPoint, AChunk*> ActiveChunks;

    UPROPERTY()
    TSet<FIntPoint> LoadingChunks;
};