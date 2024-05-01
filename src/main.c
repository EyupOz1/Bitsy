#include "raylib.h"
#include "rcamera.h"

#include "World.h"
#include "Player.h"
#include "Chunk.h"

#include "Debug.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

Player *player;
int loadedChunksCount = 0;
Chunk *loadedChunks[2000];

Shader shader;
Light light;

void setup()
{
    player = RL_MALLOC(sizeof(Player));
    player_create(player);

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    shader = LoadShader("src/lighting.vs", "src/lighting.fs");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){0.1f, 0.1f, 0.1f, 1.0f}, SHADER_UNIFORM_VEC4);

    light = CreateLight(LIGHT_POINT, (Vector3){-2, 1, -2}, Vector3Zero(), YELLOW, shader);
}
void update()
{
    float cameraPos[3] = {player->camera.position.x, player->camera.position.y, player->camera.position.z};
    SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    UpdateLightValues(shader, light);

    player_update(player);

    world_chunk_update(player, loadedChunks, &loadedChunksCount);
    world_chunk_draw(loadedChunks, &loadedChunksCount, shader);

    debug_chunk_show(&(Chunk){.pos = {0, 0, 0}});
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
