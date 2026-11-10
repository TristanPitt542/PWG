#include "Chunk.h"
#include "ChunkMeshData.h"
#include "PCGComponent.h"
#include "ProceduralMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

AChunk::AChunk()
{
    // Disable per-frame tick since chunks are updated via ChunkManager calls
    PrimaryActorTick.bCanEverTick = false;

    // Create procedural mesh root component
    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProceduralMesh;
    
    // Enable complex collision for physics and trace queries
    ProceduralMesh->bUseComplexAsSimpleCollision = true;

    // Attach PCG component for procedural foliage/prop placement
    ChunkPCG = CreateDefaultSubobject<UPCGComponent>(TEXT("ChunkPCG"));
}

void AChunk::RenderChunk(const FChunkMeshData& MeshData, UMaterialInterface* Material, FIntPoint Coord)
{
    if (!ProceduralMesh) return;

    // Reset previous mesh section before creating a new one
    ProceduralMesh->ClearAllMeshSections();
    
    if (MeshData.Vertices.Num() > 0)
    {
        // Populate mesh section with calculated geometry data
        ProceduralMesh->CreateMeshSection_LinearColor(
            0, MeshData.Vertices, MeshData.Triangles, MeshData.Normals,
            MeshData.UV0, TArray<FLinearColor>(), MeshData.Tangents, true
        );

        if (Material) ProceduralMesh->SetMaterial(0, Material);

        // Ensure physics mesh data is generated for collision
        ProceduralMesh->ContainsPhysicsTriMeshData(true);
    }

    // Refresh mesh bounds and update physics state
    ProceduralMesh->UpdateBounds();
    ProceduralMesh->RecreatePhysicsState();

    if (ChunkPCG)
    {
        // Update PCG component transform and run generation
        ChunkPCG->UpdateComponentToWorld();
        ChunkPCG->Generate(true);
    }
}
