#include "raylib.h"
#include "rcamera.h"

#include "core/Debug.h"
#include "core/Utils.h"

#include "visuals/Shader.h"

#include "world/Chunk.h"
#include "world/ChunkSystem.h"
#include "world/BlockData.h"

#include "entity/Player.h"

#include "GLOBAL.h"


Config GLOBAL;

Player *player;

ChunkSystem chunkSys;

Model block;

void setup()
{
    GLOBAL = (Config){
        .fieldOfView = 95.0f,
        .flyingSpeed = 0.1f,
        .mouseActive = 1,
        .mouseSensitivity = 0.008f,
        .pos = (Vector3){0, 0, 0},
        .atlas = LoadTextureFromImage(LoadImage(PATH_TEXTURES_ATLAS)),
        .renderDistance = 2};

    shader_init();

    player = MemAlloc(sizeof(Player));
    player_init(player);
    chunkSystem_init(&chunkSys);

    blockData_init();

    block = LoadModelFromMesh(mesh_block());
}

void update()
{
    chunkSystem_update(player->camera.position, &chunkSys);
    player_update(player, &chunkSys);

    // Debug
    DrawSphere(player->rayCollision.point, 0.4f, BLUE);
    DrawLine3D(player->rayCollision.point, Vector3Add(player->rayCollision.point, player->rayCollision.normal), PURPLE);
    DrawRay(player->ray, GREEN);

    DrawModel(block, player->targetBlockPosInWorldSpace, 1.0, YELLOW);

    DrawBillboard(player->camera, GLOBAL.atlas, (Vector3){0, 0, 0}, 1.0, WHITE);
}
void ui()
{
    int step = 20;
    int y = -step;
    DrawText(TextFormat("playerPosRaw: (%f, %f, %f)", player->camera.position.x, player->camera.position.y, player->camera.position.z), 0, y += step, 20, BLACK);

    Vector3 res = worldPositionToChunk(player->camera.position);
    DrawText(TextFormat("playerChunk: %f, %f, %f", res.x, res.y, res.z), 0, y += step, 20, BLACK);

    DrawText(TextFormat("rayPosRaw: %f, %f, %f", player->rayCollision.point.x, player->rayCollision.point.y, player->rayCollision.point.z), 0, y += step, 20, BLACK);
    DrawText(TextFormat("rayNormal: %f, %f, %f", player->rayCollision.normal.x, player->rayCollision.normal.y, player->rayCollision.normal.z), 0, y += step, 20, BLACK);

    DrawText(TextFormat("rayBlockPosInWorldSpace: %f, %f, %f", player->targetBlockPosInWorldSpace.x, player->targetBlockPosInWorldSpace.y, player->targetBlockPosInWorldSpace.z), 0, y += step, 20, BLACK);

    if (player->targetChunkValid)
    {
        DrawText(TextFormat("rayChunkPos:  %.2f, %.2f, %.2f", player->targetChunkPos.x, player->targetChunkPos.y, player->targetChunkPos.z), 0, y += step, 20, BLACK);
    }
    DrawText(TextFormat("rayBlockPosInChunkSpace: %.2f, %.2f, %.2f", player->targetBlockPosInChunkSpace.x, player->targetBlockPosInChunkSpace.y, player->targetBlockPosInChunkSpace.z), 0, y += step, 20, BLACK);

    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 1, GREEN);

    DrawFPS(0, y += step);

    DrawTexture(GLOBAL.atlas, 0, y += step, WHITE);
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
        BeginMode3D(player->camera);
        update();
        EndMode3D();

        ui();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
