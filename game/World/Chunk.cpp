#include "Chunk.hpp"
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
#include "Core/Utils.hpp"
#include "raylib.h"
#include "World/Block.hpp"

Chunk::Chunk(Vector2Int pos)
{
	this->position = pos;
	this->validModel = 0;
}

void Chunk::Init()
{
	// TraceLog(LOG_DEBUG, "New Chunk: %i, %i, %i", ExpandVc3(this->position));

	this->blocks.resize(CHUNK_SIZE_XZ * CHUNK_SIZE_Y * CHUNK_SIZE_XZ);
}

void Chunk::genTerrain()
{
	/*
	Image noise = GenImagePerlinNoise(CHUNK_SIZE_XZ, CHUNK_SIZE_XZ, this->position.x, this->position.y, 1);
	for (int i = 0; i < CHUNK_SIZE_XZ; i++)
	{
		for (int j = 0; j < CHUNK_SIZE_XZ; j++)
		{
			unsigned char height = GetImageColor(noise, i, j).g / 2;
			int x = map(height, 0, 255, 0, CHUNK_SIZE_Y - 1);

			this->setBlock({i, x, j}, {2}, true);
			for (int s = x - 1; s >= 0; s--)
			{
				this->setBlock({i, s, j}, {1}, true);
			}
		}
	}
	UnloadImage(noise);
	*/
	for (int i = 0; i < CHUNK_SIZE_XZ; i++)
	{
		for (int j = 0; j < CHUNK_SIZE_XZ; j++)
		{

			this->setBlock({ i, 0, j }, { 2 }, true);
		}
	}
}

void Chunk::genMesh()
{
	this->mesh = generateChunkMesh(this);
}

BlockState Chunk::getBlock(Vector3Int pos)
{
	int index = pos.x * CHUNK_SIZE_XZ * CHUNK_SIZE_Y + pos.y * CHUNK_SIZE_XZ + pos.z;
	if (index < 0 && index >= CHUNK_SIZE_XZ * CHUNK_SIZE_Y * CHUNK_SIZE_XZ)
	{
		TraceLog(LOG_DEBUG, "Chunk cant get Block in Chunk %i %i %i", ExpandVc3(pos));
	}

	BlockState bl = this->blocks[index];

	return bl;
}

bool Chunk::setBlock(Vector3Int pos, BlockState block, bool shouldReplace)
{
	if (
		pos.x >= CHUNK_SIZE_XZ || pos.y >= CHUNK_SIZE_Y || pos.z >= CHUNK_SIZE_XZ ||
		pos.x < 0 || pos.y < 0 || pos.z < 0)
	{
		TraceLog(LOG_DEBUG, "On Chunk (%i, %i) cannot set Block %i on (%i, %i, %i)", ExpandVc2(this->position), block.ID, ExpandVc3(pos));
		return false;
	}

	this->blocksPos.push_back(pos);
	int index = pos.x * CHUNK_SIZE_XZ * CHUNK_SIZE_Y + pos.y * CHUNK_SIZE_XZ + pos.z;
	this->blocks[index] = block;

	return true;
}
