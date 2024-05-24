#pragma once

#include "raylib.h"
#include "Chunk.h"

typedef struct ChunkSystem
{
    Chunk* loadedChunks[2000];
    int loadedChunksCount;
} ChunkSystem;

void chunkSystem_init(ChunkSystem* chunkSys);
void chunkSystem_update(Vector3 playerPos, ChunkSystem *chunkSys, Shader shader, Texture tex);
Chunk *chunk_find(ChunkSystem * chunkSys, Vector3 pos);
