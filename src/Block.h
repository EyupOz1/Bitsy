#pragma once
// Define constants for each side of the cube
#define DIR_POS_Y     (1 << 0) // Bit 0 represents the top side
#define DIR_NEG_Y  (1 << 1) // Bit 1 represents the bottom side
#define DIR_POS_X   (1 << 2) // Bit 2 represents the front side
#define DIR_NEG_X    (1 << 3) // Bit 3 represents the back side
#define DIR_POS_Z    (1 << 4) // Bit 4 represents the left side
#define DIR_NEG_Z   (1 << 5) // Bit 5 represents the right side


#define CHUNK_SIZE 6



#include "raylib.h"

typedef struct
{
    int BlockID;
    Vector3 coords;

} Block;

Mesh Block_Draw();