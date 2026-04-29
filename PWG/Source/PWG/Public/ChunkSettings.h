#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChunkSettings.generated.h"

UCLASS(BlueprintType)
class PWG_API UChunkSettings : public UDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    FIntPoint Size = FIntPoint(32, 32);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    float Scale = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    float NoiseScale = 0.01f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    float ZMultiplier = 1500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    float UVScale = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    int32 RenderDistance = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    UMaterialInterface* ChunkMaterial;

    UPROPERTY(EditAnywhere, Category = "Settings")
    TSubclassOf<class AChunk> ChunkClass;
};