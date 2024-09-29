#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"
#include "Chunk.hpp"
#include "core/Utils.hpp"

class World
{

public:
	std::vector<Chunk*> loadedChunks;
	Chunk* getChunk(Vector3Int pos);
	void addChunk(Chunk* chunk);

	void Init();
	void calcChunks(Vector3Int playerChunkPos);

private:
	void chunksToLoad(Vector3Int playerChunkPos, std::vector<Vector3Int>& chunksToLoad);
};
