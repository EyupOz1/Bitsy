#pragma once

#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "../world/Chunk.h"
#include "../world/ChunkSystem.h"
#include "../core/Utils.h"
#include "../GLOBAL.h"
#include "../world/Block.h"
#include "rlights.h"


typedef struct Player
{
    Camera3D camera;

    Light light;

    Ray ray;
    RayCollision rayCollision;

    Vector3 targetBlockPosInWorldSpace;
    Vector3 targetBlockPosInChunkSpace;
    Vector3 targetChunkPos;
    unsigned char targetChunkValid;

} Player;

void player_init(Player *player);
void player_update(Player *player, ChunkSystem *chunkSys);