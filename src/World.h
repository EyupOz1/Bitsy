#pragma once
#include "Chunk.h"
#include "raylib.h"
#include "Player.h"
#include "raymath.h"
#include "stdio.h"

#define WORLD_RENDER_DISTANCE 5


typedef struct World
{
    Chunk* loadedChunks[20];
    int chunkCount;

} World;

/* void World_getChunkFromPlayer(Player *player, World *world);
void world_init(World *wrld);
 */
Vector3 getChunkPos(Vector3 pos);
void world_chunk_update(Player *player, Chunk** loadedChunks, int loadedChunksCount);