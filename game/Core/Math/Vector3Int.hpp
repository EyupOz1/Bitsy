#pragma once

#include "raylib.h"

#define ExpandVc3(vec) vec.x, vec.y, vec.z
unsigned char Vector3Compare(Vector3 a, Vector3 b);

struct Vector3Int
{
    int x, y, z;
};

Vector3Int Vector3IntAdd(Vector3Int vec1, Vector3Int vec2);
Vector3Int Vector3IntSubstract(Vector3Int vec1, Vector3Int vec2);
unsigned char Vector3IntCompare(Vector3Int vec1, Vector3Int vec2);

float Vector3IntDistance(Vector3Int v1, Vector3Int v2);
float Vector3IntDistanceSqr(Vector3Int v1, Vector3Int v2);


Vector3 Vec3IntToVec3(Vector3Int vec);
Vector3Int Vec3ToVec3Int(Vector3 vec);


Vector3Int roundToChunk(Vector3 pos);
int roundCHNK(float pos);