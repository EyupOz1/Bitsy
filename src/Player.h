#pragma once

#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "Chunk.h"

#define CAMERA_MOVE_SPEED 0.2f
#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.003f

typedef struct Player
{

    Camera3D camera;

} Player;

void player_create(Player *player);
void player_move(Player *player);
RayCollision player_interact(Player *player, Chunk **loadedChunks, int *loadedChunksCount);
