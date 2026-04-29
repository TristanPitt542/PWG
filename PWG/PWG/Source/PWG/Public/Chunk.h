#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkMeshData.h"
#include "Chunk.generated.h"

class UProceduralMeshComponent;
class UHierarchicalInstancedStaticMeshComponent;

UCLASS()
class PWG_API AChunk : public AActor
{
    GENERATED_BODY()

public:
    AChunk();

    // Passing by const reference to avoid expensive copies
    void RenderChunk(const FChunkMeshData& MeshData, UMaterialInterface* Material);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Terrain")
    UProceduralMeshComponent* ProceduralMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PCG")
    class UPCGComponent* ChunkPCG;
};