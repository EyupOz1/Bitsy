#include "Texture.h"

RenderTexture texture_init()
{
    RenderTexture res = LoadRenderTexture(64, 16);
    BeginTextureMode(res);
    ClearBackground(BLANK);
    DrawRectangle(0, 0, 16, 16, DARKBROWN);
    DrawRectangle(16, 0, 16, 16, BROWN);
    DrawRectangle(32, 0, 16, 16, GREEN);
    DrawRectangle(48, 0, 16, 16, GOLD);
    EndTextureMode();
    return res;
}

Vector2 texture_getCoords(Blocks blockID)
{
    switch (blockID)
    {
    case BLOCK_stone:
        break;
    
    default:
        break;
    }
}