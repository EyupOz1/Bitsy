#include "Utils.h"

// Math
Vector3 worldPositionToChunk(Vector3 pos)
{
    float x = pos.x, y = pos.y, z = pos.z;

    if (fmod(pos.x, CHUNK_SIZE) != 0)
    {
        x = (int)(pos.x / CHUNK_SIZE) * CHUNK_SIZE;
        if (pos.x < 0)
        {
            x -= CHUNK_SIZE;
        }
    }

    if (fmod(pos.y, CHUNK_SIZE) != 0)
    {
        y = (int)(pos.y / CHUNK_SIZE) * CHUNK_SIZE;
        if (pos.y < 0)
        {
            y -= CHUNK_SIZE;
        }
    }

    if (fmod(pos.z, CHUNK_SIZE) != 0)
    {
        z = (int)(pos.z / CHUNK_SIZE) * CHUNK_SIZE;

        if (pos.z < 0)
        {
            z -= CHUNK_SIZE;
        }
    }

    return (Vector3){x, y, z};
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

unsigned char SaveStorageValue(unsigned int position, int value)
{
    bool success = false;
    int dataSize = 0;
    unsigned int newDataSize = 0;
    unsigned char *fileData = LoadFileData(PATH_CONFIGS, &dataSize);
    unsigned char *newFileData = NULL;

    if (fileData != NULL)
    {
        if (dataSize <= (position * sizeof(int)))
        {
            // Increase data size up to position and store value
            newDataSize = (position + 1) * sizeof(int);
            newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);

            if (newFileData != NULL)
            {
                // RL_REALLOC succeded
                int *dataPtr = (int *)newFileData;
                dataPtr[position] = value;
            }
            else
            {
                // RL_REALLOC failed
                TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", PATH_CONFIGS, dataSize, position * sizeof(int));

                // We store the old size of the file
                newFileData = fileData;
                newDataSize = dataSize;
            }
        }
        else
        {
            // Store the old size of the file
            newFileData = fileData;
            newDataSize = dataSize;

            // Replace value on selected position
            int *dataPtr = (int *)newFileData;
            dataPtr[position] = value;
        }

        success = SaveFileData(PATH_CONFIGS, newFileData, newDataSize);
        RL_FREE(newFileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", PATH_CONFIGS, value);
    }
    else
    {
        TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", PATH_CONFIGS);

        dataSize = (position + 1) * sizeof(int);
        fileData = (unsigned char *)RL_MALLOC(dataSize);
        int *dataPtr = (int *)fileData;
        dataPtr[position] = value;

        success = SaveFileData(PATH_CONFIGS, fileData, dataSize);
        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", PATH_CONFIGS, value);
    }

    return success;
}

int LoadStorageValue(unsigned int position)
{
    int value = 0;
    int dataSize = 0;
    unsigned char *fileData = LoadFileData(PATH_CONFIGS, &dataSize);

    if (fileData != NULL)
    {
        if (dataSize < (position * 4))
            TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", PATH_CONFIGS, position);
        else
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", PATH_CONFIGS, value);
    }

    return value;
}

void calculateChunkDistToDraw(int *dist, int trueRenderDistance)
{
    int nearChunksCount = 0;
    int f = 1;
    dist[nearChunksCount++] = 0;
    for (; nearChunksCount < trueRenderDistance; nearChunksCount++)
    {
        if (nearChunksCount % 2 == 0)
        {
            dist[nearChunksCount] = CHUNK_SIZE * f++;
        }
        else
        {
            dist[nearChunksCount] = -(CHUNK_SIZE * f);
        }
    }
}


void  chunk_swap(ChunkSystem* chunkSys, int chunkIndex1, int chunkIndex2)
{
    Chunk* temp = chunkSys->loadedChunks[chunkIndex1];
    chunkSys->loadedChunks[chunkIndex1] = chunkSys->loadedChunks[chunkIndex2];
    chunkSys->loadedChunks[chunkIndex2] = temp; 
}

