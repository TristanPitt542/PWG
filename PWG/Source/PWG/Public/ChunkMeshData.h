#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "ChunkMeshData.generated.h"

USTRUCT(BlueprintType)
struct FInstanceData
{
    GENERATED_BODY()

    UPROPERTY()
    int32 TypeIndex; // 0 for Tree, 1 for Rock, etc.

    UPROPERTY()
    FTransform Transform;
};

USTRUCT(BlueprintType)
struct FChunkMeshData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Data")
    TArray<FVector> Vertices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Data")
    TArray<int32> Triangles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Data")
    TArray<FVector> Normals;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Data")
    TArray<FVector2D> UV0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Data")
    TArray<FProcMeshTangent> Tangents;

    UPROPERTY()
    TArray<FInstanceData> Instances;

    //Clear Data
    void Clear()
    {
        Vertices.Reset();
        Triangles.Reset();
        Normals.Reset();
        UV0.Reset();
        Tangents.Reset();
    }
};