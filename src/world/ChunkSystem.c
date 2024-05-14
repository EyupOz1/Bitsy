#include "ChunkSystem.h"

void chunkSystem_init()
{
}

void chunkSystem_update(Player *player, Chunk **loadedChunks, int *loadedChunksCount, Shader shader, Texture tex)
{
    reup(player, loadedChunks, loadedChunksCount);

    draw(loadedChunks, loadedChunksCount, shader, tex);
}

void reup(Player *player, Chunk **loadedChunks, int *loadedChunksCount)
{
    Vector3 chunkPosPlayerIsIn = worldPositionToChunk(player->camera.position);
    int chunksToLoadCount = 27;
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
            chunk_create(newChunk, chunksToLoad[i], 1);

            chunk_perlin_generate(newChunk);

            loadedChunks[(*loadedChunksCount)++] = newChunk;
        }
    }
}

void draw(Chunk **loadedChunks, int *loadedChunksCount, Shader shader, Texture tex)
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
            loadedChunks[i]->shouldLoad = 0;
            loadedChunks[i]->currentModel.materials[0].maps[0].texture = tex;
            loadedChunks[i]->currentModel.materials[0].shader = shader;
            DrawModel(loadedChunks[i]->currentModel, loadedChunks[i]->pos, 1.0f, WHITE);
        }
    }
}