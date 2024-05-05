#include "raylib.h"
#include "rcamera.h"
#include "gui/raygui.h"

#include "core/rlights.h"
#include "core/Debug.h"
#include "Utils.h"

#include "world/World.h"
#include "entity/Player.h"
#include "world/Chunk.h"
#include "core/Shader.h"

Player *player;
RayCollision rx;
unsigned char mouseActive = 0;

int loadedChunksCount = 0;
Chunk *loadedChunks[2000];

Shader shader;
Light light;
Texture2D tex;

void setup()
{
    player = RL_MALLOC(sizeof(Player));
    player_init(player);

    shader_init(&shader, &light, &tex);
    GuiLoadStyleDefault();

    Chunk *newChunk = RL_MALLOC(sizeof(Chunk));
    chunk_create(newChunk, (Vector3){0, 0, 0}, 1);
    chunk_block_add(newChunk, (Block){.BlockID = 1}, (Vector3){0, 0, 0});
    chunk_mesh_create(newChunk);
    newChunk->currentModel = LoadModelFromMesh(newChunk->currentMesh);
    loadedChunks[loadedChunksCount++] = newChunk;

    Vector3 vecToSearch = {0, 0, 1};
    TraceLog(LOG_DEBUG, TextFormat("BlockID at (%f, %f, %f): %i", vecToSearch.x, vecToSearch.y, vecToSearch.z, (loadedChunks[0]->Blocks[(int)vecToSearch.x][(int)vecToSearch.y][(int)vecToSearch.z])));
}

void update()
{
    // Shader
    shader_update(&shader, &light, player->camera.position);

    // Player
    player_update(player, loadedChunks, &loadedChunksCount);
    if (IsKeyPressed(KEY_F))
    {
        mouseActive = !mouseActive;
        mouseActive ? EnableCursor() : DisableCursor();
    }


    DrawSphere((Vector3){0, 0, 0}, 0.2f, BLUE);

    DrawSphere(rx.point, 0.02f, BLUE);
    DrawLine3D(rx.point, Vector3Add(rx.point, rx.normal), PURPLE);

    // World
    //world_chunk_update(player, loadedChunks, &loadedChunksCount);
    loadedChunks[0]->shouldLoad = 1;
    world_chunk_draw(loadedChunks, &loadedChunksCount, shader, tex);

    // Debug
    debug_chunk_show(loadedChunks[0]);
}

void ui()
{
    DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", player->camera.position.x, player->camera.position.y, player->camera.position.z), 610, 60, 10, BLACK);
    DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", player->camera.target.x, player->camera.target.y, player->camera.target.z), 610, 75, 10, BLACK);
    DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", player->camera.up.x, player->camera.up.y, player->camera.up.z), 610, 90, 10, BLACK);

    Vector3 pos1 = worldPositionToChunk(player->camera.position);
    DrawText(TextFormat("%f, %f, %f", pos1.x, pos1.y, pos1.z), 0, 0, 10, BLACK);

    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 1, GREEN);
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
