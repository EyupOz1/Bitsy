#include "raylib.h"
#include "rcamera.h"

#include "World.h"
#include "Player.h"
#include "Chunk.h"
#include "Shader.h"

#include "Debug.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

Player *player;
int loadedChunksCount = 0;
Chunk *loadedChunks[2000];

Shader shader;
Light light;
Texture2D tex;
Ray cpy;

void test()
{
    if (IsKeyPressed(KEY_O))
    {
        TraceLog(LOG_DEBUG, "Shooting Ray");
        Ray ray = GetMouseRay((Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2}, player->camera);
        cpy = ray;
        TraceLog(LOG_DEBUG, "POSITION: %f, %f, %f\n VBO: %i ", loadedChunks[1]->pos.x, loadedChunks[1]->pos.y, loadedChunks[1]->pos.z, loadedChunks[1]->currentMesh.vaoId);
        RayCollision rc = GetRayCollisionMesh(ray, loadedChunks[1]->currentMesh, loadedChunks[1]->currentModel.transform);
        if (rc.hit)
        {
            TraceLog(LOG_DEBUG, "Ray HIT");
            TraceLog(LOG_DEBUG, TextFormat("Ray hit on pos: %f, %f, %f", rc.point.x, rc.point.y, rc.point.z));
        }
        DrawRay(ray, BLUE);
        DrawPoint3D(rc.point, GREEN);
    }
}

void setup()
{
    player = RL_MALLOC(sizeof(Player));
    player_create(player);

    shader_init(&shader, &light, &tex);


}
void update()
{

    light.position = player->camera.position;
    float cameraPos[3] = {player->camera.position.x, player->camera.position.y, player->camera.position.z};
    SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    UpdateLightValues(shader, light);

    player_update(player);

    world_chunk_update(player, loadedChunks, &loadedChunksCount);
    world_chunk_draw(loadedChunks, &loadedChunksCount, shader, tex);

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
