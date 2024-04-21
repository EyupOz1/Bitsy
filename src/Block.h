#pragma once

#include "raylib.h"

#define BLOCK_VERTICES_COUNT 8
#define BLOCK_INDICES_COUNT 24

typedef struct
{
    int BlockID;
    Vector3 coords;

} Block;
