#pragma once

#include "stdio.h"
#include "string.h"
#include "../core/Utils.h"

#include "raylib.h"
#include "raymath.h"

#define CHUNK_SIZE 16

typedef enum Blocks
{
    BLOCK_grass = 1,
    BLOCK_stone
} Blocks;

typedef struct
{
    int BlockID;
} Block;

typedef struct Chunk
{
    Block Blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Vector3 BlocksPos[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    int BlockPosIndex;

    Mesh currentMesh;
    Model currentModel;

    unsigned char dirty;
    Vector3 pos;
    unsigned char shouldLoad;
} Chunk;

void chunk_create(Chunk *chnk, Vector3 pos, int shouldLoad);
void chunk_mesh_create(Chunk *Chnk);
void chunk_block_add(Chunk *Chnk, Block Blck, Vector3 pos);
void chunk_perlin_generate(Chunk *chunk);
Chunk *chunk_find(Chunk **loadedChunks, int *loadedChunksCount, Vector3 pos);