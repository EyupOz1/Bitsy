#include "Chunk.hpp"
#include "raylib.h"
#include <iostream>
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
#include "Core/Utils.hpp"
#include "World/Block.hpp"
#include <array>

Chunk::Chunk(Vector3Int pos)
{
	TraceLog(LOG_DEBUG, "New Chunk: %i, %i, %i", ExpandVc3(pos));

	this->position = pos;
	this->blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
	this->genTerrain();
}
Chunk::~Chunk() {}

void Chunk::genTerrain()
{
	if (this->position.y == 0)
	{

		Image noise = GenImagePerlinNoise(CHUNK_SIZE, CHUNK_SIZE, this->position.x, this->position.z, 1);
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				unsigned char height = GetImageColor(noise, i, j).g;

				int x = map(height, 0, 255, 0, CHUNK_SIZE - 1);

				this->setBlock({ i, x, j }, { 2 }, true);
				for (int s = x - 1; s >= 0; s--)
				{
					this->setBlock({ i, s, j }, { 1 }, true);
				}
			}
		}
		UnloadImage(noise);
	}
	else if (this->position.y < 0)
	{
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					this->setBlock({ i, j, k }, { 3 }, true);
				}
			}
		}
	}
}



BlockState Chunk::getBlock(Vector3Int pos)
{
	int index = (static_cast<int>(pos.z) * CHUNK_SIZE * CHUNK_SIZE) + (static_cast<int>(pos.y) * CHUNK_SIZE) + static_cast<int>(pos.x);
	BlockState bl = this->blocks[index];

	return bl;
}

bool Chunk::setBlock(Vector3Int pos, BlockState block, bool shouldReplace)
{
	if (
		pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE || pos.z >= CHUNK_SIZE ||
		pos.x < 0 || pos.y < 0 || pos.z < 0)
	{
		TraceLog(LOG_DEBUG, "On Chunk (%f, %f, %f) cannot set Block %i on (%f, %f, %f)", ExpandVc3(this->position), block.ID, ExpandVc3(pos));
		return false;
	}

	this->blocksPos.push_back(pos);
	int index = (pos.z * CHUNK_SIZE * CHUNK_SIZE) + (pos.y * CHUNK_SIZE) + pos.x;
	this->blocks[index] = block;

	return true;
}

void Chunk::genMesh(std::array<Chunk*, 6> neighbourChunks)
{
	generateChunkMesh(neighbourChunks, this);
	this->status = CHUNK_STATUS_GEN_MODEL;
}
