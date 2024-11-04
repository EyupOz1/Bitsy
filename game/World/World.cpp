#include "World.hpp"
#include "Core/Utils.hpp"
#include <vector>
#include "raymath.h"
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
#include <array>
#include <future>
#include <chrono>

void World::Init(Texture blockAtlas)
{
	this->atlas = blockAtlas;
}

void World::processChunkCalc()
{
	if (!this->chunksToCalculate.empty())
	{
		std::optional<Chunk> item = this->chunksToCalculate.tryDequeue();
		if (item)
		{
			Chunk chunk = item.value();
			if (chunk.status == CHUNK_STATUS_GEN_BLOCKS)
			{
				chunk.Init();
				chunk.genTerrain();
				chunk.status = CHUNK_STATUS_GEN_MESH;
			}

			if (chunk.status == CHUNK_STATUS_GEN_MESH)
			{
				chunk.genMesh();
				chunk.status = CHUNK_STATUS_GEN_MODEL;
			}

			this->finishedChunks.enqueue(chunk);
		}
	}
}

// playerChunkCurrent-, LastPos at max. one Chunk difference
// TODO: Handle case where Chunk velo is 2 chunks away
void World::updateChunks(Vector3Int playerChunkCurrentPos, Vector3Int playerChunkLastPos)
{

	int renderRadius = (RENDER_DISTANCE - 1) / 2;
	int renderRadiusChunks = renderRadius * CHUNK_SIZE;

	Vector3Int newChunksMiddleDir = playerChunkCurrentPos.substract(playerChunkLastPos);
	Vector3Int newChunksMiddleDist = newChunksMiddleDir.scale(renderRadius);

	if (abs(newChunksMiddleDir.x + newChunksMiddleDir.y + newChunksMiddleDir.z) == CHUNK_SIZE)
	{
		TraceLog(LOG_DEBUG, "Unexpected Chunk Movement");
	}

	Vector3Int unsignedMask = {newChunksMiddleDir.x != 0, newChunksMiddleDir.y != 0, newChunksMiddleDir.z != 0}; // 1 = new Chunks in that direction
	Vector3Int unsignedInvertedMask = {!unsignedMask.x, !unsignedMask.y, !unsignedMask.z};

	Vector3Int newChunkMiddleToCornerDir = unsignedInvertedMask.scale(renderRadiusChunks);
	Vector3Int NewChunkMiddlePos = playerChunkCurrentPos.add(newChunksMiddleDist);

	Vector3Int playerNewChunkCorner1Pos = NewChunkMiddlePos.add(newChunkMiddleToCornerDir);
	Vector3Int playerNewChunkCorner2Pos = NewChunkMiddlePos.substract(newChunkMiddleToCornerDir);

	TraceLog(LOG_DEBUG, "updateChunks");
	TraceLog(LOG_DEBUG, "currentChunkPos: %i, %i, %i, lastChunkPos: %i, %i, %i", ExpandVc3(playerChunkCurrentPos), ExpandVc3(playerChunkLastPos));
	TraceLog(LOG_DEBUG, "newChunksMiddleDir: %i, %i, %i, newChunksMiddleDist: %i, %i, %i", ExpandVc3(newChunksMiddleDir), ExpandVc3(newChunksMiddleDist));
	TraceLog(LOG_DEBUG, "unsignedMask: %i, %i, %i, unsignedInvertedMask: %i, %i, %i", ExpandVc3(unsignedMask), ExpandVc3(unsignedInvertedMask));
	TraceLog(LOG_DEBUG, "newChunkMiddleToCornerDir: %i, %i, %i, NewChunkMiddlePos: %i, %i, %i", ExpandVc3(newChunkMiddleToCornerDir), ExpandVc3(NewChunkMiddlePos));
	TraceLog(LOG_DEBUG, "playerNewChunkCorner1Pos: %i, %i, %i, playerNewChunkCorner2Pos: %i, %i, %i", ExpandVc3(playerNewChunkCorner1Pos), ExpandVc3(playerNewChunkCorner2Pos));

	// To get the other to values to know what to iterate over
	Vector2 iterator1 = filterNonZeroComponent(playerNewChunkCorner1Pos.multiply(unsignedInvertedMask));
	Vector2 iterator2 = filterNonZeroComponent(playerNewChunkCorner2Pos.multiply(unsignedInvertedMask));

	for (int i = iterator2.x; i <= iterator1.x; i += CHUNK_SIZE)
		for (int j = iterator2.y; j <= iterator1.y; j += CHUNK_SIZE)
		{
			Vector3Int currPos = {0, 0, 0};
			if (unsignedInvertedMask.x == 0)
			{
				currPos = currPos.add({NewChunkMiddlePos.x, i, j});
			}
			else if (unsignedInvertedMask.y == 0)
			{
				currPos = currPos.add({i, NewChunkMiddlePos.y, j});
			}
			else if (unsignedInvertedMask.z == 0)
			{
				currPos = currPos.add({i, j, NewChunkMiddlePos.z});
			}
			else
			{
				throw std::invalid_argument("Exactly one component must be zero.");
			}
			// TraceLog(LOG_DEBUG, "curr: %i, %i, %i", ExpandVc3(currPos));

			Chunk *currChunk = this->activeChunks.getChunk(currPos);
			if (currChunk == nullptr)
			{
				Chunk *newChunk = new Chunk(currPos);
				newChunk->status = CHUNK_STATUS_GEN_BLOCKS;
				this->activeChunks.addChunk(newChunk);
				this->chunksToCalculate.enqueue(*newChunk);
			}
		}

	// Chunks to delete

	Vector3Int oldChunksMiddleDir = playerChunkLastPos.substract(playerChunkCurrentPos);
	Vector3Int oldChunksMiddleDist = oldChunksMiddleDir.scale(renderRadius);

	Vector3Int oldChunkMiddleToCornerDir = unsignedInvertedMask.scale(renderRadiusChunks);
	Vector3Int oldChunkMiddlePos = playerChunkLastPos.add(oldChunksMiddleDist);

	Vector3Int playerOldChunkCorner1Pos = oldChunkMiddlePos.add(oldChunkMiddleToCornerDir);
	Vector3Int playerOldChunkCorner2Pos = oldChunkMiddlePos.substract(oldChunkMiddleToCornerDir);

	Vector2 olditerator1 = filterNonZeroComponent(playerOldChunkCorner1Pos.multiply(unsignedInvertedMask));
	Vector2 olditerator2 = filterNonZeroComponent(playerOldChunkCorner2Pos.multiply(unsignedInvertedMask));

	for (int i = olditerator2.x; i <= olditerator1.x; i += CHUNK_SIZE)
		for (int j = olditerator2.y; j <= olditerator1.y; j += CHUNK_SIZE)
		{
			Vector3Int currPos = {0, 0, 0};
			if (unsignedInvertedMask.x == 0)
			{
				currPos = currPos.add({oldChunkMiddlePos.x, i, j});
			}
			else if (unsignedInvertedMask.y == 0)
			{
				currPos = currPos.add({i, oldChunkMiddlePos.y, j});
			}
			else if (unsignedInvertedMask.z == 0)
			{
				currPos = currPos.add({i, j, oldChunkMiddlePos.z});
			}
			else
			{
				throw std::invalid_argument("Exactly one component must be zero.");
			}
			TraceLog(LOG_DEBUG, "curr: %i, %i, %i", ExpandVc3(currPos));
			Chunk *currChunk = this->activeChunks.getChunk(currPos);
			this->chunksToDelete.enqueue(currChunk);
			this->activeChunks.removeChunk(currPos);
		}
}

void World::Update()
{
}
