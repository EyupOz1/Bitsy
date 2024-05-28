#pragma once

#define PATH_TEXTURES_ATLAS "res/textures/Atlas.png"
#define PATH_SHADERS_FRAGMENT "res/shaders/lighting.fs"
#define PATH_SHADERS_VERTEX "res/shaders/lighting.vs"
#define PATH_CONFIGS "res/configs/cfg"
#define PATH_CONFIGS_ATLAS "res/configs/cfg"
#define MAX_BLOCK_COUNT 64
#define TEXTURE_SIZE 16
#define ATLAS_WIDTH 4
#define ATLAS_HEIGHT 2
#define ATLAS_X_STEP_SIZE (1.0f / ATLAS_WIDTH)
#define ATLAS_Y_STEP_SIZE (1.0f / ATLAS_HEIGHT)


#include "raylib.h"

typedef struct BlockData
{
    char blockName[64];
    char screenName[64];

     
    Vector2 posZ;
    Vector2 negZ;
    Vector2 posY;
    Vector2 negY;
    Vector2 posX;
    Vector2 negX;

} BlockData;

typedef struct Config
{
    // Basic Settings
    unsigned char mouseActive;
    float flyingSpeed;
    float mouseSensitivity;
    float fieldOfView;
    Vector3 pos;
    unsigned char renderDistance; // Currently has to be converted to odd integer -> x = renderDist * 2 - 1; 



    BlockData blockDataList[MAX_BLOCK_COUNT];
    Texture atlas;
    Shader shader;

} Config;

extern Config GLOBAL;
