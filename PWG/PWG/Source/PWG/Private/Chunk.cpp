#include "Chunk.h"
#include "ChunkMeshData.h"
#include "PCGComponent.h"
#include "ProceduralMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

AChunk::AChunk()
{
    PrimaryActorTick.bCanEverTick = false;

    // These names now match the updated header
    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProceduralMesh;
    ProceduralMesh->bUseComplexAsSimpleCollision = true;

    ChunkPCG = CreateDefaultSubobject<UPCGComponent>(TEXT("ChunkPCG"));
}

void AChunk::RenderChunk(const FChunkMeshData& MeshData, UMaterialInterface* Material, FIntPoint Coord)
{
    if (!ProceduralMesh) return;

    ProceduralMesh->ClearAllMeshSections();
    if (MeshData.Vertices.Num() > 0)
    {
        ProceduralMesh->CreateMeshSection_LinearColor(
            0, MeshData.Vertices, MeshData.Triangles, MeshData.Normals,
            MeshData.UV0, TArray<FLinearColor>(), MeshData.Tangents, true
        );

        if (Material) ProceduralMesh->SetMaterial(0, Material);

        // Force collision update before PCG samples the surface
        ProceduralMesh->ContainsPhysicsTriMeshData(true);
    }

    // Update the mesh first
    ProceduralMesh->UpdateBounds();
    ProceduralMesh->RecreatePhysicsState();

    if (ChunkPCG)
    {
        // Sync the component to the new world location
        ChunkPCG->UpdateComponentToWorld();

        // Trigger the generation
        ChunkPCG->Generate(true);
    }
}