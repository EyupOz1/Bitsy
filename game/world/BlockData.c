#include "BlockData.h"

void blockData_init()
{
    GLOBAL.blockDataList[1] = (BlockData){
        .blockName = "debug",
        .screenName = "Debug Block",
        .posZ = {1 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .negZ = {1 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .posY = {2 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .negY = {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .posX = {1 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .negX = {1 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
    };
    GLOBAL.blockDataList[2] = (BlockData){
        .blockName = "dirt",
        .screenName = "Dirt",
        .posZ = {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .negZ = {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .posY = {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .negY = {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .posX = {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
        .negX = {3 * ATLAS_X_STEP_SIZE, 0 * ATLAS_Y_STEP_SIZE},
    };
}