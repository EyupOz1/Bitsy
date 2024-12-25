#pragma once

#include "Chunk.hpp"
#include "raylib.h"
#include "World/ChunkSystem.hpp"
#include <future>
#include <vector>

class World
{
public:
	std::vector<std::future<Chunk*>> futures;


	void Init(Texture blockAtlas);
	void Update(Vector2Int playerChunkPos);
	void processCalculatedChunks();


	ChunkSystem chunksToCreate;
	ChunkSystem calculatingChunks;
    ChunkSystem activeChunks;
    ChunkSystem chunksToDelete;
	Texture atlas;

};