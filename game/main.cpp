#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include <vector>
#include "Player.hpp"
#include "Core/Math/Vector3Int.hpp"
#include <thread>
#include "World/World.hpp"
#include "Core/Defines.hpp"

Player player;
Texture atlas;
World world;

bool killThread = 0;
std::thread ChunkGenThread;

int playerChunkUpdates = 0;

void chunkGenThreadFunction()
{
	Vector3Int lastUpdatedChunk = {-1, -1, -1}; // only calcChunks if player.currentChunk changed
	while (!killThread)
	{
		if (!Vector3IntCompare(player.currentChunkPos, lastUpdatedChunk))
		{
			world.calcChunks(player.currentChunkPos);
			lastUpdatedChunk = player.currentChunkPos;
		}

		if (!world.calculatingChunks.empty())
		{

			Chunk *curr = world.calculatingChunks.back();
			std::array<Vector3Int, 6> neighbourChunksPos{
				Vector3IntAdd(curr->position, {+CHUNK_SIZE, 0, 0}),
				Vector3IntAdd(curr->position, {-CHUNK_SIZE, 0, 0}),
				Vector3IntAdd(curr->position, {0, +CHUNK_SIZE, 0}),
				Vector3IntAdd(curr->position, {0, -CHUNK_SIZE, 0}),
				Vector3IntAdd(curr->position, {0, 0, +CHUNK_SIZE}),
				Vector3IntAdd(curr->position, {0, 0, -CHUNK_SIZE}),
			};
			std::array<Chunk *, 6> neighbourChunks = world.loadedChunks.getChunks(neighbourChunksPos);
			curr->genMesh(neighbourChunks);

			world.finishedChunks.push(curr);
			world.calculatingChunks.pop_back();
		}
	}
}

void setup()
{
	player.Init();
	world.Init(LoadTexture(PATH_TEXTURES_ATLAS));
	ChunkGenThread = std::thread(chunkGenThreadFunction);
}

void update()
{
	player.Update();
	world.Update();

}

void ui()
{
	int y = -20;
	int step = 20;
	DrawText(TextFormat("%i", GetFPS()), 0, y += step, 20, BLACK);
	DrawText(TextFormat("playerPos: (%f, %f, %f)", ExpandVc3(player.position)), 0, y += step, 20, BLACK);
	DrawText(TextFormat("playerChunkPos: (%i, %i, %i)", ExpandVc3(player.currentChunkPos)), 0, y += step, 20, BLACK);
	DrawText(TextFormat("loadedChunksSize: (%i)", world.loadedChunks.size()), 0, y += step, 20, BLACK);
	DrawText(TextFormat("bufferChunksSize: (%i)", world.calculatingChunks.size()), 0, y += step, 20, BLACK);
}

int main(void)
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 720, "Bitsy");
	DisableCursor();
	SetTargetFPS(144);
	SetTraceLogLevel(LOG_ERROR);

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
