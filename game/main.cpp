#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
#include "Player.hpp"
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <World/Chunk.hpp>
#include"Core/DebugMenu.hpp"
#include <World/World.hpp>

Player player;
Texture atlas;
World world;

void setup()
{
	player.Init();
	world.Init(LoadTexture(PATH_TEXTURES_ATLAS));
}

Vector2Int lastUpdatedChunk = { -CHUNK_SIZE_Y, 0 };
void update()
{
	player.Update(&world);

	if (!(player.currentChunkPos == lastUpdatedChunk))
	{
		world.Update(player.currentChunkPos);
		lastUpdatedChunk = player.currentChunkPos;
	}

	world.processCalculatedChunks();


	std::vector<Chunk*> chunksToDelete;

	for (Chunk* ch : world.activeChunks)
	{


		if (ch->position.distanceSqr(player.currentChunkPos) > CHUNK_DELETE_DIST)
		{
			if (ch->validModel)
			{
				UnloadModel(ch->model);
				chunksToDelete.push_back(ch);
				continue;
			}
		}
		if (ch->validModel == 0)
		{
			UploadMesh(&ch->mesh, false);
			ch->model = LoadModelFromMesh(ch->mesh);
			ch->validModel = 1;
			ch->model.materials->maps->texture = world.atlas;


		}

		DrawModel(ch->model, { (float)ch->position.x, 0, (float)ch->position.y }, 1.0, WHITE);
	}

	for (Chunk* ch : chunksToDelete)
	{
		world.activeChunks.deleteChunk(ch->position);
		delete ch;
	}

}
void ui()
{
	DebugMenu::getInstance().render();
	DebugMenu::getInstance().setEntry(0, []() { return TextFormat("%i FPS", GetFPS()); });
	/*
	int y = -20;
	int step = 20;
	DrawText(TextFormat("%i", GetFPS()), 0, y += step, 20, BLACK);
	DrawText(TextFormat("playerPos: (%f, %f, %f)", ExpandVc3(player.position)), 0, y += step, 20, BLACK);
	DrawText(TextFormat("playerChunkPos: (%i, %i)", ExpandVc2(player.currentChunkPos)), 0, y += step, 20, BLACK);
	*/

	
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

	CloseWindow();

	return 0;
}
