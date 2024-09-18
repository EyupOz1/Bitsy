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
    void Update(Vector3Int playerChunkPos);

    int destroyed;
    int unloaded;
    int created;

private:
    void chunksToLoad(Vector3Int playerChunkPos, std::vector<Vector3Int> &chunksToLoad);
};
