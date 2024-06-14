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
    void Init();

    void Update(Vector3 playerPos);
    void Draw();

    void place(Vector3Int pos, Block &block);

    void updateLoadedChunks(Vector3 playerPos);
    int findChunkByPos(Vector3Int pos);
    void calculateChunksToLoad(Vector3 playerPos, std::vector<Vector3Int> &chunksToLoad);
};
