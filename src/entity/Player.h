#pragma once

#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "../world/Chunk.h"
#include "../core/Utils.h"


typedef struct Player
{

    Camera3D camera;
    
    Ray ray;
    RayCollision rayCollision;
    Vector3 targetBlockPosInWorldSpace;
    Vector3 targetBlockPosInChunkSpace;
    Vector3 targetChunkPos;
    unsigned char targetChunkValid;

} Player;

void player_init(Player *player);
void player_update(Player *player, Chunk **loadedChunks, int *loadedChunksCount);