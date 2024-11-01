
#include "World/ChunkSystem.hpp"
#include "World/Chunk.hpp"
#include <array>

Chunk *ChunkSystem::getChunk(Vector3Int pos)
{
    Chunk *curr = this->chunks[pos];
    return curr; // returns nullptr if not found
}

void ChunkSystem::addChunk(Chunk *newChunk)
{
    this->chunks[newChunk->position] = newChunk;
}

void ChunkSystem::removeChunk(Vector3Int pos)
{
    this->chunks.erase(pos);
}

int ChunkSystem::size()
{
    return this->chunks.size();
}