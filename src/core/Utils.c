#include "Utils.h"

// In World-Space
Vector3 worldPositionToChunk(Vector3 pos)
{
    Vector3 res = (Vector3){(int)(pos.x / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.y / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.z / CHUNK_SIZE) * CHUNK_SIZE};

    return res;
}

void worldPosToChunkAndPos(Vector3 worldPos, Vector3 *dstPosInChunkSpace, Chunk *dstChunk)
{
    Vector3 chunkPos = worldPositionToChunk(worldPos);
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
    Vector3 targetBlock = (Vector3){coll.point.x, coll.point.y, coll.point.z};

    if (coll.normal.x == 1.0f || coll.normal.x == -1.0f)
    {
        targetBlock.x = round(targetBlock.x);
        targetBlock.y = ceil(targetBlock.y);
        targetBlock.z = ceil(targetBlock.z);

        targetBlock.y--;
        targetBlock.z--;
        if (coll.normal.x == -1.0f)
        {
            targetBlock.x--;
        }
    }
    if (coll.normal.y == 1.0f || coll.normal.y == -1.0f)
    {
        targetBlock.x = ceil(targetBlock.x);
        targetBlock.y = round(targetBlock.y);
        targetBlock.z = ceil(targetBlock.z);

        targetBlock.x--;
        targetBlock.z--;
        if (coll.normal.y == -1.0f)
        {
            targetBlock.y--;
        }
    }
    if (coll.normal.z == 1.0f || coll.normal.z == -1.0f)
    {
        targetBlock.x = ceil(targetBlock.x);
        targetBlock.y = ceil(targetBlock.y);
        targetBlock.z = round(targetBlock.z);

        targetBlock.x--;
        targetBlock.y--;
        if (coll.normal.z == -1.0f)
        {
            targetBlock.z--;
        }
    }

    targetBlock = (Vector3){(targetBlock.x), (targetBlock.y), (targetBlock.z)};

    return targetBlock;
}