#include "Utils.h"

Vector3 worldPositionToChunk(Vector3 pos)
{
    Vector3 res = (Vector3){(int)(pos.x / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.y / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.z / CHUNK_SIZE) * CHUNK_SIZE};

    return res;
}

unsigned char Vector3Compare(Vector3 a, Vector3 b)
{
    if (a.x == b.x && a.y == b.y && a.z == b.z)
    {
        return 1;
    }

    return 0;
}

int map(int input, int in_min, int in_max, int out_min, int out_max)
{
    return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int roundToInt(float number)
{
    return (int)(number >= 0 ? floor(number + 0.5f) : ceil(number - 0.5f));
}

float floorToInt(float x) {
    if (x >= 0) {
        return (float)((int)x); // Cast x to int to truncate decimal part
    } else {
        int integerPart = (int)x; // Get the integer part
        return (float)(integerPart - 1); // Subtract 1 for negative numbers
    }
}