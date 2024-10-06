#include "World.hpp"
#include "Core/Utils.hpp"
#include <vector>
#include "raymath.h"
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
#include <array>
#include <future>
#include <chrono>
void World::Init()
{

}

void World::calcChunks(Vector3Int playerChunkPos)
{
	this->loadedChunksMutex.lock();


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
			Chunk* newChunk = new Chunk(chunksToLoad[i]);
			this->addChunk(newChunk);
		}
	}



	for (int i = 0; i < this->loadedChunks.size(); i++)
	{
		Vector3Int curr = this->loadedChunks[i]->position;
		if (Vector3IntDistance(playerChunkPos, curr) > RENDER_DISTANCE * CHUNK_SIZE)
		{
			this->loadedChunks.erase(this->loadedChunks.begin() + i);
		}
	}


	this->loadedChunksMutex.unlock();
	this->buildMeshes();
}

void World::buildMeshes()
{

	this->loadedChunksMutex.lock();
	auto t1 = std::chrono::high_resolution_clock::now();


	std::vector<std::future<void>> futures;

	for (int i = 0; i < this->loadedChunks.size(); i++)
	{
		Chunk* curr = this->loadedChunks[i];
		if (curr->status != CHUNK_STATUS_GEN_MESH)
		{
			continue;
		}
		std::array<Chunk*, 6> neighbourChunks{
			this->getChunk(Vector3IntAdd(curr->position, {+CHUNK_SIZE, 0, 0})),
			this->getChunk(Vector3IntAdd(curr->position, {-CHUNK_SIZE, 0, 0})),
			this->getChunk(Vector3IntAdd(curr->position, {0, +CHUNK_SIZE, 0})),
			this->getChunk(Vector3IntAdd(curr->position, {0, -CHUNK_SIZE, 0})),
			this->getChunk(Vector3IntAdd(curr->position, {0, 0, +CHUNK_SIZE})),
			this->getChunk(Vector3IntAdd(curr->position, {0, 0, -CHUNK_SIZE})),
		};

		// async
		futures.push_back(std::async(std::launch::async, generateChunkMesh, neighbourChunks, curr));
		
		// sync
		//curr->genMesh(neighbourChunks);


		curr->status = CHUNK_STATUS_GEN_MODEL;
	}

	for (int i = 0; i < futures.size(); i++)
	{
		futures[i].get();
	}


	auto t2 = std::chrono::high_resolution_clock::now();
	auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	TraceLog(LOG_ERROR, "%lld", ms_int.count());
	
	this->loadedChunksMutex.unlock();
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