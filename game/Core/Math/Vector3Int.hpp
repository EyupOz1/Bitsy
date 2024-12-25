#pragma once

#include "Core/Defines.hpp"
#include "raylib.h"

#define ExpandVc3(vec) vec.x, vec.y, vec.z

struct Vector3Int
{
    int x, y, z;

    Vector3Int add(const Vector3Int &vec);
    Vector3Int substract(const Vector3Int &vec);
    Vector3Int multiply(const Vector3Int &vec);
    Vector3Int scale(int scale);
    bool compare(const Vector3Int &vec);

    float distance(const Vector3Int &vec);
    float distanceSqr(const Vector3Int &vec);

    int sumOfXYZ();

    Vector3 toVector3();

    bool operator==(const Vector3Int &other) const;
};

Vector3Int Vector3IntAdd(Vector3Int vec1, Vector3Int vec2);
Vector3Int Vector3IntSubstract(Vector3Int vec1, Vector3Int vec2);
Vector3Int Vector3IntMultiply(Vector3Int vec1, Vector3Int vec2);
Vector3Int Vector3IntScale(Vector3Int vec, int scale);
unsigned char Vector3IntCompare(Vector3Int vec1, Vector3Int vec2);
float Vector3IntDistance(Vector3Int v1, Vector3Int v2);
float Vector3IntDistanceSqr(Vector3Int v1, Vector3Int v2);
int Vector3IntSumOfXYZ(Vector3Int vec);
Vector3 Vector3IntToVector3(Vector3Int vec);

// Vector3
unsigned char Vector3Compare(Vector3 a, Vector3 b);
Vector3Int Vector3ToVector3Int(Vector3 vec);
