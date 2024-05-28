#include "ChunkSystem.h"

void chunkSystem_init(ChunkSystem *chunkSys)
{
    chunkSys->loadedChunksCount = 0;
}

void chunkSystem_update(Vector3 playerPos, ChunkSystem *chunkSys)
{
    update_chunksToLoad(playerPos, chunkSys);

    draw_chunksToLoad(chunkSys);
}

void update_chunksToLoad(Vector3 playerPos, ChunkSystem *chunkSys)
{
    // FIXME: Write function to set or reset Globals this doesnt need to be so ugly
    const unsigned char renderDist = GLOBAL.renderDistance * 2 - 1;
    Vector3 chunkPosOfPlayer = worldPositionToChunk(playerPos);
    Vector3 chunksToLoad[renderDist * renderDist * renderDist];

    int nearChunks[renderDist];
    calculateChunkDistToDraw(&nearChunks, renderDist);

    int count = 0;
    for (int i = 0; i < renderDist; i++)
    {
        for (int j = 0; j < renderDist; j++)
        {
            for (int k = 0; k < renderDist; k++)
            {
                chunksToLoad[count++] = Vector3Add(chunkPosOfPlayer, (Vector3){nearChunks[i], nearChunks[j], nearChunks[k]});
            }
        }
    }

    for (int i = 0; i < renderDist * renderDist * renderDist; i++)
    {
        Chunk *curr = chunkSystem_findChunkByPos(chunkSys, chunksToLoad[i]);
        //TraceLog(LOG_DEBUG, "CH %i", curr);

        if (curr)
        {
            curr->shouldLoad = 1;
        } else 
        {

            Chunk *newChunk = RL_MALLOC(sizeof(Chunk));
            chunk_create(newChunk, chunksToLoad[i], 1);
            worldGen_generate(newChunk);
            chunkSys->loadedChunks[(chunkSys->loadedChunksCount)++] = newChunk;
        }
    }
}

void draw_chunksToLoad(ChunkSystem *chunkSys)
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
            chunkSys->loadedChunks[i]->currentModel.materials[0].maps[0].texture = GLOBAL.atlas;
            chunkSys->loadedChunks[i]->currentModel.materials[0].shader = GLOBAL.shader;
            DrawModel(chunkSys->loadedChunks[i]->currentModel, chunkSys->loadedChunks[i]->pos, 1.0f, WHITE);
        }
    }
}

Chunk *chunkSystem_findChunkByPos(ChunkSystem *chunkSys, Vector3 pos)
{
    Vector3 chunk_pos = worldPositionToChunk(pos);
    for (int i = 0; i < chunkSys->loadedChunksCount; i++)
    {
        if (Vector3Compare(chunk_pos, chunkSys->loadedChunks[i]->pos))
        {
            //TraceLog(LOG_DEBUG, "Chunk_find: arg: %f, %f, %f res: %f, %f, %f", pos.x, pos.y, pos.z, chunkSys->loadedChunks[i]->pos.x, chunkSys->loadedChunks[i]->pos.y, chunkSys->loadedChunks[i]->pos.z);
            return chunkSys->loadedChunks[i];
        }
    }
    return 0;
}