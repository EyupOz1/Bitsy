#pragma once

#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "stdio.h"

#define CAMERA_MOVE_SPEED 0.2f
#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.003f 


typedef struct Player
{

    Camera3D camera;
    

} Player;


void player_create(Player* player);
void player_update(Player *player);
