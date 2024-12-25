#pragma once

// Player
#define PLAYER_FOV 95
#define PLAYER_MOVEMENT_SPEED 10.0f
#define PLAYER_MOUSE_SENSITIVITY_SPEED 0.008f

// World
#define CHUNK_SIZE_XZ 32
#define RENDER_DISTANCE 5 // Needs to be odd number
#define CHUNK_SIZE_Y 128

// System

#define TEXTURE_SIZE 16
#define ATLAS_WIDTH 4
#define ATLAS_HEIGHT 2
#define ATLAS_X_STEP_SIZE (1.0f / ATLAS_WIDTH)
#define ATLAS_Y_STEP_SIZE (1.0f / ATLAS_HEIGHT)

#define PATH_TEXTURES_ATLAS "../res/textures/Atlas.png"
#define PATH_SHADERS_FRAGMENT "../res/shaders/lighting.fs"
#define PATH_SHADERS_VERTEX "../res/shaders/lighting.vs"


#define CHUNK_DELETE_DIST (RENDER_DISTANCE * CHUNK_SIZE_XZ) * (RENDER_DISTANCE * CHUNK_SIZE_XZ) * 2 + CHUNK_SIZE_XZ