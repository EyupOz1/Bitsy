#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"
#include "Chunk.hpp"
#include "core/Utils.hpp"
#include <mutex>
#include "Core/Math/ThreadSafeQueue.hpp"
#include "World/ChunkSystem.hpp"

class World
{
public:

	void Init(Texture blockAtlas);
	void Update();
	
	void calcChunks(Vector3Int playerChunkPos);

	ChunkSystem loadedChunks;
	std::vector<Chunk *> calculatingChunks;
	ThreadSafeQueue<Chunk *> finishedChunks;
	std::vector<Chunk *> chunksToDelete;

private:
	void chunksToLoad(Vector3Int playerChunkPos, std::vector<Vector3Int> &chunksToLoad);
	
	Texture atlas;
};
