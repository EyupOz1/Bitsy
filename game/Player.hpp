#pragma once

#include "raylib.h"
#include "Lighting/Light.hpp"

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