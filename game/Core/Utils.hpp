#pragma once

#include "Core/Math/Vector3Int.hpp"
#include "raylib.h"
#include "World/Chunk.hpp"

int map(int input, int in_min, int in_max, int out_min, int out_max);
void getBaseNormals(float *inpt);
void calculateVertices(float *inpt, Vector3Int currPos);
Mesh generateChunkMesh(Chunk* chunk);
Vector2 filterNonZeroComponent(Vector3Int vec);
//float abs(float x);
Vector3Int roundToChunkVec(Vector3 pos);
Vector2Int roundToChunkVec(Vector2 pos);