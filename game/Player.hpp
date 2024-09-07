#pragma once

#include "raylib.h"
#include "Core/Math/Vector3Int.hpp"

class Player
{
private:
    void move();

public:

    Camera camera;
    Vector3 position;
    Vector3Int currentChunkPos;


    void Init();
    void Update();

};