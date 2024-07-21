#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"
#include "Chunk.hpp"
#include "core/Utils.hpp"

class World
{

public:
    std::vector<Chunk *> loadedChunks;

    void Init(Vector3 playerPos);

    void Update(Vector3 playerPos, World &world);
    void Draw();

    void updateLoadedChunks(Vector3 playerPos);
    void updateMeshLoadedChunks(Vector3 playerPos, World &world);
    int findChunkByPos(Vector3Int pos);
    void calculateChunksToLoad(Vector3 playerPos, std::vector<Vector3Int> &chunksToLoad);
};
