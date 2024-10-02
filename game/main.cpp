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
	Vector3Int lastUpdatedChunk = { -1, -1, -1 }; // only calcChunks if player.currentChunk changed
	while (!killThread)
	{
		if (!Vector3IntCompare(player.currentChunkPos, lastUpdatedChunk))
		{
			world.calcChunks(player.currentChunkPos);
			lastUpdatedChunk = player.currentChunkPos;
		}
	}
}

void setup()
{
	player.Init();
	atlas = LoadTexture(PATH_TEXTURES_ATLAS);
	ChunkGenThread = std::thread(chunkGenThreadFunction);
	
}

void update()
{
	player.Update();
	world.loadedChunksMutex.lock();
	for (int i = 0; i < world.loadedChunks.size(); i++)
	{
		Chunk* curr = world.loadedChunks[i];
		if (curr->status == CHUNK_STATUS_GEN_MODEL)
		{
			UploadMesh(&curr->mesh, false);
			curr->model = LoadModelFromMesh(curr->mesh);
			curr->model.materials[0].maps[0].texture = atlas;
			curr->status = CHUNK_STATUS_RENDER;
		}
		if (curr->status == CHUNK_STATUS_RENDER)
		{
			DrawModel(curr->model, Vec3IntToVec3(curr->position), 1.0f, RAYWHITE);
		}
	}
	world.loadedChunksMutex.unlock();


}

void ui()
{
	int y = -20;
	int step = 20;
	DrawText(TextFormat("%i", GetFPS()), 0, y += step, 20, BLACK);
	DrawText(TextFormat("playerPos: (%f, %f, %f)", ExpandVc3(player.position)), 0, y += step, 20, BLACK);
	DrawText(TextFormat("playerChunkPos: (%i, %i, %i)", ExpandVc3(player.currentChunkPos)), 0, y += step, 20, BLACK);
	DrawText(TextFormat("loadedChunksSize: (%i)", world.loadedChunks.size()), 0, y += step, 20, BLACK);
}

int main(void)
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(1080, 720, "Bitsy");
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
