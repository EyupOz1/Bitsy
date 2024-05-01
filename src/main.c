#include "raylib.h"
#include "rcamera.h"

#include "World.h"
#include "Player.h"
#include "Chunk.h"

#include "Debug.h"


Player *player;
int loadedChunksCount = 0;
Chunk *loadedChunks[2000];

void setup()
{
    player = RL_MALLOC(sizeof(Player));
    player_create(player);

    Chunk* ch = RL_MALLOC(sizeof(Chunk));
    chunk_create(ch, (Vector3){0, 0, 0});
    loadedChunks[0] = ch;
    chunk_block_add(loadedChunks[0], (Block){.BlockID = 1}, (Vector3){1, 3, 1});
    chunk_block_add(loadedChunks[0], (Block){.BlockID = 1}, (Vector3){1, 4, 1});
    chunk_block_add(loadedChunks[0], (Block){.BlockID = 1}, (Vector3){1, 5, 1});
    chunk_mesh_create(ch);
    ch->currentModel = LoadModelFromMesh(ch->currentMesh);

}
void update()
{
    player_update(player);
    DrawModel(loadedChunks[0]->currentModel, (Vector3){0, 0, 0}, 1.0, GREEN);


/*
    world_chunk_update(player, loadedChunks, &loadedChunksCount);
    world_chunk_draw(loadedChunks, &loadedChunksCount);

    debug_chunk_show(&(Chunk){.pos = {0, 0, 0}});

    */
}

void ui()
{
    DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", player->camera.position.x, player->camera.position.y, player->camera.position.z), 610, 60, 10, BLACK);
    DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", player->camera.target.x, player->camera.target.y, player->camera.target.z), 610, 75, 10, BLACK);
    DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", player->camera.up.x, player->camera.up.y, player->camera.up.z), 610, 90, 10, BLACK);

    Vector3 pos1 = worldPositionToChunk(player->camera.position);
    DrawText(TextFormat("%f, %f, %f", pos1.x, pos1.y, pos1.z), 0, 0, 10, BLACK);
}

int main(void)
{
    InitWindow(1080, 720, "Bitsy");
    DisableCursor();
    SetTargetFPS(120);
    SetTraceLogLevel(LOG_ALL);

    setup();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(player->camera);

        update();

        EndMode3D();

        ui();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
