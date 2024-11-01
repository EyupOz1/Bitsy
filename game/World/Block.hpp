#pragma once

#include <vector>
#include "string"
#include "raylib.h"
#include "Core/Defines.hpp"

class BlockData {
public:
	std::string m_name;
	std::string m_screenName;

	Vector2 m_posZ;
	Vector2 m_negZ;
	Vector2 m_posY;
	Vector2 m_negY;
	Vector2 m_posX;
	Vector2 m_negX;

	BlockData(std::string name, std::string screenName, Vector2 posZ, Vector2 negZ, Vector2 posY, Vector2 negY, Vector2 posX, Vector2 negX)
	{
		m_name = name;
		m_screenName = screenName;
		m_posZ = { posZ.x * ATLAS_X_STEP_SIZE, posZ.y * ATLAS_Y_STEP_SIZE };
		m_negZ = { negZ.x * ATLAS_X_STEP_SIZE, negZ.y * ATLAS_Y_STEP_SIZE };
		m_posY = { posY.x * ATLAS_X_STEP_SIZE, posY.y * ATLAS_Y_STEP_SIZE };
		m_negY = { negY.x * ATLAS_X_STEP_SIZE, negY.y * ATLAS_Y_STEP_SIZE };
		m_posX = { posX.x * ATLAS_X_STEP_SIZE, posX.y * ATLAS_Y_STEP_SIZE };
		m_negX = { negX.x * ATLAS_X_STEP_SIZE, negX.y * ATLAS_Y_STEP_SIZE };
	}
};

// State a block instance has like orientation
class BlockState
{
public:
	int ID;
};

void getTexCoords(int BlockID, float(&buf)[48]);
