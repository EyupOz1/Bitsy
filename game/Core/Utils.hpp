#pragma once

#include "raylib.h"
#include "Core/Math/Vector3Int.hpp"
#include "World/Block.hpp"


int map(int input, int in_min, int in_max, int out_min, int out_max);
void getBaseNormals(float *inpt);
void calculateVertices(float *inpt, Vector3Int currPos);
void getTexcoords(Block block, float (&buf)[48]);