#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"
#include "core/Utils.hpp"

class Chunk
{
public:
    // data
    Vector3Int position;
    std::vector<Block> blocks;
    std::vector<Vector3Int> blocksPos;

    // meta
    bool dirty;
    Mesh mesh;
    Model model;

    //

    void Init(Vector3Int pos);
    void Destroy();

    void UpdateBlocks();
    void UpdateMesh();

    void genMeshModel();

    void Draw();

    Block getBlock(Vector3Int pos);
    bool setBlock(Vector3Int pos, Block block, bool shouldReplace);

    bool meshValid();
    bool modelValid();

    void meshModelDestroy();
};
