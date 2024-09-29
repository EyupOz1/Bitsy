#include "World/World.hpp"
#include "World/Chunk.hpp"
#include "Core/Math/Vector3Int.hpp"

Chunk* World::getChunk(Vector3Int pos)
{
	for (int i = 0; i < this->loadedChunks.size(); i++)
	{
		if (Vector3IntCompare(this->loadedChunks[i]->position, pos))
		{
			return this->loadedChunks[i];
		}
	}
}
void World::addChunk(Chunk* chunk)
{
	this->loadedChunks.push_back(chunk);
}
