#include "Chunk.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

AChunk::AChunk()
{
    PrimaryActorTick.bCanEverTick = false;

    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProceduralMesh;

    // Performance optimization: 
    // If you don't need chunks to move, tell the engine it's static
    ProceduralMesh->SetMobility(EComponentMobility::Static);
}

void AChunk::RenderChunk(const FChunkMeshData& MeshData, UMaterialInterface* Material)
{
    if (!ProceduralMesh) return;

    ProceduralMesh->ClearAllMeshSections();

    // This is the only "heavy" call remaining. 
    // It takes the pre-calculated data and puts it on the GPU.
    ProceduralMesh->CreateMeshSection_LinearColor(
        0,
        MeshData.Vertices,
        MeshData.Triangles,
        MeshData.Normals,
        MeshData.UV0,
        TArray<FLinearColor>(), // Vertex Colors (unused)
        MeshData.Tangents,
        true // Create Collision
    );

    if (Material)
    {
        ProceduralMesh->SetMaterial(0, Material);
    }
}