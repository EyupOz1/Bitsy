#pragma once
#include "Chunk.h"
#include "raylib.h"
#include "Player.h"
#include "raymath.h"
#include "stdio.h"

#define CHUNK_BUFFER 125


typedef struct World
{
    Chunk loadedChunks[5];

} World;

void World_getChunkFromPlayer(Player *player, World *world);