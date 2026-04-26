#include "Chunk.h"
#include "PCGComponent.h"
#include "ProceduralMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

AChunk::AChunk()
{
    PrimaryActorTick.bCanEverTick = false;

    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProceduralMesh;

    // This tells the engine to use the mesh geometry for traces/PCG sampling
    ProceduralMesh->bUseComplexAsSimpleCollision = true;

    // Initialize 2 asset types for now (Tree and Rock)
    for (int32 i = 0; i < 2; i++)
    {
        FName CompName = *FString::Printf(TEXT("AssetComponent_%d"), i);
        auto* NewComp = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(CompName);
        NewComp->SetupAttachment(RootComponent);
        AssetComponents.Add(NewComp);
    }

    ChunkPCG = CreateDefaultSubobject<UPCGComponent>(TEXT("ChunkPCG"));
}

void AChunk::RenderChunk(const FChunkMeshData& MeshData, UMaterialInterface* Material)
{
    if (!ProceduralMesh) return;

    // 1. Render Terrain
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

    // 2. Clear old manual assets
    for (UHierarchicalInstancedStaticMeshComponent* Comp : AssetComponents)
    {
        Comp->ClearInstances();
    }

    // 3. Render manual assets (the ones from your C++ noise logic)
    for (const FInstanceData& Inst : MeshData.Instances)
    {
        if (AssetComponents.IsValidIndex(Inst.TypeIndex))
        {
            AssetComponents[Inst.TypeIndex]->AddInstance(Inst.Transform);
        }
    }

    // 4. Trigger PCG for foliage
    if (ChunkPCG)
    {
        // UpdateBounds ensures PCG knows how big the mountain is
        ProceduralMesh->UpdateBounds();
        ProceduralMesh->RecreatePhysicsState();
        ChunkPCG->Cleanup();
        ChunkPCG->Generate(true);
    }
}