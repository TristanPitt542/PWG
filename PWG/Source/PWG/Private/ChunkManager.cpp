#include "ChunkManager.h"

void UChunkManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    // Initialize collections to prevent memory trash
    ActiveChunks.Empty();
    LoadingChunks.Empty();
}

void UChunkManager::Deinitialize()
{
    ActiveChunks.Empty();
    Super::Deinitialize();
}

void UChunkManager::LoadTerrainSettings(UChunkSettings* NewSettings)
{
    if (NewSettings)
    {
        CurrentSettings = NewSettings;
        UE_LOG(LogTemp, Warning, TEXT("Terrain Settings Loaded Successfully!"));


        // Now you can access: CurrentSettings->ChunkMaterial
        UpdateChunks();
    }
}

void UChunkManager::UpdateChunks()
{
    if (!CurrentSettings) return;

    // Use CurrentSettings->Size, CurrentSettings->NoiseScale, etc.
    // Example:
    float MyScale = CurrentSettings->Scale;
}