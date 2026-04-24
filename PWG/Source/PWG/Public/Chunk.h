// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ChunkMeshData.h"

#include "Chunk.generated.h"


class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class PWG_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:
    AChunk();

    void RenderChunk(FChunkMeshData MeshData, UMaterialInterface* Material);

protected:
    UPROPERTY(VisibleAnywhere)
    UProceduralMeshComponent* ProceduralMesh;
};