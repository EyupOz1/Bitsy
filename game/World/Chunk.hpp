#pragma once

#include "raylib.h"
#include <vector>
#include "World/Block.hpp"
#include "Core/Math/Vector3Int.hpp"

class Chunk
{
public:
    Vector3Int position;
    std::vector<BlockState> blocks;
    std::vector<Vector3Int> blocksPos;
    
    unsigned char status;

    Chunk(Vector3Int pos);
    void Init();

    void genTerrain();
    void genMesh();

    BlockState getBlock(Vector3Int pos);
    bool setBlock(Vector3Int pos, BlockState block, bool shouldReplace);

    Mesh mesh;
    Model model;
    bool validModel;
};
