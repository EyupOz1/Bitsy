#pragma once

#include "raylib.h"
#include "Core/Math/Vector3Int.hpp"
#include "World/Block.hpp"
#include "World/Chunk.hpp"
#include <array>

int map(int input, int in_min, int in_max, int out_min, int out_max);
void getBaseNormals(float *inpt);
void calculateVertices(float *inpt, Vector3Int currPos);
Mesh generateChunkMesh(Chunk* chunk);
Vector2 filterNonZeroComponent(Vector3Int vec);