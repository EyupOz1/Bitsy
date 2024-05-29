#pragma once

#include "raylib.h"
#include "Chunk.h"
#include "WorldGen.h"
#include "Block.h"
#include "../core/Utils.h"

typedef struct ChunkSystem
{
    Chunk* loadedChunks[1024];
    int loadedChunksCount;
} ChunkSystem;

void chunkSystem_init(ChunkSystem* chunkSys);
void chunkSystem_update(Vector3 playerPos,Vector3 chunkPos, ChunkSystem *chunkSys);
Chunk *chunkSystem_findChunkByPos(ChunkSystem * chunkSys, Vector3 pos);
void chunkSystem_addChunk(ChunkSystem *chunkSys, Chunk *newChunk);