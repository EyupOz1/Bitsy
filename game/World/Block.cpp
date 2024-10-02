#include "Block.hpp"
#include "raylib.h"


BlockData getBlockData(int BlockID)
{
	switch (BlockID)
	{
	case 1:
		return { "dirt", "Dirt", {3,0},{3,0},{3,0},{3,0},{3,0},{3,0} };
		break;

	case 2:
		return { "grass", "Grass Block", {1, 0}, {1, 0},{2, 0}, {3, 0}, { 1, 0 }, {1,0} };
		break;
	case 3:
		return { "stone", "Stone", {0, 1}, {0, 1},{0, 1}, {0, 1}, { 0, 1 }, {0,1 } };
		break;


	default:
		return { "air", "Air", {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1} };
		break;
	}

}


void getTexCoords(int BlockID, float(&buf)[48])
{
	BlockData block = getBlockData(BlockID);

	float baseTexcoords[] = {
	block.m_posZ.x, block.m_posZ.y + ATLAS_Y_STEP_SIZE,
	block.m_posZ.x + ATLAS_X_STEP_SIZE, block.m_posZ.y + ATLAS_Y_STEP_SIZE,
	block.m_posZ.x + ATLAS_X_STEP_SIZE, block.m_posZ.y,
	block.m_posZ.x, block.m_posZ.y,

	block.m_negZ.x + ATLAS_X_STEP_SIZE, block.m_negZ.y + ATLAS_Y_STEP_SIZE,
	block.m_negZ.x + ATLAS_X_STEP_SIZE, block.m_negZ.y,
	block.m_negZ.x, block.m_negZ.y,
	block.m_negZ.x, block.m_negZ.y + ATLAS_Y_STEP_SIZE,

	block.m_posY.x, block.m_posY.y,
	block.m_posY.x, block.m_posY.y + ATLAS_Y_STEP_SIZE,
	block.m_posY.x + ATLAS_X_STEP_SIZE, block.m_posY.y + ATLAS_Y_STEP_SIZE,
	block.m_posY.x + ATLAS_X_STEP_SIZE, block.m_posY.y,

	block.m_negY.x + ATLAS_X_STEP_SIZE, block.m_negY.y,
	block.m_negY.x, block.m_negY.y,
	block.m_negY.x, block.m_negY.y + ATLAS_Y_STEP_SIZE,
	block.m_negY.x + ATLAS_X_STEP_SIZE, block.m_negY.y + ATLAS_Y_STEP_SIZE,

	block.m_posX.x + ATLAS_X_STEP_SIZE, block.m_posX.y + ATLAS_Y_STEP_SIZE,
	block.m_posX.x + ATLAS_X_STEP_SIZE, block.m_posX.y,
	block.m_posX.x, block.m_posX.y,
	block.m_posX.x, block.m_posX.y + ATLAS_Y_STEP_SIZE,

   block.m_negX.x, block.m_negX.y + ATLAS_Y_STEP_SIZE,
   block.m_negX.x + ATLAS_X_STEP_SIZE, block.m_negX.y + ATLAS_Y_STEP_SIZE,
   block.m_negX.x + ATLAS_X_STEP_SIZE, block.m_negX.y,
   block.m_negX.x, block.m_negX.y

	};

	for (int i = 0; i < 48; i++)
	{
		buf[i] = baseTexcoords[i];
	}
}