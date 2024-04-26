#pragma once
#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "stdio.h"


#define CAMERA_MOVE_SPEED 0.09f
#define CAMERA_ROTATION_SPEED 0.03f
#define CAMERA_PAN_SPEED 0.2f

// Camera mouse movement sensitivity
#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.003f // TODO: it should be independant of framerate
#define CAMERA_MOUSE_SCROLL_SENSITIVITY 1.5f

#define CAMERA_ORBITAL_SPEED 0.5f // Radians per second

#define CAMERA_FIRST_PERSON_STEP_TRIGONOMETRIC_DIVIDER 8.0f
#define CAMERA_FIRST_PERSON_STEP_DIVIDER 30.0f
#define CAMERA_FIRST_PERSON_WAVING_DIVIDER 200.0f

// PLAYER (used by camera)
#define PLAYER_MOVEMENT_SENSITIVITY 20.0f


typedef struct Player
{

    struct Camera3D player_camera;
    

} Player;


Player* player_create() ;
void player_update(Camera *camera, int mode);
Ray Player_keys(Player* player);