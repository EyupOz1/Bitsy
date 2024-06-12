#include "BlockData.hpp"
#include "Block.hpp"
#include "Core/State.hpp"
#include "Core/Defines.hpp"

void BlockData::getTexcoords(Block &block, float (&buf)[48])
{
    BlockData blockData = State::get().blocks[block.ID];

    float baseTexcoords[] = {
        blockData.m_posZ.x, blockData.m_posZ.y + ATLAS_Y_STEP_SIZE,
        blockData.m_posZ.x + ATLAS_X_STEP_SIZE, blockData.m_posZ.y + ATLAS_Y_STEP_SIZE,
        blockData.m_posZ.x + ATLAS_X_STEP_SIZE, blockData.m_posZ.y,
        blockData.m_posZ.x, blockData.m_posZ.y,

        blockData.m_negZ.x + ATLAS_X_STEP_SIZE, blockData.m_negZ.y + ATLAS_Y_STEP_SIZE,
        blockData.m_negZ.x + ATLAS_X_STEP_SIZE, blockData.m_negZ.y,
        blockData.m_negZ.x, blockData.m_negZ.y,
        blockData.m_negZ.x, blockData.m_negZ.y + ATLAS_Y_STEP_SIZE,

        blockData.m_posY.x, blockData.m_posY.y,
        blockData.m_posY.x, blockData.m_posY.y + ATLAS_Y_STEP_SIZE,
        blockData.m_posY.x + ATLAS_X_STEP_SIZE, blockData.m_posY.y + ATLAS_Y_STEP_SIZE,
        blockData.m_posY.x + ATLAS_X_STEP_SIZE, blockData.m_posY.y,

        blockData.m_negY.x + ATLAS_X_STEP_SIZE, blockData.m_negY.y,
        blockData.m_negY.x, blockData.m_negY.y,
        blockData.m_negY.x, blockData.m_negY.y + ATLAS_Y_STEP_SIZE,
        blockData.m_negY.x + ATLAS_X_STEP_SIZE, blockData.m_negY.y + ATLAS_Y_STEP_SIZE,

        blockData.m_posX.x + ATLAS_X_STEP_SIZE, blockData.m_posX.y + ATLAS_Y_STEP_SIZE,
        blockData.m_posX.x + ATLAS_X_STEP_SIZE, blockData.m_posX.y,
        blockData.m_posX.x, blockData.m_posX.y,
        blockData.m_posX.x, blockData.m_posX.y + ATLAS_Y_STEP_SIZE,

        blockData.m_negX.x, blockData.m_negX.y + ATLAS_Y_STEP_SIZE,
        blockData.m_negX.x + ATLAS_X_STEP_SIZE, blockData.m_negX.y + ATLAS_Y_STEP_SIZE,
        blockData.m_negX.x + ATLAS_X_STEP_SIZE, blockData.m_negX.y,
        blockData.m_negX.x, blockData.m_negX.y

    };

    for (int i = 0; i < 48; i++)
    {
        buf[i] = baseTexcoords[i];
    }
};