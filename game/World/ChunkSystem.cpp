
#include "World/ChunkSystem.hpp"
#include "World/Chunk.hpp"
#include <array>

Chunk *ChunkSystem::getChunk(Vector3Int pos)
{
    for (int i = 0; i < this->chunks.size(); i++)
    {
        if (Vector3IntCompare(this->chunks[i]->position, pos))
        {
            return this->chunks[i];
        }
    }
    return nullptr;
}
std::array<Chunk *, 6> ChunkSystem::getChunks(std::array<Vector3Int, 6> &positions)
{
    std::array<Chunk *, 6> resultChunks;

    for (int i = 0; i < 6; i++)
    {
        Chunk *chunk = this->getChunk(positions[i]);
        resultChunks[i] = chunk;
    }

    return resultChunks;
}
void ChunkSystem::addChunk(Chunk *newChunk)
{
    this->chunks.push_back(newChunk);
}

int ChunkSystem::size()
{
    return this->chunks.size();
}