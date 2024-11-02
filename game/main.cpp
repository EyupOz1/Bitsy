#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include <vector>
#include "Player.hpp"
#include "Core/Math/Vector3Int.hpp"
#include <thread>
#include "World/World.hpp"
#include "Core/Defines.hpp"
#include <Core/Math/ThreadSafeQueue.hpp>
#include <optional>
#include <iostream>

Player player;
Texture atlas;
World world;

bool killThread = 0;
std::thread ChunkGenThread;

int playerChunkUpdates = 0;

void chunkGenThreadFunction()
{
	while (!killThread)
	{
		if (!world.chunksToCalculate.empty())
		{
			std::optional<Chunk> item = world.chunksToCalculate.tryDequeue();
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

				world.finishedChunks.enqueue(chunk);
			}
		}
	}
}

void setup()
{
	player.Init();
	world.Init(LoadTexture(PATH_TEXTURES_ATLAS));
	int renderRadius = (RENDER_DISTANCE - 1) / 2;
	for (int i = -renderRadius; i <= renderRadius; i++)
	{
		for (int j = -renderRadius; j <= renderRadius; j++)
		{
			for (int k = -renderRadius; k <= renderRadius; k++)
			{
				Vector3Int currPos = {i * CHUNK_SIZE, j * CHUNK_SIZE, k * CHUNK_SIZE};
				currPos = currPos.add(player.currentChunkPos);
				Chunk *currChunk = world.activeChunks.getChunk(currPos);
				if (currChunk == nullptr)
				{
					Chunk *newChunk = new Chunk(currPos);
					newChunk->status = CHUNK_STATUS_GEN_BLOCKS;
					world.activeChunks.addChunk(newChunk);
					world.chunksToCalculate.enqueue(*newChunk);
				}
			}
		}
	}
	ChunkGenThread = std::thread(chunkGenThreadFunction);
}

Vector3Int lastUpdatedChunk = {0, 0, 0}; // TODO: Dont forget to make Player Spawn a variable
void update()
{
	bool playerMovedToNewChunk = false;
	player.Update();

	if (!(player.currentChunkPos == lastUpdatedChunk))
	{
		world.updateChunks(player.currentChunkPos, lastUpdatedChunk);
		lastUpdatedChunk = player.currentChunkPos;
	}

	for (int i = 0; i < 3; i++)
	{
		std::optional<Chunk> item = world.finishedChunks.tryDequeue();
		if (item)
		{
			Chunk chunk = item.value();
			Chunk *curr = world.activeChunks.getChunk(chunk.position);
			if (curr != nullptr)
			{
				*curr = chunk;
			}
		}
	}

	for (auto it = world.activeChunks.begin(); it != world.activeChunks.end(); ++it)
	{
		Chunk *curr = it->second;
		if (curr->status == CHUNK_STATUS_GEN_MODEL)
		{
			UploadMesh(&curr->mesh, false);
			curr->model = LoadModelFromMesh(curr->mesh);
			curr->model.materials[0].maps[0].texture = world.atlas;
			curr->status = CHUNK_STATUS_RENDER;
		}
		if (curr->status == CHUNK_STATUS_RENDER)
		{
			DrawModel(curr->model, curr->position.toVector3(), 1.0f, RAYWHITE);
		}

		DrawSphere({0, 0, 0}, 5.0f, BLACK);
	}
}
void ui()
{
	int y = -20;
	int step = 20;
	DrawText(TextFormat("%i", GetFPS()), 0, y += step, 20, BLACK);
	DrawText(TextFormat("playerPos: (%f, %f, %f)", ExpandVc3(player.position)), 0, y += step, 20, BLACK);
	DrawText(TextFormat("playerChunkPos: (%i, %i, %i)", ExpandVc3(player.currentChunkPos)), 0, y += step, 20, BLACK);
	DrawText(TextFormat("activeChunksSize: (%i)", world.activeChunks.size()), 0, y += step, 20, BLACK);
	DrawText(TextFormat("chunksToCalculateSize: (%i)", world.chunksToCalculate.size()), 0, y += step, 20, BLACK);
	DrawText(TextFormat("finishedChunksSize: (%i)", world.finishedChunks.size()), 0, y += step, 20, BLACK);
}

int main(void)
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 720, "Bitsy");
	DisableCursor();
	SetTargetFPS(144);
	SetTraceLogLevel(LOG_ALL);

	setup();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		BeginMode3D(player.camera);
		update();
		EndMode3D();

		ui();

		EndDrawing();
	}
	killThread = 1;
	ChunkGenThread.join();
	CloseWindow();

	return 0;
}
