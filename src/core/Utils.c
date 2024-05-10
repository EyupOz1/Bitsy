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

float floorToInt(float x)
{
    if (x >= 0)
    {
        return (float)((int)x); // Cast x to int to truncate decimal part
    }
    else
    {
        int integerPart = (int)x;        // Get the integer part
        return (float)(integerPart - 1); // Subtract 1 for negative numbers
    }
}

Vector3 rayCollisionToBlockPos(RayCollision coll)
{
    Vector3 targetBlock = Vector3Zero();
    if (coll.normal.x != 0)
    {
        if (coll.point.x > 0)
        {
            float x = (coll.normal.x == 1.0f ? coll.point.x : coll.point.x - 1);
            targetBlock = (Vector3){x, coll.point.y, coll.point.z};
        }
        else
        {

            float x = (coll.normal.x == 1.0f ? coll.point.x + 1 : coll.point.x);
            targetBlock = (Vector3){x, coll.point.y, coll.point.z};
        }
    }
    else if (coll.normal.y != 0)
    {
        if (coll.point.y > 0)
        {
            float y = (coll.normal.y == 1.0f ? coll.point.y : coll.point.y - 1);
            targetBlock = (Vector3){coll.point.x, y, coll.point.z};
        }
        else
        {
            float y = (coll.normal.y == 1.0f ? coll.point.y + 1 : coll.point.y);
            targetBlock = (Vector3){coll.point.x, y, coll.point.z};
        }
    }
    else if (coll.normal.z != 0)
    {
        if (coll.point.z > 0)
        {
            float z = (coll.normal.z == 1 ? coll.point.z : coll.point.z - 1);
            targetBlock = (Vector3){coll.point.x, coll.point.y, z};
        }
        else
        {
            float z = (coll.normal.z == 1 ? coll.point.z + 1 : coll.point.z);
            targetBlock = (Vector3){coll.point.x, coll.point.y, z};
        }
    }
    targetBlock = (Vector3){floorToInt(targetBlock.x), floorToInt(targetBlock.y), floorToInt(targetBlock.z)};
    return targetBlock;
}