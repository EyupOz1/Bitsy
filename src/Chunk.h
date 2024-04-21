#pragma once

#include "stdio.h"
#include "string.h"

#include "raylib.h"

#include "Block.h"

#define CHUNK_SIZE 6



typedef struct Chunk
{
    Block Blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Mesh currentMesh;
    unsigned char dirty;
} Chunk;

void chunk_mesh_create(Chunk *Chnk);