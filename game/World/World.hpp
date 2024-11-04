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
	void updateChunks(Vector3Int playerChunkCurrentPos, Vector3Int playerChunkLastPos);

	void processChunkCalc();

	ChunkSystem activeChunks;

	ThreadSafeQueue<Chunk> chunksToCalculate;
	ThreadSafeQueue<Chunk> finishedChunks;

	ThreadSafeQueue<Chunk*> chunksToDelete;



	Texture atlas;
};
