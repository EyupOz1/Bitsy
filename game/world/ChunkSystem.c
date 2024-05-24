#include "ChunkSystem.h"

void chunkSystem_init(ChunkSystem *chunkSys)
{
    chunkSys->loadedChunksCount = 0;
}

void chunkSystem_update(Vector3 playerPos, ChunkSystem *chunkSys, Shader shader, Texture tex)
{
    reup(playerPos, chunkSys);

    draw(chunkSys, shader, tex);
}

void reup(Vector3 playerPos, ChunkSystem *chunkSys)
{
    Vector3 chunkPosPlayerIsIn = worldPositionToChunk(playerPos);
    const int chunksToLoadCount = 27;
    Vector3 chunksToLoad[chunksToLoadCount];

    int count = 0;
    int arr[] = {0, CHUNK_SIZE, -CHUNK_SIZE};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                chunksToLoad[count++] = Vector3Add(chunkPosPlayerIsIn, (Vector3){arr[i], arr[j], arr[k]});
            }
        }
    }

    for (int i = 0; i < chunksToLoadCount; i++)
    {
        unsigned char chunkExists = 0;
        for (int j = 0; j < chunkSys->loadedChunksCount; j++)
        {
            if (
                chunksToLoad[i].x == (chunkSys->loadedChunks[j])->pos.x &&
                chunksToLoad[i].y == (chunkSys->loadedChunks[j])->pos.y &&
                chunksToLoad[i].z == (chunkSys->loadedChunks[j])->pos.z)
            {
                chunkExists = 1;
                (chunkSys->loadedChunks[j])->shouldLoad = 1;
                break;
            }
        }
        if (!chunkExists)
        {

            Chunk *newChunk = RL_MALLOC(sizeof(Chunk));
            chunk_create(newChunk, chunksToLoad[i], 1);

            chunk_perlin_generate(newChunk);

            chunkSys->loadedChunks[(chunkSys->loadedChunksCount)++] = newChunk;
        }
    }
}

void draw(ChunkSystem *chunkSys, Shader shader, Texture tex)
{
    for (int i = 0; i < chunkSys->loadedChunksCount; i++)
    {
        if (chunkSys->loadedChunks[i]->dirty && chunkSys->loadedChunks[i]->shouldLoad)
        {
            chunk_mesh_create(chunkSys->loadedChunks[i]);
            chunkSys->loadedChunks[i]->currentModel = LoadModelFromMesh(chunkSys->loadedChunks[i]->currentMesh);
            chunkSys->loadedChunks[i]->dirty = 0;
        }
        if (chunkSys->loadedChunks[i]->shouldLoad)
        {
            chunkSys->loadedChunks[i]->shouldLoad = 0;
            chunkSys->loadedChunks[i]->currentModel.materials[0].maps[0].texture = tex;
            chunkSys->loadedChunks[i]->currentModel.materials[0].shader = shader;
            DrawModel(chunkSys->loadedChunks[i]->currentModel, chunkSys->loadedChunks[i]->pos, 1.0f, WHITE);
        }
    }
}

Chunk *chunk_find(ChunkSystem * chunkSys, Vector3 pos)
{
    Vector3 chunk_pos = worldPositionToChunk(pos);
    for (int i = 0; i < chunkSys->loadedChunksCount; i++)
    {
        if (chunkSys->loadedChunks[i]->pos.x == chunk_pos.x && chunkSys->loadedChunks[i]->pos.y == chunk_pos.y && chunkSys->loadedChunks[i]->pos.z == chunk_pos.z)
        {
            TraceLog(LOG_DEBUG, "Chunk_find: arg: %f, %f, %f res: %f, %f, %f", pos.x, pos.y, pos.z, chunkSys->loadedChunks[i]->pos.x, chunkSys->loadedChunks[i]->pos.y, chunkSys->loadedChunks[i]->pos.z);
            return chunkSys->loadedChunks[i];
        }
    }
    return 0;
}