#pragma once

#include "raylib.h"
#include "../world/Chunk.h"
#include "math.h"
#include "../GLOBAL.h"
#include "../world/Block.h"

Vector3 worldPositionToChunk(Vector3 pos);
unsigned char Vector3Compare(Vector3 a, Vector3 b);
Vector3 rayCollisionToBlockPos(RayCollision coll);
unsigned char SaveStorageValue(unsigned int position, int value);
int LoadStorageValue(unsigned int position);