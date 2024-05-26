#pragma once

#define PATH_TEXTURES_ATLAS "res/textures/Atlas.png"
#define PATH_SHADERS_FRAGMENT "res/shaders/lighting.fs"
#define PATH_SHADERS_VERTEX "res/shaders/lighting.vs"
#define PATH_CONFIG "res/configs/cfg"

typedef struct Config
{
    unsigned char mouseActive;
    float flyingSpeed;
    float mouseSensitivity;
    float fieldOfView;
    Vector3 pos;
} Config;

extern Config GLOBAL;
