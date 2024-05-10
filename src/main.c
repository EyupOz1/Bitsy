#include "raylib.h"
#include "rcamera.h"
#include "gui/raygui.h"

#include "core/rlights.h"
#include "core/Debug.h"

#include "world/World.h"
#include "entity/Player.h"
#include "core/Utils.h"
#include "world/Chunk.h"
#include "core/Shader.h"
#include "world/ChunkSystem.h"

Config CFG = {
    .flyingSpeed = 0.2f,
    .mouseActive = 1,
    .mouseSensitivity = 0.005f,
    .fieldOfView = 95.0f,
};

Player *player;

int loadedChunksCount = 0;
Chunk *loadedChunks[2000];

Shader shader;
Light light;
Texture2D tex;
Model block;

void setup()
{
    player = MemAlloc(sizeof(Player));
    player_init(player);

    shader_init(&shader, &light, &tex);

    GuiLoadStyleDefault();

    block = LoadModelFromMesh(mesh_block());
}
int x = 1;

void update()
{
    chunkSystem_update(player, loadedChunks, &loadedChunksCount, shader, tex);
    player_update(player, loadedChunks, &loadedChunksCount, &CFG);
    shader_update(&shader, &light, player->camera.position);

    // Debug
    DrawSphere(player->rayCollision.point, 0.4f, BLUE);
    DrawSphere((Vector3){0.5, 0, 0.5}, 0.3f, PURPLE);
    DrawLine3D(player->rayCollision.point, Vector3Add(player->rayCollision.point, player->rayCollision.normal), PURPLE);
    DrawRay(player->ray, GREEN);


    DrawModel(block, player->targetBlockPosInWorldSpace, 1.0, YELLOW);
}
void ui()
{
    int step = 20;
    int y = -step;
    DrawText(TextFormat("playerPosRaw: (%f, %f, %f)", player->camera.position.x, player->camera.position.y, player->camera.position.z), 0, y += step, 20, BLACK);

    Vector3 pos1 = worldPositionToChunk(player->camera.position);
    DrawText(TextFormat("playerChunk: %f, %f, %f", pos1.x, pos1.y, pos1.z), 0, y += step, 20, BLACK);

    DrawText(TextFormat("rayPosRaw: %f, %f, %f", player->rayCollision.point.x, player->rayCollision.point.y, player->rayCollision.point.z), 0, y += step, 20, BLACK);
    DrawText(TextFormat("rayNormal: %f, %f, %f", player->rayCollision.normal.x, player->rayCollision.normal.y, player->rayCollision.normal.z), 0, y += step, 20, BLACK);

    DrawText(TextFormat("rayBlockPosInWorldSpace: %f, %f, %f", player->targetBlockPosInWorldSpace.x, player->targetBlockPosInWorldSpace.y, player->targetBlockPosInWorldSpace.z), 0, y += step, 20, BLACK);

    if (player->targetChunkValid)
    {
        DrawText(TextFormat("rayChunkPos:  %.2f, %.2f, %.2f", player->targetChunkPos.x, player->targetChunkPos.y, player->targetChunkPos.z), 0, y += step, 20, BLACK);
    }
    DrawText(TextFormat("rayBlockPosInChunkSpace: %.2f, %.2f, %.2f", player->targetBlockPosInChunkSpace.x, player->targetBlockPosInChunkSpace.y, player->targetBlockPosInChunkSpace.z), 0, y += step, 20, BLACK);

    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 1, GREEN);
}

int main(void)
{
    InitWindow(1080, 720, "Bitsy");
    DisableCursor();
    SetTargetFPS(60);
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
