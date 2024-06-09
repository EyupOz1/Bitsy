#include "State.hpp"
#include "raylib.h"
#include "Defines.hpp"
#include "raymath.h"

State *State::instance = nullptr;

State::State()
{
    TraceLog(LOG_DEBUG, "Global State initialized");
    fieldOfView = 95;
    movementSpeed = 0.1f;
    playerStartingPos = {0, 0, 0};
    mouseSensitivity = 0.008f;
    renderDistance = 7;

    this->shader = LoadShader(PATH_SHADERS_VERTEX, PATH_SHADERS_FRAGMENT);
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    int ambientLoc = GetShaderLocation(shader, "ambient");
    float ambientVal[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    SetShaderValue(shader, ambientLoc, ambientVal, SHADER_UNIFORM_VEC4);




    this->atlas = LoadTexture(PATH_TEXTURES_ATLAS);

    this->blocks.push_back(
        BlockData("NULL",
                  "NULL",
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE}));

    this->blocks.push_back(
        BlockData("debug",
                  "Debug Block",
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE}));

    this->blocks.push_back(
        BlockData("dirt",
                  "Dirt",
                  {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE}));

    this->blocks.push_back(
        BlockData("grass",
                  "Grass",
                  {1 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {1 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {2 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {1 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
                  {1 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE}));
}

State::~State()
{
    TraceLog(LOG_DEBUG, "Global State initialized");
}