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

void AChunk::RenderChunk(FChunkMeshData MeshData, UMaterialInterface* Material)
{
    if (!ProceduralMesh) return;

    // Check if we've already created section 0
    if (ProceduralMesh->GetNumSections() > 0)
    {
        ProceduralMesh->UpdateMeshSection_LinearColor(
            0, MeshData.Vertices, MeshData.Normals, MeshData.UV0, TArray<FLinearColor>(), MeshData.Tangents
        );
    }
    else
    {
        ProceduralMesh->CreateMeshSection_LinearColor(
            0, MeshData.Vertices, MeshData.Triangles, MeshData.Normals,
            MeshData.UV0, TArray<FLinearColor>(), MeshData.Tangents, true // Collision
        );
    }

    if (Material) ProceduralMesh->SetMaterial(0, Material);
}