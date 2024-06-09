#pragma once

#include <string>
#include "Block.hpp"
#include "raylib.h"
#include <vector>
#include "Defines.hpp"

class BlockData
{
public:
    std::string m_blockName = "debug";
    std::string m_screenName = "Debug Block";
    Vector2 m_posZ;
    Vector2 m_negZ;
    Vector2 m_posY;
    Vector2 m_negY;
    Vector2 m_posX;
    Vector2 m_negX;

    BlockData(std::string blockName, std::string screenName, Vector2 posZ, Vector2 negZ, Vector2 posY, Vector2 negY, Vector2 posX, Vector2 negX)
        : m_blockName(blockName), m_screenName(screenName),
          m_posZ(posZ), m_negZ(negZ), m_posY(posY), m_negY(negY), m_posX(posX), m_negX(negX)
    {
    }

    static void getTexcoords(Block &block, float (&buf)[48]);
};