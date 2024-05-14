#include "Utils.h"


// Math
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


#define STORAGE_DATA_FILE "test"

unsigned char SaveStorageValue(unsigned int position, int value)
{
    bool success = false;
    int dataSize = 0;
    unsigned int newDataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);
    unsigned char *newFileData = NULL;

    if (fileData != NULL)
    {
        if (dataSize <= (position*sizeof(int)))
        {
            // Increase data size up to position and store value
            newDataSize = (position + 1)*sizeof(int);
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
                TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", STORAGE_DATA_FILE, dataSize, position*sizeof(int));

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

        success = SaveFileData(STORAGE_DATA_FILE, newFileData, newDataSize);
        RL_FREE(newFileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
    }
    else
    {
        TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", STORAGE_DATA_FILE);

        dataSize = (position + 1)*sizeof(int);
        fileData = (unsigned char *)RL_MALLOC(dataSize);
        int *dataPtr = (int *)fileData;
        dataPtr[position] = value;

        success = SaveFileData(STORAGE_DATA_FILE, fileData, dataSize);
        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
    }

    return success;
}


int LoadStorageValue(unsigned int position)
{
    int value = 0;
    int dataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);

    if (fileData != NULL)
    {
        if (dataSize < (position*4)) TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
        else
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
    }

    return value;
}