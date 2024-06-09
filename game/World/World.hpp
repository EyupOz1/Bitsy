#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"
#include "Chunk.hpp"

class World
{
private:
    std::vector<Chunk *> loadedChunks;

public:
    void Init();

    void Update(Vector3 playerPos);
    void Draw();

    int findChunkByPos(Vector3 pos);
    void calculateChunksToLoad(Vector3 playerPos, std::vector<Vector3> &chunksToLoad);
};
