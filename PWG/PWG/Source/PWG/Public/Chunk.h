#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkMeshData.h"
#include "Chunk.generated.h"

class UProceduralMeshComponent;
class UPCGComponent;

/**
 * Represents an individual spatial terrain chunk. Manages its own procedural mesh 
 * rendering section, collision cooking, and procedural content generation (PCG) bindings.
 */
UCLASS()
class PWG_API AChunk : public AActor
{
    GENERATED_BODY()

public:
    AChunk();

    // Renders the chunk geometry, updates material assignments, forces physics collision baking, and triggers PCG scattering
    void RenderChunk(const FChunkMeshData& MeshData, UMaterialInterface* Material, FIntPoint Coord);

    // Component accessors for external management and raycast queries
    UProceduralMeshComponent* GetProceduralMesh() const { return ProceduralMesh; }
    UPCGComponent* GetPCGComponent() const { return ChunkPCG; }

protected:
    // Core procedural mesh component acting as the actor's root transform container
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProceduralMeshComponent* ProceduralMesh;

    // PCG component handling automated foliage and asset scattering across the chunk surface
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPCGComponent* ChunkPCG;

    // Spatial grid coordinate assigned to this chunk instance
    FIntPoint ChunkCoord;
};
