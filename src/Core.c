#include "Core.h"


int init(int screenWidth, int screenHeight, char* windowName, int targetFps)
{
    InitWindow(screenWidth, screenHeight, windowName);
    DisableCursor();
    SetTargetFPS(targetFps);
}