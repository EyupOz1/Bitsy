#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"
#include "Chunk.hpp"
#include "core/Utils.hpp"
#include <mutex>

class World
{

public:
	std::mutex loadedChunksMutex;
	std::vector<Chunk*> loadedChunks;


	Chunk* getChunk(Vector3Int pos);
	void addChunk(Chunk* chunk);

	void Init();
	void calcChunks(Vector3Int playerChunkPos);
	void buildMeshes();



	std::vector<Chunk*> chunksToDelete;

private:
	void chunksToLoad(Vector3Int playerChunkPos, std::vector<Vector3Int>& chunksToLoad);
};
