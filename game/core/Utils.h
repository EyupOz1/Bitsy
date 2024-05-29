#pragma once

#include "raylib.h"
#include "../world/Chunk.h"
#include "math.h"
#include "../GLOBAL.h"
#include "../world/Block.h"
#include "../world/ChunkSystem.h"
#include "math.h"

typedef struct ChunkSystem ChunkSystem;


Vector3 worldPositionToChunk(Vector3 pos);
unsigned char Vector3Compare(Vector3 a, Vector3 b);
Vector3 rayCollisionToBlockPos(RayCollision coll);
unsigned char SaveStorageValue(unsigned int position, int value);
int LoadStorageValue(unsigned int position);
void calculateChunkDistToDraw(int *dist, int trueRenderDistance);
void chunk_swap(ChunkSystem* chunkSys, int chunkIndex1, int chunkIndex2);