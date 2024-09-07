#include "raylib.h"
#include "Core/Math/Vector3Int.hpp"
#include "Core/Defines.hpp"
#include <cmath>

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

Vector3 Vec3IntToVec3(Vector3Int vec)
{
    return Vector3{static_cast<float>(vec.x), static_cast<float>(vec.y), static_cast<float>(vec.z)};
}

Vector3Int Vec3ToVec3Int(Vector3 vec)
{
    return Vector3Int{static_cast<int>(vec.x), static_cast<int>(vec.y), static_cast<int>(vec.z)};
}

unsigned char Vector3Compare(Vector3 a, Vector3 b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}

Vector3Int roundToChunk(Vector3 pos)
{
    Vector3Int posx = {roundCHNK(pos.x), roundCHNK(pos.y), roundCHNK(pos.z)};
    return {posx};
}

int roundCHNK(float pos)
{
    if (pos - static_cast<int>(pos) == 0.0)
    {
        return static_cast<int>(pos);
    }
    
    int x = ((int)pos / CHUNK_SIZE) * CHUNK_SIZE;
    if (pos < 0)
    {
        x -= CHUNK_SIZE;
    }
    return x;
}