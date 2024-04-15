#pragma once

#include "raylib.h"

typedef struct
{
    int BlockID;
    Texture tex;
    Vector3 coords;

} Block;

Mesh Block_Draw();
Texture2D block_texture_create();