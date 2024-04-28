#include "World.h"

Vector3 world_PosToChunk(Vector3 pos)
{
    Vector3 res = (Vector3){(int)(pos.x / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.y / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.z / CHUNK_SIZE) * CHUNK_SIZE};

    return res;
}

void world_chunk_update(Player *player, Chunk **loadedChunks, int *loadedChunksCount)
{
    Vector3 chunkPosPlayerIsIn = world_PosToChunk(player->camera.position);
    int chunksToLoadCount = 27;
    Vector3 chunksToLoad[] = {

        Vector3Add(chunkPosPlayerIsIn, (Vector3){0, 0, 0}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){CHUNK_SIZE, 0, 0}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){-CHUNK_SIZE, 0, 0}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){0, CHUNK_SIZE, 0}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){0, -CHUNK_SIZE, 0}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){0, 0, CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){0, 0, -CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){CHUNK_SIZE, CHUNK_SIZE, 0}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){CHUNK_SIZE, -CHUNK_SIZE, 0}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){-CHUNK_SIZE, CHUNK_SIZE, 0}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){-CHUNK_SIZE, -CHUNK_SIZE, 0}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){CHUNK_SIZE, 0, CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){CHUNK_SIZE, 0, -CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){-CHUNK_SIZE, 0, CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){-CHUNK_SIZE, 0, -CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){0, CHUNK_SIZE, CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){0, CHUNK_SIZE, -CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){0, -CHUNK_SIZE, CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){0, -CHUNK_SIZE, -CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){CHUNK_SIZE, CHUNK_SIZE, -CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){CHUNK_SIZE, -CHUNK_SIZE, CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){CHUNK_SIZE, -CHUNK_SIZE, -CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){-CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){-CHUNK_SIZE, CHUNK_SIZE, -CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){-CHUNK_SIZE, -CHUNK_SIZE, CHUNK_SIZE}),
        Vector3Add(chunkPosPlayerIsIn, (Vector3){-CHUNK_SIZE, -CHUNK_SIZE, -CHUNK_SIZE})

    };

    for (int i = 0; i < chunksToLoadCount; i++)
    {
        unsigned char chunkExists = 0;
        for (int j = 0; j < *loadedChunksCount; j++)
        {
            if (
                chunksToLoad[i].x == (*loadedChunks[j]).pos.x &&
                chunksToLoad[i].y == (*loadedChunks[j]).pos.y &&
                chunksToLoad[i].z == (*loadedChunks[j]).pos.z)
            {
                chunkExists = 1;
                (*loadedChunks[j]).shouldLoad = 1;
                break;
            }
        }
        if (!chunkExists)
        {

            Chunk *newChunk = RL_MALLOC(sizeof(Chunk));
            chunk_create(newChunk, chunksToLoad[i]);
            newChunk->shouldLoad = 1;

            chunk_perlin_generate(newChunk);

            loadedChunks[(*loadedChunksCount)++] = newChunk;
        }
    }
}


void world_chunk_draw(Chunk **loadedChunks, int *loadedChunksCount)
{
        for (int i = 0; i < *loadedChunksCount; i++)
    {
        if (loadedChunks[i]->dirty && loadedChunks[i]->shouldLoad)
        {
            chunk_mesh_create(loadedChunks[i]);
            loadedChunks[i]->currentModel = LoadModelFromMesh(loadedChunks[i]->currentMesh);
            loadedChunks[i]->dirty = 0;
        }
        if (loadedChunks[i]->shouldLoad)
        {
            DrawModelWires(loadedChunks[i]->currentModel, loadedChunks[i]->pos, 1.0f, PURPLE);
            loadedChunks[i]->shouldLoad = 0;
        }
    }
}
