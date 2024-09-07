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
    std::vector<Chunk *> chunksToDestroy;


    void Update(Vector3Int playerChunkPos);
};
