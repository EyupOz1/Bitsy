#include "cmath"
#include "State.hpp"
#include "Utils.hpp"
#include "Defines.hpp"

float roundToChunk(float pos)
{
    float res = pos;
    if (fmod(pos, CHUNK_SIZE) != 0)
    {
        res = (int)(pos / CHUNK_SIZE) * CHUNK_SIZE;
        if (pos < 0)
        {
            res -= CHUNK_SIZE;
        }
    }
    return res;
}

int map(int input, int in_min, int in_max, int out_min, int out_max)
{
    return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void getBaseNormals(float *inpt)
{
    float baseNormals[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f};

    for (int i = 0; i < 72; ++i)
    {
        inpt[i] = baseNormals[i];
    }
}

void calculateVertices(float *inpt, Vector3Int currPos)
{
    Vector3 pos = Vec3IntToVec3(currPos);

    float localVertices[] = {

        1 + pos.x, 0 + pos.y, 0 + pos.z,
        1 + pos.x, 0 + pos.y, 1 + pos.z,
        1 + pos.x, 1 + pos.y, 1 + pos.z,
        1 + pos.x, 1 + pos.y, 0 + pos.z,

        0 + pos.x, 0 + pos.y, 0 + pos.z,
        0 + pos.x, 1 + pos.y, 0 + pos.z,
        0 + pos.x, 1 + pos.y, 1 + pos.z,
        0 + pos.x, 0 + pos.y, 1 + pos.z,

        0 + pos.x, 1 + pos.y, 0 + pos.z,
        1 + pos.x, 1 + pos.y, 0 + pos.z,
        1 + pos.x, 1 + pos.y, 1 + pos.z,
        0 + pos.x, 1 + pos.y, 1 + pos.z,

        0 + pos.x, 0 + pos.y, 0 + pos.z,
        0 + pos.x, 0 + pos.y, 1 + pos.z,
        1 + pos.x, 0 + pos.y, 1 + pos.z,
        1 + pos.x, 0 + pos.y, 0 + pos.z,

        0 + pos.x, 0 + pos.y, 1 + pos.z,
        0 + pos.x, 1 + pos.y, 1 + pos.z,
        1 + pos.x, 1 + pos.y, 1 + pos.z,
        1 + pos.x, 0 + pos.y, 1 + pos.z,

        0 + pos.x, 0 + pos.y, 0 + pos.z,
        1 + pos.x, 0 + pos.y, 0 + pos.z,
        1 + pos.x, 1 + pos.y, 0 + pos.z,
        0 + pos.x, 1 + pos.y, 0 + pos.z};

    for (int i = 0; i < 72; ++i)
    {
        inpt[i] = localVertices[i];
    }
}

unsigned char Vector3Compare(Vector3 a, Vector3 b)
{
    if (a.x == b.x && a.y == b.y && a.z == b.z)
    {
        return 1;
    }

    return 0;
}

Vector3 Vec3IntToVec3(Vector3Int vec)
{
    return Vector3{static_cast<float>(vec.x), static_cast<float>(vec.y), static_cast<float>(vec.z)};
}

Vector3Int Vec3ToVec3Int(Vector3 vec)
{
    return Vector3Int{static_cast<int>(vec.x), static_cast<int>(vec.y), static_cast<int>(vec.z)};
}

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
    if (a.x == b.x && a.y == b.y && a.z == b.z)
    {
        return 1;
    }

    return 0;
}