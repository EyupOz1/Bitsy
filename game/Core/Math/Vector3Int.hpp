#pragma once

#include "raylib.h"
#include "Core/Defines.hpp"
#include <algorithm>
#include <functional>

#define ExpandVc3(vec) vec.x, vec.y, vec.z

struct Vector3Int
{
    int x, y, z;

    Vector3Int add(const Vector3Int& vec);
    Vector3Int substract(const Vector3Int& vec);
    bool compare(const Vector3Int& vec);

    float distance(const Vector3Int& vec);
    float distanceSqr(const Vector3Int& vec);

    Vector3 toVector3();

    bool operator==(const Vector3Int &other) const;

    // if Vec3Int is chunk Coords -> use this hash function
    struct ChunkHash
    {
        std::size_t operator()(const Vector3Int& vec) const
        {
            int normX = vec.x / CHUNK_SIZE;
            int normY = vec.y / CHUNK_SIZE;
            int normZ = vec.z / CHUNK_SIZE;
            
            std::size_t hash = 17;
            hash = hash * 31 + std::hash<int>()(normX);
            hash = hash * 31 + std::hash<int>()(normY);
            hash = hash * 31 + std::hash<int>()(normZ);
            return hash;
        }
    };
};

Vector3Int Vector3IntAdd(Vector3Int vec1, Vector3Int vec2);
Vector3Int Vector3IntSubstract(Vector3Int vec1, Vector3Int vec2);
unsigned char Vector3IntCompare(Vector3Int vec1, Vector3Int vec2);
float Vector3IntDistance(Vector3Int v1, Vector3Int v2);
float Vector3IntDistanceSqr(Vector3Int v1, Vector3Int v2);
Vector3 Vector3IntToVector3(Vector3Int vec);

// Vector3
unsigned char Vector3Compare(Vector3 a, Vector3 b);
Vector3Int Vector3ToVector3Int(Vector3 vec);

// Chunk
int roundToChunkInt(float pos);
Vector3Int roundToChunkVec(Vector3 pos);