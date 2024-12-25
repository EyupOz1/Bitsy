#pragma once

#include "Core/Math/Vector2Int.hpp"
#include "Core/Math/Vector3Int.hpp"
#include "raylib.h"
#include "World/World.hpp"

class Player
{
private:
    void move();

public:

    Camera camera;
    Vector3 position;
    Vector2Int currentChunkPos;
    Vector2Int lastChunkPos;


    void Init();
    void Update(World* world);

};