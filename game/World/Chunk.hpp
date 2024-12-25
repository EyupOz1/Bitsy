#pragma once

#include "Core/Math/Vector2Int.hpp"
#include "Core/Math/Vector3Int.hpp"
#include "raylib.h"
#include "World/Block.hpp"
#include <vector>

class Chunk
{
public:
    Vector2Int position;
    std::vector<BlockState> blocks;
    std::vector<Vector3Int> blocksPos;
    
    Chunk(Vector2Int pos);
    void Init();

    void genTerrain();
    void genMesh();

    BlockState getBlock(Vector3Int pos);
    bool setBlock(Vector3Int pos, BlockState block, bool shouldReplace);

    Mesh mesh;
    Model model;
    bool validModel;
};
