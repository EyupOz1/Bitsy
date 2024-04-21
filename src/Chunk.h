#pragma once
#include "Block.h"
#include "raylib.h"
#include "Block.h"
#include "Chunk.h"
#include "stdio.h"


typedef struct Chunk
{
    Block Blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Mesh currentMesh;
} Chunk;

Mesh chunk_mesh_create(Chunk *Chnk);
