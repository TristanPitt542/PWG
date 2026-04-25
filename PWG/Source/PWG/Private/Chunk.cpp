#include "Chunk.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

AChunk::AChunk()
{
    PrimaryActorTick.bCanEverTick = false;

    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProceduralMesh;

    ProceduralMesh->bUseComplexAsSimpleCollision = true;

    ProceduralMesh->SetMobility(EComponentMobility::Static);
}

void AChunk::RenderChunk(const FChunkMeshData& MeshData, UMaterialInterface* Material)
{
    if (!ProceduralMesh) return;

    // Clear existing data to ensure the buffers are fresh
    ProceduralMesh->ClearAllMeshSections();

    ProceduralMesh->CreateMeshSection_LinearColor(
        0, 
        MeshData.Vertices, 
        MeshData.Triangles, 
        MeshData.Normals,
        MeshData.UV0, 
        TArray<FLinearColor>(), // Empty vertex colors
        MeshData.Tangents, 
        true // Create Collision
    );

    if (Material) ProceduralMesh->SetMaterial(0, Material);
}