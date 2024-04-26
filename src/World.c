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

void world_chunk_update(Player *player, Chunk **loadedChunks, int *loadedChunksCount)
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

    for (int i = 0; i < 7; i++)
    {
        unsigned char chunkExists = 0;
        for (int j = 0; j < *loadedChunksCount; j++)
        {
            if (positions[i].x == (*loadedChunks[j]).pos.x && positions[i].y == (*loadedChunks[j]).pos.y && positions[i].z == (*loadedChunks[j]).pos.z)
            {
                chunkExists = 1;
                (*loadedChunks[i]).shouldLoad = 1;
            }
        }
        if (!chunkExists)
        {
            Chunk *ch = RL_MALLOC(sizeof(Chunk));
            chunk_create(ch, positions[i]);
            ch->shouldLoad = 1;
            chunk_block_add(ch, (Block){.BlockID = 1}, (Vector3){0, 0, 0});
            loadedChunks[(*loadedChunksCount)++] = ch;
        }
    }
}
