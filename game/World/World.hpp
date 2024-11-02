#pragma once

#include "raylib.h"
#include <vector>
#include "Block.hpp"
#include "Chunk.hpp"
#include "core/Utils.hpp"
#include <mutex>
#include "World/ChunkSystem.hpp"
#include <Core/Math/ThreadSafeQueue.hpp>

class World
{
public:

	void Init(Texture blockAtlas);
	void Update();
	
	ChunkSystem activeChunks;
	
	ThreadSafeQueue<Chunk> chunksToCalculate;
	ThreadSafeQueue<Chunk> finishedChunks;

	void updateChunks(Vector3Int playerChunkCurrentPos, Vector3Int playerChunkLastPos);


	static void chunksToLoad(Vector3Int playerChunkPos, std::vector<Vector3Int> &chunksToLoad);
	
	Texture atlas;
};
