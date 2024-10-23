#pragma once

// Player
#define PLAYER_FOV 95
#define PLAYER_MOVEMENT_SPEED 0.1f
#define PLAYER_MOUSE_SENSITIVITY_SPEED 0.008f

// World
#define CHUNK_SIZE 8
#define RENDER_DISTANCE 7 // Needs to be odd number  

// System
#define PATH_TEXTURES_ATLAS "res/textures/Atlas.png"

#define TEXTURE_SIZE 16
#define ATLAS_WIDTH 4
#define ATLAS_HEIGHT 2
#define ATLAS_X_STEP_SIZE (1.0f / ATLAS_WIDTH)
#define ATLAS_Y_STEP_SIZE (1.0f / ATLAS_HEIGHT)

#define PATH_TEXTURES_ATLAS "res/textures/Atlas.png"
#define PATH_SHADERS_FRAGMENT "res/shaders/lighting.fs"
#define PATH_SHADERS_VERTEX "res/shaders/lighting.vs"

#define CHUNK_STATUS_RENDER 0
#define CHUNK_STATUS_GEN_MODEL 1
