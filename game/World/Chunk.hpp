#pragma once

#include "raylib.h"
#include <vector>
#include "World/Block.hpp"
#include "Core/Math/Vector3Int.hpp"
#include "atomic"

class Chunk
{
public:
    // data
    Vector3Int position;
    std::vector<Block> blocks;
    std::vector<Vector3Int> blocksPos;

    // meta
    Mesh mesh;
    Model model;

    std::atomic<unsigned char> status; // CHUNK_...

    void Init(Vector3Int pos);
    void Destroy();

    void UpdateBlocks();
    void generateMesh();

    Block getBlock(Vector3Int pos);
    bool setBlock(Vector3Int pos, Block block, bool shouldReplace);

};
