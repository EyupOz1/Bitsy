#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"

class Chunk
{
public:
    Mesh mesh;
    Model model;

    bool dirty;

    Vector3 position;

    std::vector<Block> blocks;
    std::vector<Vector3> blocksPos;

    void Init(Vector3 pos);

    void Update();
    void Draw();
    void Destroy();

    void gen();
    void perlin();

    Block getBlock(Vector3 pos);
    bool setBlock(Vector3 pos, Block block);
};
