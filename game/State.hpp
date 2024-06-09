#pragma once

#include "raylib.h"
#include "World/BlockData.hpp"
#include <vector>
#include "rlights.h"


class State
{
public:
    unsigned char fieldOfView;
    float movementSpeed;
    Vector3 playerStartingPos;
    float mouseSensitivity;
    float renderDistance; // Needs to be odd; 

    Texture atlas;
    Shader shader;
    Light globalLight;

    std::vector<BlockData> blocks;

    static State &get()
    {

        if (!instance)
        {
            instance = new State();
        }
        return *instance;
    }

    State(const State &) = delete;
    State &operator=(const State &) = delete;

private:
    State();
    ~State();
    static State *instance;
};