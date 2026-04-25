#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkMeshData.h" // Ensure FInstanceData is defined here
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

    // Array to hold HISMC for different asset types (0: Trees, 1: Rocks, etc.)
    UPROPERTY(VisibleAnywhere, Category = "Assets")
    TArray<UHierarchicalInstancedStaticMeshComponent*> AssetComponents;

    UPROPERTY(VisibleAnywhere)
    class UHierarchicalInstancedStaticMeshComponent* TreeHISMC;

    UPROPERTY(VisibleAnywhere)
    class UHierarchicalInstancedStaticMeshComponent* RockHISMC;

    // Helper to initialize HISMCs
    void SetupAssetComponent(int32 Index, UStaticMesh* Mesh);
};