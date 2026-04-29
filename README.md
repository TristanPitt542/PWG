https://github.com/user-attachments/assets/19d1f090-46d0-4a4e-95e9-368513857985

# PWG | Procedural World Generator

A high-performance Unreal Engine 5 framework for infinite, multithreaded terrain generation. This project bridges the gap between **C++ Procedural Meshes** and the **PCG (Procedural Content Generation)** framework to create dynamic, foliage-rich environments at runtime.

---

## 🚀 Key Features

* **Multithreaded Chunking:** Offloads heavy vertex and noise calculations to background threads to prevent game-thread hitches.
* **Runtime PCG Integration:** Dynamically populates the world with foliage, rocks, and debris using a custom PCG pipeline that "samples" procedural geometry on the fly.
* **Slope-Aware Distribution:** Uses vertex normal analysis to distinguish between flat grassy plains and steep mountain cliffs.
* **HISM Optimization:** Leverages Hierarchical Instanced Static Meshes for all environment assets to ensure high rendering performance even with dense forests.

---

## 🛠 Technical Architecture

### The Chunk Lifecycle
Generating foliage on procedural terrain requires strict synchronization between the Mesh, the Physics Engine, and the PCG Graph.

1.  **Vertex Generation:** `ChunkManager` (World Subsystem) calculates heightmaps.
2.  **Mesh Construction:** `AChunk` builds the `ProceduralMeshComponent` with complex collision.
3.  **Physics Sync:** Explicitly rebuilds the physics state so PCG raycasts can "hit" the mountains.
4.  **PCG Generation:** The PCG Graph executes a projection-based workflow to spawn assets.
