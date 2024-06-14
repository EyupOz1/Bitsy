#pragma once

#include "raylib.h"

#define ExpandVc3(vec) vec.x, vec.y, vec.z

struct Vector3Int
{
    int x, y, z;
};

float roundToChunk(float pos);
int map(int input, int in_min, int in_max, int out_min, int out_max);
void getBaseNormals(float *inpt);
void calculateVertices(float *inpt, Vector3Int currPos);
unsigned char Vector3Compare(Vector3 a, Vector3 b);

Vector3 Vec3IntToVec3(Vector3Int vec);
Vector3Int Vec3ToVec3Int(Vector3 vec);
Vector3Int Vector3IntAdd(Vector3Int vec1, Vector3Int vec2);
Vector3Int Vector3IntSubstract(Vector3Int vec1, Vector3Int vec2);
unsigned char Vector3IntCompare(Vector3Int vec1, Vector3Int vec2);
