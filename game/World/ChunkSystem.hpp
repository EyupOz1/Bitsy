#pragma once

#include "World/Chunk.hpp"
#include <vector>
#include <array>
#include "Core/Math/Vector3Int.hpp"
#include <unordered_map>

class ChunkSystem
{
private:
    std::unordered_map<Vector3Int, Chunk *, Vector3Int::ChunkHash> chunks;

public:
    Chunk *getChunk(Vector3Int pos);
    void addChunk(Chunk *newChunk);
    void removeChunk(Vector3Int pos);

    int size();

    std::unordered_map<Vector3Int, Chunk *, Vector3Int::ChunkHash>::const_iterator begin() const { return chunks.cbegin(); }
    std::unordered_map<Vector3Int, Chunk *, Vector3Int::ChunkHash>::const_iterator end() const { return chunks.cend(); }

    std::unordered_map<Vector3Int, Chunk *, Vector3Int::ChunkHash>::iterator begin() { return chunks.begin(); }
    std::unordered_map<Vector3Int, Chunk *, Vector3Int::ChunkHash>::iterator end() { return chunks.end(); }
};