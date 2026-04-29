#include "Chunk.h"
#include "PCGComponent.h"
#include "ProceduralMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

AChunk::AChunk()
{
    PrimaryActorTick.bCanEverTick = false;

    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProceduralMesh;

    // Use Collision
    ProceduralMesh->bUseComplexAsSimpleCollision = true;


    ChunkPCG = CreateDefaultSubobject<UPCGComponent>(TEXT("ChunkPCG"));
}

void AChunk::RenderChunk(const FChunkMeshData& MeshData, UMaterialInterface* Material)
{
    if (!ProceduralMesh) return;

    // Render Terrain
    ProceduralMesh->ClearAllMeshSections();
    if (MeshData.Vertices.Num() > 0)
    {
        // The last parameter 'true' already handles collision generation internally
        ProceduralMesh->CreateMeshSection_LinearColor(
            0, MeshData.Vertices, MeshData.Triangles, MeshData.Normals,
            MeshData.UV0, TArray<FLinearColor>(), MeshData.Tangents, true
        );

        if (Material) ProceduralMesh->SetMaterial(0, Material);
    }

    // Trigger PCG
    if (ChunkPCG)
    {
        // UpdateBounds ensures PCG knows how big the mountain is
        ProceduralMesh->UpdateBounds();
        ProceduralMesh->RecreatePhysicsState();
        ChunkPCG->Cleanup();
        ChunkPCG->Generate(true);
    }
}