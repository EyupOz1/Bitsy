#pragma once

#include "raylib.h"
#include "rlights.h"

class Player
{
private:
    void move();

public:

    Camera camera;
    Vector3 position;

    Light light;

    void Init();
    void Update();
};