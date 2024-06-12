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




void calculateVertices(float *inpt, Vector3 &currPos)
{
        float localVertices[] = {

            1 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,

            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,

            0 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,

            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 0 + currPos.z,

            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,

            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 0 + currPos.z};



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

