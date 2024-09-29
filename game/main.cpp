#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include <vector>
#include "Player.hpp"
#include "Core/Math/Vector3Int.hpp"
#include <thread>
#include "World/World.hpp"
#include "Core/Defines.hpp"

bool killThread = 0;
std::thread ChunkGenThread;

Player player;
World world;

Texture atlas;


void chunkGenThreadFunction()
{
	Vector3Int lastChunk = player.currentChunkPos;
	while (!killThread)
	{
		if (Vector3IntCompare(player.currentChunkPos, lastChunk))
		{
			world.calcChunks(player.currentChunkPos);
		}
		lastChunk = player.currentChunkPos;
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
	for (int i = 0; i < world.loadedChunks.size(); i++)
	{

		if (world.loadedChunks[i]->status.load() == CHUNK_CreateModel)
		{
			world.loadedChunks[i]->status = CHUNK_CreatingModel;

			UploadMesh(&world.loadedChunks[i]->mesh, false);
			world.loadedChunks[i]->model = LoadModelFromMesh(world.loadedChunks[i]->mesh);
			world.loadedChunks[i]->model.materials[0].maps[0].texture = atlas;

			world.loadedChunks[i]->status = CHUNK_Render;
		}
		if (world.loadedChunks[i]->status.load() == CHUNK_Render)
		{
			DrawModel(world.loadedChunks[i]->model, Vec3IntToVec3(world.loadedChunks[i]->position), 1.0f, RAYWHITE);
		}

		if (world.loadedChunks[i]->status.load() == CHUNK_DeleteChunk)
		{
			world.loadedChunks[i]->status = CHUNK_DeletingChunk;
			world.loadedChunks[i]->Destroy();

		}


	}
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
