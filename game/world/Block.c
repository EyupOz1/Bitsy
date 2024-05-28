#include "Block.h"


void block_setTexCoords(Block *block, float *buf)
{

    BlockData blockData = GLOBAL.blockDataList[block->BlockID];

    float baseTexcoords[] = {
        blockData.posZ.x, blockData.posZ.y + ATLAS_Y_STEP_SIZE,
        blockData.posZ.x + ATLAS_X_STEP_SIZE, blockData.posZ.y + ATLAS_Y_STEP_SIZE,
        blockData.posZ.x + ATLAS_X_STEP_SIZE, blockData.posZ.y,
        blockData.posZ.x, blockData.posZ.y,

        blockData.negZ.x + ATLAS_X_STEP_SIZE, blockData.negZ.y + ATLAS_Y_STEP_SIZE,
        blockData.negZ.x + ATLAS_X_STEP_SIZE, blockData.negZ.y,
        blockData.negZ.x, blockData.negZ.y,
        blockData.negZ.x, blockData.negZ.y + ATLAS_Y_STEP_SIZE,

        blockData.posY.x, blockData.posY.y,
        blockData.posY.x, blockData.posY.y + ATLAS_Y_STEP_SIZE,
        blockData.posY.x + ATLAS_X_STEP_SIZE, blockData.posY.y + ATLAS_Y_STEP_SIZE,
        blockData.posY.x + ATLAS_X_STEP_SIZE, blockData.posY.y,

        blockData.negY.x + ATLAS_X_STEP_SIZE, blockData.negY.y,
        blockData.negY.x, blockData.negY.y,
        blockData.negY.x, blockData.negY.y + ATLAS_Y_STEP_SIZE,
        blockData.negY.x + ATLAS_X_STEP_SIZE, blockData.negY.y + ATLAS_Y_STEP_SIZE,

        blockData.posX.x + ATLAS_X_STEP_SIZE, blockData.posX.y + ATLAS_Y_STEP_SIZE,
        blockData.posX.x + ATLAS_X_STEP_SIZE, blockData.posX.y,
        blockData.posX.x, blockData.posX.y,
        blockData.posX.x, blockData.posX.y + ATLAS_Y_STEP_SIZE,

        blockData.negX.x, blockData.negX.y + ATLAS_Y_STEP_SIZE,
        blockData.negX.x + ATLAS_X_STEP_SIZE, blockData.negX.y + ATLAS_Y_STEP_SIZE,
        blockData.negX.x + ATLAS_X_STEP_SIZE, blockData.negX.y,
        blockData.negX.x, blockData.negX.y

    };

    for (int i = 0; i < 48; i++)
    {
        buf[i] = baseTexcoords[i];
    }
}