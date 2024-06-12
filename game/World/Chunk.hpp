#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"

class Chunk
{
public:
    bool dirty;

    Vector3 position;

    std::vector<Block> blocks;
    std::vector<Vector3> blocksPos;

    void Init(Vector3 pos);

    void Update();
    void Draw();

    void Destroy();

    void gen();

    Block getBlock(Vector3 pos);
    bool setBlock(Vector3 pos, Block block);

    Mesh mesh;
    Model model;

    bool meshValid();
    bool modelValid();

    void meshModelDestroy();

    void perlin();
};
