#pragma once

#include "raylib.h"

#define ExpandVc2(vec) vec.x, vec.y

struct Vector2Int
{
    int x, y;

    Vector2Int add(const Vector2Int &vec);
    Vector2Int substract(const Vector2Int &vec);
    Vector2Int multiply(const Vector2Int &vec);
    Vector2Int scale(int scale);
    bool compare(const Vector2Int &vec);

    float distance(const Vector2Int &vec);
    float distanceSqr(const Vector2Int &vec);

    int sumOfXYZ();

    Vector2 toVector2();

    bool operator==(const Vector2Int &other) const;

};

Vector2Int Vector2IntAdd(Vector2Int vec1, Vector2Int vec2);
Vector2Int Vector2IntSubstract(Vector2Int vec1, Vector2Int vec2);
Vector2Int Vector2IntMultiply(Vector2Int vec1, Vector2Int vec2);
Vector2Int Vector2IntScale(Vector2Int vec, int scale);
unsigned char Vector2IntCompare(Vector2Int vec1, Vector2Int vec2);
float Vector2IntDistance(Vector2Int v1, Vector2Int v2);
float Vector2IntDistanceSqr(Vector2Int v1, Vector2Int v2);
int Vector2IntSumOfXYZ(Vector2Int vec);
Vector2 Vector2IntToVector2(Vector2Int vec);

// Vector2
unsigned char Vector2Compare(Vector2 a, Vector2 b);
Vector2Int Vector2ToVector2Int(Vector2 vec);
