#pragma once

#include "World/Chunk.hpp"
#include <vector>
#include <array>
#include "Core/Math/Vector3Int.hpp"

class ChunkSystem
{
private:
    std::vector<Chunk *> chunks;

public:

    Chunk *getChunk(Vector3Int pos);
    std::array<Chunk *, 6> getChunks(std::array<Vector3Int, 6> &positions);
    void addChunk(Chunk *newChunk);

    int size();

    std::vector<Chunk *>::const_iterator begin() const { return chunks.cbegin(); }
    std::vector<Chunk *>::const_iterator end() const { return chunks.cend(); }

    std::vector<Chunk *>::iterator begin() { return chunks.begin(); }
    std::vector<Chunk *>::iterator end() { return chunks.end(); }
};
