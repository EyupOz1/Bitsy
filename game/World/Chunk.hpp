#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"
#include "core/Utils.hpp"

class Chunk
{
public:
    bool dirty;

    Vector3Int position;

    std::vector<Block> blocks;
    std::vector<Vector3Int> blocksPos;

    void Init(Vector3Int pos);

    void Update();
    void Draw();

    void Destroy();

    void gen();

    Block getBlock(Vector3Int pos);
    bool setBlock(Vector3Int pos, Block block, bool shouldReplace);
    Mesh mesh;
    Model model;

    bool meshValid();
    bool modelValid();

    void meshModelDestroy();

    void perlin();
};
