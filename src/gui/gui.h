#pragma once

#include "raylib.h"

typedef struct
{
    char tools[100][20];
    int toolsCount;
} DebugInfo;

typedef struct
{
    Vector2 window_position;
    Vector2 window_size;
    bool minimized;
    bool moving;
    bool resizing;
    Vector2 scroll;
} DebugWindow;

void DEBUG_update();
void DEBUG_add(const char *info);
void DEBUG_end();