#pragma once
// Define constants for each side of the cube
#define TOP_BIT     (1 << 0) // Bit 0 represents the top side
#define BOTTOM_BIT  (1 << 1) // Bit 1 represents the bottom side
#define FRONT_BIT   (1 << 2) // Bit 2 represents the front side
#define BACK_BIT    (1 << 3) // Bit 3 represents the back side
#define LEFT_BIT    (1 << 4) // Bit 4 represents the left side
#define RIGHT_BIT   (1 << 5) // Bit 5 represents the right side

#include "raylib.h"

typedef struct
{
    int BlockID;
    Texture tex;
    Vector3 coords;

} Block;

Mesh Block_Draw(unsigned char bitmask);
Texture2D block_texture_create();