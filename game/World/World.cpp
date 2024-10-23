#include "World.hpp"
#include "Core/Utils.hpp"
#include <vector>
#include "raymath.h"
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
#include <array>
#include <future>
#include <chrono>

void World::Init(Texture blockAtlas)
{
	this->atlas = blockAtlas;
}

void World::calcChunks(Vector3Int playerChunkPos)
{

	std::vector<Vector3Int> chunksToLoad;
	this->chunksToLoad(playerChunkPos, chunksToLoad);

	for (int i = 0; i < chunksToLoad.size(); i++)
	{
		bool alreadyExists = false;
		for (int j = 0; j < this->calculatingChunks.size(); j++)
		{
			if (Vector3IntCompare(chunksToLoad[i], this->calculatingChunks[j]->position))
			{
				alreadyExists = true;
				break;
			}
		}

		if (!alreadyExists)
		{
			for (Chunk *loadedChunk : this->loadedChunks)
			{
				if (Vector3IntCompare(chunksToLoad[i], loadedChunk->position))
				{
					alreadyExists = true;
					break;
				}
			}
		}



		if (!alreadyExists)
		{
			Chunk *newChunk = new Chunk(chunksToLoad[i]);
			this->calculatingChunks.push_back(newChunk);
		}
	}
}

void World::chunksToLoad(Vector3Int playerChunkPos, std::vector<Vector3Int> &chunksToLoad)
{

	int renderRadius = (RENDER_DISTANCE - 1) / 2;
	for (int i = -renderRadius; i <= renderRadius; i++)
	{
		for (int j = -renderRadius; j <= renderRadius; j++)
		{
			for (int k = -renderRadius; k <= renderRadius; k++)
			{
				chunksToLoad.push_back(Vector3IntAdd(playerChunkPos, {i * CHUNK_SIZE, j * CHUNK_SIZE, k * CHUNK_SIZE}));
			}
		}
	}
}

void World::Update()
{
	for (Chunk *loadedChunk : this->loadedChunks)
	{
		Chunk *curr = loadedChunk;
		if (curr->status == CHUNK_STATUS_GEN_MODEL)
		{
			UploadMesh(&curr->mesh, false);
			curr->model = LoadModelFromMesh(curr->mesh);
			curr->model.materials[0].maps[0].texture = this->atlas;
			curr->status = CHUNK_STATUS_RENDER;
		}
		if (curr->status == CHUNK_STATUS_RENDER)
		{
			DrawModel(curr->model, Vec3IntToVec3(curr->position), 1.0f, RAYWHITE);
		}
	}

	bool success = false;
	do
	{
		Chunk *ch;
		success = this->finishedChunks.tryPop(ch);
		if (success)
		{
			this->loadedChunks.addChunk(ch);
		}

	} while (success);
}
