#include "Core/Utils.hpp"
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
#include "World/Block.hpp"

int map(int input, int in_min, int in_max, int out_min, int out_max)
{
    return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void getBaseNormals(float *inpt)
{
    float baseNormals[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f};

    for (int i = 0; i < 72; ++i)
    {
        inpt[i] = baseNormals[i];
    }
}

void calculateVertices(float *inpt, Vector3Int currPos)
{
    Vector3 pos = Vec3IntToVec3(currPos);

    float localVertices[] = {

        1 + pos.x, 0 + pos.y, 0 + pos.z,
        1 + pos.x, 0 + pos.y, 1 + pos.z,
        1 + pos.x, 1 + pos.y, 1 + pos.z,
        1 + pos.x, 1 + pos.y, 0 + pos.z,

        0 + pos.x, 0 + pos.y, 0 + pos.z,
        0 + pos.x, 1 + pos.y, 0 + pos.z,
        0 + pos.x, 1 + pos.y, 1 + pos.z,
        0 + pos.x, 0 + pos.y, 1 + pos.z,

        0 + pos.x, 1 + pos.y, 0 + pos.z,
        1 + pos.x, 1 + pos.y, 0 + pos.z,
        1 + pos.x, 1 + pos.y, 1 + pos.z,
        0 + pos.x, 1 + pos.y, 1 + pos.z,

        0 + pos.x, 0 + pos.y, 0 + pos.z,
        0 + pos.x, 0 + pos.y, 1 + pos.z,
        1 + pos.x, 0 + pos.y, 1 + pos.z,
        1 + pos.x, 0 + pos.y, 0 + pos.z,

        0 + pos.x, 0 + pos.y, 1 + pos.z,
        0 + pos.x, 1 + pos.y, 1 + pos.z,
        1 + pos.x, 1 + pos.y, 1 + pos.z,
        1 + pos.x, 0 + pos.y, 1 + pos.z,

        0 + pos.x, 0 + pos.y, 0 + pos.z,
        1 + pos.x, 0 + pos.y, 0 + pos.z,
        1 + pos.x, 1 + pos.y, 0 + pos.z,
        0 + pos.x, 1 + pos.y, 0 + pos.z};

    for (int i = 0; i < 72; ++i)
    {
        inpt[i] = localVertices[i];
    }
}

void getTexcoords(Block block, float (&buf)[48])
{
    Vector2 m_posZ = {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE};
    Vector2 m_negZ = {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE};
    Vector2 m_posY = {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE};
    Vector2 m_negY = {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE};
    Vector2 m_posX = {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE};
    Vector2 m_negX = {0 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE};

    float baseTexcoords[] = {
        m_posZ.x, m_posZ.y + ATLAS_Y_STEP_SIZE,
        m_posZ.x + ATLAS_X_STEP_SIZE, m_posZ.y + ATLAS_Y_STEP_SIZE,
        m_posZ.x + ATLAS_X_STEP_SIZE, m_posZ.y,
        m_posZ.x, m_posZ.y,

        m_negZ.x + ATLAS_X_STEP_SIZE, m_negZ.y + ATLAS_Y_STEP_SIZE,
        m_negZ.x + ATLAS_X_STEP_SIZE, m_negZ.y,
        m_negZ.x, m_negZ.y,
        m_negZ.x, m_negZ.y + ATLAS_Y_STEP_SIZE,

        m_posY.x, m_posY.y,
        m_posY.x, m_posY.y + ATLAS_Y_STEP_SIZE,
        m_posY.x + ATLAS_X_STEP_SIZE, m_posY.y + ATLAS_Y_STEP_SIZE,
        m_posY.x + ATLAS_X_STEP_SIZE, m_posY.y,

        m_negY.x + ATLAS_X_STEP_SIZE, m_negY.y,
        m_negY.x, m_negY.y,
        m_negY.x, m_negY.y + ATLAS_Y_STEP_SIZE,
        m_negY.x + ATLAS_X_STEP_SIZE, m_negY.y + ATLAS_Y_STEP_SIZE,

        m_posX.x + ATLAS_X_STEP_SIZE, m_posX.y + ATLAS_Y_STEP_SIZE,
        m_posX.x + ATLAS_X_STEP_SIZE, m_posX.y,
        m_posX.x, m_posX.y,
        m_posX.x, m_posX.y + ATLAS_Y_STEP_SIZE,

        m_negX.x, m_negX.y + ATLAS_Y_STEP_SIZE,
        m_negX.x + ATLAS_X_STEP_SIZE, m_negX.y + ATLAS_Y_STEP_SIZE,
        m_negX.x + ATLAS_X_STEP_SIZE, m_negX.y,
        m_negX.x, m_negX.y

    };

    for (int i = 0; i < 48; i++)
    {
        buf[i] = baseTexcoords[i];
    }
};