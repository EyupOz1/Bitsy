#include "World/Chunk.hpp"
#include "World/ChunkSystem.hpp"
#include <array>

Chunk *ChunkSystem::getChunk(Vector2Int pos)
{
    for (int i = 0; i < this->chunks.size(); i++)
    {
        if (this->chunks[i]->position == pos)
        {
            return this->chunks[i];
        }
    }
    return nullptr;
}

template <std::size_t N>
std::array<Chunk *, N> ChunkSystem::getChunks(const std::array<Vector2Int, N> &positions)
{
    std::array<Chunk *, N> resultChunks;

    for (std::size_t i = 0; i < N; i++)
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
    return (int)this->chunks.size();
}

void ChunkSystem::deleteChunk(Vector2Int pos)
{
    this->chunks.erase(
        std::remove_if(this->chunks.begin(), this->chunks.end(), [&pos](Chunk*& elem) {
            return elem->position == pos;
            }),
        this->chunks.end()
    );
}