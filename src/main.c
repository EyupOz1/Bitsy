#include "raylib.h"
#include "rcamera.h"
#include "math.h"

#include "World.h"
#include "Player.h"
#include "Chunk.h"
#include "Shader.h"

#include "Debug.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

Player *player;
RayCollision rx;

int loadedChunksCount = 0;
Chunk *loadedChunks[2000];

Shader shader;
Light light;
Texture2D tex;

void setup()
{
    player = RL_MALLOC(sizeof(Player));
    player_create(player);

    shader_init(&shader, &light, &tex);

    Chunk *newChunk = RL_MALLOC(sizeof(Chunk));
    chunk_create(newChunk, (Vector3){0, 0, 0}, 1);
    chunk_block_add(newChunk, (Block){.BlockID = 1}, (Vector3){1, 1, 1});
    chunk_mesh_create(newChunk);
    newChunk->currentModel = LoadModelFromMesh(newChunk->currentMesh);
    loadedChunks[loadedChunksCount++] = newChunk;
}

void update()
{
    // Shader
    light.position = player->camera.position;
    float cameraPos[3] = {player->camera.position.x, player->camera.position.y, player->camera.position.z};
    SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    UpdateLightValues(shader, light);

    // Player
    player_move(player);
    RayCollision temp = player_interact(player, loadedChunks, &loadedChunksCount);
    if (temp.hit == 1)
    {
        
        rx = temp;
    }

    DrawSphere(rx.point, 0.02f, BLUE);
    DrawLine3D(rx.point, Vector3Add(rx.point, rx.normal), PURPLE);

    // World
    // world_chunk_update(player, loadedChunks, &loadedChunksCount);
    loadedChunks[0]->shouldLoad = 1;
    world_chunk_draw(loadedChunks, &loadedChunksCount, shader, tex);

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
