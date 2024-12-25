#pragma once

#include "Core/Math/Vector2Int.hpp"
#include "World/Chunk.hpp"
#include <array>
#include <vector>

class ChunkSystem
{
private:
    std::vector<Chunk *> chunks;

public:
    Chunk *getChunk(Vector2Int pos);

    template <std::size_t N>
    std::array<Chunk *, N> getChunks(const std::array<Vector2Int, N> &positions);

    void addChunk(Chunk *newChunk);
    void deleteChunk(Vector2Int pos);

    int size();

    std::vector<Chunk *>::const_iterator begin() const { return chunks.cbegin(); }
    std::vector<Chunk *>::const_iterator end() const { return chunks.cend(); }

    std::vector<Chunk *>::iterator begin() { return chunks.begin(); }
    std::vector<Chunk *>::iterator end() { return chunks.end(); }
};