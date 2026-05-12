#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkMeshData.h"
#include "Chunk.generated.h"

class UProceduralMeshComponent;
class UPCGComponent;

UCLASS()
class PWG_API AChunk : public AActor
{
    GENERATED_BODY()

public:
    AChunk();

    // Declaration for the rendering logic used by ChunkManager
    void RenderChunk(const FChunkMeshData& MeshData, class UMaterialInterface* Material);

    UProceduralMeshComponent* GetProceduralMesh() const { return ProceduralMesh; }
    UPCGComponent* GetPCGComponent() const { return ChunkPCG; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProceduralMeshComponent* ProceduralMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPCGComponent* ChunkPCG;
};