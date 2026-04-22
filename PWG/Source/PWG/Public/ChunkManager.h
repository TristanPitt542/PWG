#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ChunkSettings.h"
#include "ChunkManager.generated.h"

class AChunk;
struct FChunkMeshData;

UCLASS()
class PWG_API UChunkManager : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "Terrain")
    void LoadTerrainSettings(UChunkSettings* NewSettings);

private:
    UPROPERTY()
    UChunkSettings* CurrentSettings;

    UPROPERTY()
    TMap<FIntPoint, AChunk*> ActiveChunks;

    TSet<FIntPoint> LoadingChunks;

    void UpdateChunks();
    void FinalizeChunk(FIntPoint Coord, FChunkMeshData Data);
};