#include "Chunk.h"
#include "ProceduralMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

AChunk::AChunk()
{
    PrimaryActorTick.bCanEverTick = false;

    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProceduralMesh;
    ProceduralMesh->bUseComplexAsSimpleCollision = true;

    // Initialize 2 asset types for now (Tree and Rock)
    // In a production environment, you'd load these from a Data Asset
    for (int32 i = 0; i < 2; i++)
    {
        FName CompName = *FString::Printf(TEXT("AssetComponent_%d"), i);
        auto* NewComp = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(CompName);
        NewComp->SetupAttachment(RootComponent);
        AssetComponents.Add(NewComp);
    }
}

void AChunk::RenderChunk(const FChunkMeshData& MeshData, UMaterialInterface* Material)
{
    if (!ProceduralMesh) return;

    // 1. Render Terrain
    ProceduralMesh->ClearAllMeshSections();
    if (MeshData.Vertices.Num() > 0)
    {
        ProceduralMesh->CreateMeshSection_LinearColor(
            0, MeshData.Vertices, MeshData.Triangles, MeshData.Normals,
            MeshData.UV0, TArray<FLinearColor>(), MeshData.Tangents, true
        );
        if (Material) ProceduralMesh->SetMaterial(0, Material);
    }

    // 2. Render Assets (Trees/Rocks)
    for (UHierarchicalInstancedStaticMeshComponent* Comp : AssetComponents)
    {
        Comp->ClearInstances();
    }

    for (const FInstanceData& Inst : MeshData.Instances)
    {
        if (AssetComponents.IsValidIndex(Inst.TypeIndex))
        {
            // Transforms are local to the Chunk Actor to preserve precision
            AssetComponents[Inst.TypeIndex]->AddInstance(Inst.Transform);
        }
    }
}