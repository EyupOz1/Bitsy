#include "raylib.h"
#include "Core/Math/Vector3Int.hpp"
#include "Core/Defines.hpp"
#include <cmath>

// Vector3Int Class implementation down below
Vector3Int Vector3IntAdd(Vector3Int vec1, Vector3Int vec2)
{
    return {vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z};
}
Vector3Int Vector3IntSubstract(Vector3Int vec1, Vector3Int vec2)
{
    return {vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z};
}
unsigned char Vector3IntCompare(Vector3Int a, Vector3Int b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}
float Vector3IntDistance(Vector3Int v1, Vector3Int v2)
{
    float result = 0.0f;

    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;
    result = sqrtf(dx * dx + dy * dy + dz * dz);

    return result;
}
float Vector3IntDistanceSqr(Vector3Int v1, Vector3Int v2)
{
    float result = 0.0f;

    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;
    result = dx * dx + dy * dy + dz * dz;

    return result;
}
Vector3 Vector3IntToVector3(Vector3Int vec)
{
    return Vector3{
        static_cast<float>(vec.x),
        static_cast<float>(vec.y),
        static_cast<float>(vec.z)};
}

// Vector3
unsigned char Vector3Compare(Vector3 a, Vector3 b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}
Vector3Int Vector3ToVector3Int(Vector3 vec)
{
    return Vector3Int{
        static_cast<int>(vec.x),
        static_cast<int>(vec.y),
        static_cast<int>(vec.z)};
}

// Vector3Int Class
Vector3Int Vector3Int::add(const Vector3Int &vec)
{
    return Vector3IntAdd({x, y, z}, vec);
}
Vector3Int Vector3Int::substract(const Vector3Int &vec)
{
    return Vector3IntSubstract({x, y, z}, vec);
}
bool Vector3Int::compare(const Vector3Int &vec)
{
    return Vector3IntCompare({x, y, z}, vec);
}

float Vector3Int::distance(const Vector3Int &vec)
{
    return Vector3IntDistance({x, y, z}, vec);
}
float Vector3Int::distanceSqr(const Vector3Int &vec)
{
    return Vector3IntDistanceSqr({x, y, z}, vec);
}

Vector3 Vector3Int::toVector3()
{
    return Vector3IntToVector3({x, y, z});
}

bool Vector3Int::operator==(const Vector3Int &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

// Chunk
int roundToChunkInt(float pos)
{

    int x = ((int)pos / CHUNK_SIZE) * CHUNK_SIZE;
    if (pos < 0)
    {
        x -= CHUNK_SIZE;
    }

    return x;
}

Vector3Int roundToChunkVec(Vector3 pos)
{
    Vector3Int posx = {roundToChunkInt(pos.x), roundToChunkInt(pos.y), roundToChunkInt(pos.z)};
    return {posx};
}
