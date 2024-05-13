#include "Texture.h"

RenderTexture texture_init()
{
    RenderTexture res = LoadRenderTexture(64, 16);
    /*
    Image img = LoadImage("Test.png");
    res.texture = LoadTextureFromImage(img); 
    
    */
    BeginTextureMode(res);
    ClearBackground(BLANK);
    DrawRectangle(0, 0, 16, 16, RED);
    DrawCircle(8, 8, 5.0f, BLACK);
    DrawRectangle(16, 0, 16, 16, GREEN);
    DrawRectangle(32, 0, 16, 16, BLUE);
    DrawRectangle(48, 0, 16, 16, PURPLE);
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