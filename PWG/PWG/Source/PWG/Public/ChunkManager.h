#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ChunkManager.generated.h"

class AChunk;
class UChunkSettings;

UCLASS()
class PWG_API UChunkManager : public UTickableWorldSubsystem
{
    GENERATED_BODY()

public:
    // --- Lifecycle Overrides ---
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    virtual void OnWorldBeginPlay(UWorld& InWorld) override; // Subsystem version of BeginPlay
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UChunkManager, STATGROUP_Tickables); }

    // --- Public API ---
    UFUNCTION(BlueprintCallable, Category = "Terrain")
    void LoadTerrainSettings(UChunkSettings* NewSettings);
    void SpawnChunk(FIntPoint Coord);

protected:
    // --- Core Logic ---
    void UpdateChunks();
    void PlacePlayerOnGround();

    // --- Generation & Async ---
    // Ensure the MeshData struct is defined or forward-declared
    void GenerateMeshDataAsync(FIntPoint Coord, struct FChunkMeshData& OutData, FIntPoint Size, float Scale, float ZMult, float NoiseScale, float UVScale);

    // --- Noise & Math (The functions you were using) ---
    float GetFractalNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity);
    float GetRigidNoise(float X, float Y, int32 Octaves, float Persistence, float Lacunarity);
    float GetPerlinNoise(float X, float Y, float Scale); // Added back if you're using standard Perlin

private:
    // --- State Management ---
    UPROPERTY()
    UChunkSettings* CurrentSettings;

    UPROPERTY()
    TArray<AChunk*> ChunkPool; // Changed to TArray to support Pop/Add logic

    UPROPERTY()
    TMap<FIntPoint, AChunk*> ActiveChunks;

    TSet<FIntPoint> LoadingChunks;
    TArray<FIntPoint> SpawnQueue;

    FIntPoint LastPlayerChunkCoord;
    float TickTimer = 0.0f;
};