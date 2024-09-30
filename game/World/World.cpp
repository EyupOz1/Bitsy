#include "World.hpp"
#include "Core/Utils.hpp"
#include <vector>
#include "raymath.h"
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
void World::Init()
{
}

void World::calcChunks(Vector3Int playerChunkPos)
{
	std::vector<Vector3Int> chunksToLoad;
	this->chunksToLoad(playerChunkPos, chunksToLoad);

	for (int i = 0; i < chunksToLoad.size(); i++)
	{
		bool alreadyExists = false;
		for (int j = 0; j < this->loadedChunks.size(); j++)
		{
			if (Vector3IntCompare(chunksToLoad[i], this->loadedChunks[j]->position))
			{
				alreadyExists = true;
				break;
			}
		}
		if (!alreadyExists)
		{
			// Chunk.create()


			Chunk* newChunk = new Chunk();
			newChunk->Init(chunksToLoad[i]);
			this->addChunk(newChunk);
		}
	}

	for (int i = 0; i < this->loadedChunks.size(); i++)
	{

		if (this->loadedChunks[i]->status.load() == CHUNK_CreateMesh)
		{
			this->loadedChunks[i]->status = CHUNK_CreatingMesh;
			this->loadedChunks[i]->generateMesh();
			this->loadedChunks[i]->status = CHUNK_CreateModel;
		}

		bool exists = false;
		for (int j = 0; j < chunksToLoad.size(); j++)
		{
			if (Vector3IntCompare(chunksToLoad[j], this->loadedChunks[i]->position))
			{
				exists = true;
				break;
			}
		}
		if (!exists)
		{
			//this->chunksToDelete.push_back(this->loadedChunks[i]);
			//this->loadedChunks.erase(this->loadedChunks.begin() + i);
		}
	}
}

void World::chunksToLoad(Vector3Int playerChunkPos, std::vector<Vector3Int>& chunksToLoad)
{

	int renderRadius = (RENDER_DISTANCE - 1) / 2;
	for (int i = -renderRadius; i <= renderRadius; i++)
	{
		for (int j = -renderRadius; j <= renderRadius; j++)
		{
			for (int k = -renderRadius; k <= renderRadius; k++)
			{
				chunksToLoad.push_back(Vector3IntAdd(playerChunkPos, { i * CHUNK_SIZE, j * CHUNK_SIZE, k * CHUNK_SIZE }));
			}
		}
	}
}