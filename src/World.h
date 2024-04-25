#pragma once
#include "Chunk.h"
#include "raylib.h"
#include "Player.h"
#include "raymath.h"
#include "stdio.h"

#define WORLD_RENDER_DISTANCE 5


typedef struct World
{
    Chunk loadedChunks[12];
    int chunkCount;

} World;

void World_getChunkFromPlayer(Player *player, World *world);