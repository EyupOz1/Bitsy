#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"
#include "Chunk.hpp"

class World
{

public:
    std::vector<Chunk *> loadedChunks;
    void Init();

    void Update(Vector3 playerPos);
    void Draw();

    void place(Vector3 pos, Block &block);

    void updateLoadedChunks(Vector3 playerPos);
    int findChunkByPos(Vector3 pos);
    void calculateChunksToLoad(Vector3 playerPos, std::vector<Vector3> &chunksToLoad);
};
