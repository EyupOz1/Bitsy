#include "World/World.hpp"
#include <future>
#include <vector>

void World::Init(Texture blockAtlas)
{
	this->atlas = blockAtlas;
}

Chunk* generateChunk(Chunk* chunk) {
	chunk->Init();
	chunk->genTerrain();
	chunk->genMesh();
	return chunk;
}

void World::Update(Vector2Int playerChunkPos)
{
	std::vector<Vector2Int> validChunks;
	for (int i = playerChunkPos.x - CHUNK_SIZE_XZ * RENDER_DISTANCE; i <= playerChunkPos.x + CHUNK_SIZE_XZ * RENDER_DISTANCE; i+= CHUNK_SIZE_XZ)
	{
		for (int j = playerChunkPos.y - CHUNK_SIZE_XZ * RENDER_DISTANCE; j <= playerChunkPos.y + CHUNK_SIZE_XZ * RENDER_DISTANCE; j += CHUNK_SIZE_XZ)
		{
			validChunks.push_back({ i, j });
			if (this->activeChunks.getChunk({i, j}) == nullptr && this->chunksToCreate.getChunk({i, j}) == nullptr && this->calculatingChunks.getChunk({ i, j }) == nullptr)
			{
				this->chunksToCreate.addChunk(new Chunk({i, j}));
			}
		}
	}


	std::vector<Chunk*> processedChunks;

	for (Chunk* ch : this->chunksToCreate)
	{
		futures.push_back(std::async(std::launch::async, generateChunk, ch));
		processedChunks.push_back(ch);
		this->calculatingChunks.addChunk(ch);
	}
	for (Chunk* ch : processedChunks)
	{
		this->chunksToCreate.deleteChunk(ch->position);
	}
}


void World::processCalculatedChunks()
{
	std::vector<int> processedChunks;

	for (int i = 0; i < this->futures.size(); i++)
	{
		if (this->futures[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready)
		{
			processedChunks.push_back(i);
		}
	}
	for (auto it = processedChunks.rbegin(); it != processedChunks.rend(); ++it)
	{
		Chunk* completedChunk = this->futures[*it].get();

		this->calculatingChunks.deleteChunk(completedChunk->position);
		this->activeChunks.addChunk(completedChunk);
		this->futures.erase(this->futures.begin() + *it);
	}
}