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

// playerChunkCurrent-, LastPos at max. one Chunk difference
// TODO: Handle case where Chunk velo is 2 chunks away
void World::updateChunks(Vector3Int playerChunkCurrentPos, Vector3Int playerChunkLastPos)
{
	int renderRadius = (RENDER_DISTANCE - 1) / 2;
	int renderRadiusChunks = renderRadius * CHUNK_SIZE;

	Vector3Int newChunksMiddleDir = playerChunkCurrentPos.substract(playerChunkLastPos);
	Vector3Int newChunksMiddleDist = newChunksMiddleDir.scale(renderRadius);

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
			TraceLog(LOG_DEBUG, "curr: %i, %i, %i", ExpandVc3(currPos));

			Chunk *currChunk = this->activeChunks.getChunk(currPos);
			if (currChunk == nullptr)
			{
				Chunk *newChunk = new Chunk(currPos);
				newChunk->status = CHUNK_STATUS_GEN_BLOCKS;
				this->activeChunks.addChunk(newChunk);
				this->chunksToCalculate.enqueue(*newChunk);
			}
		}


}

void World::chunksToLoad(Vector3Int playerChunkPos, std::vector<Vector3Int> &chunksToLoad)
{

	int renderRadius = (RENDER_DISTANCE - 1) / 2;
	chunksToLoad.resize(RENDER_DISTANCE * RENDER_DISTANCE * RENDER_DISTANCE);
	for (int i = -renderRadius; i <= renderRadius; i++)
	{
		for (int j = -renderRadius; j <= renderRadius; j++)
		{
			for (int k = -renderRadius; k <= renderRadius; k++)
			{
				chunksToLoad.push_back(Vector3IntAdd(playerChunkPos, {i * CHUNK_SIZE, j * CHUNK_SIZE, k * CHUNK_SIZE}));
			}
		}
	}
}

void World::Update()
{
	/*
	for (Chunk *loadedChunk : this->loadedChunks)
	{
		Chunk *curr = loadedChunk;
		if (curr->status == CHUNK_STATUS_GEN_MODEL)
		{
			UploadMesh(&curr->mesh, false);
			curr->model = LoadModelFromMesh(curr->mesh);
			curr->model.materials[0].maps[0].texture = this->atlas;
			curr->status = CHUNK_STATUS_RENDER;
		}
		if (curr->status == CHUNK_STATUS_RENDER)
		{
			DrawModel(curr->model, Vec3IntToVec3(curr->position), 1.0f, RAYWHITE);
		}
	}

	bool success = false;
	do
	{
		Chunk *ch;
		success = this->finishedChunks.tryPop(ch);
		if (success)
		{
			this->loadedChunks.addChunk(ch);
		}

	} while (success);
	*/
}
