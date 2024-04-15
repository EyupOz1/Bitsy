#pragma once
#include "Block.h"
#include "main.h"

typedef struct Chunk
{
    Block Blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Mesh currentMesh;
} Chunk;
