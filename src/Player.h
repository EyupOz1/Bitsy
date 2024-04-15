#pragma once
#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"


typedef struct Player
{

    struct Camera3D player_camera;
    

} Player;


Player* player_create() ;
