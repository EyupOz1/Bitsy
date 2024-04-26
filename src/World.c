#include "World.h"

Vector3 getChunkPos(Vector3 pos)
{
    return (Vector3){(int)(pos.x / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.y / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.z / CHUNK_SIZE) * CHUNK_SIZE};
}
/*
void world_init(World *wrld)
{
    Chunk chnk1 = chunk_create((Vector3){0, 0, 0});
    Chunk chnk2 = chunk_create((Vector3){0, 16, 0});
    wrld->chunkCount = 0;
}
 */

void world_chunk_update(Player *player, Chunk** loadedChunks, int loadedChunksCount)
{
    Vector3 pos = getChunkPos(player->player_camera.position);
    Vector3 positions[] = {
        Vector3Add(pos, (Vector3){0, 0, 0}),
        Vector3Add(pos, (Vector3){CHUNK_SIZE, 0, 0}),
        Vector3Add(pos, (Vector3){-CHUNK_SIZE, 0, 0}),
        Vector3Add(pos, (Vector3){0, CHUNK_SIZE, 0}),
        Vector3Add(pos, (Vector3){0, -CHUNK_SIZE, 0}),
        Vector3Add(pos, (Vector3){0, 0, CHUNK_SIZE}),
        Vector3Add(pos, (Vector3){0, 0, -CHUNK_SIZE}),
    };

    int index = 0;
    for (int i = 0; i < loadedChunksCount; i++)
    {
        unsigned char shouldLoad = 0;
        for (int j = 0; j < 7; j++)
        {
            if (positions[j].x == (*loadedChunks[i]).pos.x && positions[j].y == (*loadedChunks[i]).pos.y && positions[j].z == (*loadedChunks[i]).pos.z)
            {
                shouldLoad = 1;
            }
        }

        if (shouldLoad)
        {
            (*loadedChunks[i]).shouldLoad = 1;
        }
        
    }
}