#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"

#include "string.h"

#include "World.h"
#include "Player.h"
#include "Chunk.h"
#include "Core.h"

#include "Test.h"

Player *playerptr;

World *world;

int main(void)
{
    Chunk ch = chunk_create((Vector3){0, 0, 0});
    test_world3(&ch);
    // chunk_block_add(&ch, (Block){.BlockID = 1}, (Vector3){0, 1, 1});

    init(1080, 720, "Bitsy", 120);
    playerptr = player_create();

    chunk_mesh_create(&ch);
    Model mdl = LoadModelFromMesh(ch.currentMesh);

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(playerptr->player_camera);
        player_update(&(playerptr->player_camera), CAMERA_FREE);

        Vector3 pos1 = getChunkPos(playerptr->player_camera.position);

        DrawModel(mdl, pos1, 1.0f, YELLOW);

        DrawPlane((Vector3){0.0f, -10.0f, 0.0f}, (Vector2){32.0f, 32.0f}, GREEN); // Stop losing reference frame

        EndMode3D();

        DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", playerptr->player_camera.position.x, playerptr->player_camera.position.y, playerptr->player_camera.position.z), 610, 60, 10, BLACK);
        DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", playerptr->player_camera.target.x, playerptr->player_camera.target.y, playerptr->player_camera.target.z), 610, 75, 10, BLACK);
        DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", playerptr->player_camera.up.x, playerptr->player_camera.up.y, playerptr->player_camera.up.z), 610, 90, 10, BLACK);

        DrawText(TextFormat("%f, %f, %f\n", pos1.x, pos1.y, pos1.z), 0, 0, 10, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
