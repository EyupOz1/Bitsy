#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"

#include "string.h"

#include "Block.h"
#include "World.h"
#include "Player.h"
#include "Chunk.h"
#include "Core.h"

#include "Test.h"

Player *playerptr;

World world = {0};

int main(void)
{

    init(1080, 720, "Bitsy", 120);
    playerptr = player_create();

    for (int i = 0; i < 5; i++)
    {
        test_world(&world.loadedChunks[i]);
        world.loadedChunks[i].pos = (Vector3){i * 16, 0, i * 16};
        chunk_mesh_create(&world.loadedChunks[i]);
        world.loadedChunks[i].dirty = 1;
        printf("%f, %f, %f\n", world.loadedChunks[i].pos.x, world.loadedChunks[i].pos.y, world.loadedChunks[i].pos.z);
    }

    Model models[5];

    while (!WindowShouldClose())
    {

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(playerptr->player_camera);
            UpdateCamera(&(playerptr->player_camera), CAMERA_FREE);

            DrawPlane((Vector3){0.0f, -10.0f, 0.0f}, (Vector2){32.0f, 32.0f}, GREEN); // Stop losing reference frame

            for (int i = 0; i < 5; i++)
            {
                if (world.loadedChunks[i].dirty == 1)
                {
                    world.loadedChunks[i].dirty = 0;
                    models[i] = LoadModelFromMesh(world.loadedChunks[i].currentMesh);
                    DrawModelWires(models[i], world.loadedChunks[i].pos, 1.0f, DARKGRAY);
                }
                else
                {
                    DrawModelWires(models[i], world.loadedChunks[i].pos, 1.0f, DARKGRAY);
                }
            }


            EndMode3D();
        }

        DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", playerptr->player_camera.position.x, playerptr->player_camera.position.y, playerptr->player_camera.position.z), 610, 60, 10, BLACK);
        DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", playerptr->player_camera.target.x, playerptr->player_camera.target.y, playerptr->player_camera.target.z), 610, 75, 10, BLACK);
        DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", playerptr->player_camera.up.x, playerptr->player_camera.up.y, playerptr->player_camera.up.z), 610, 90, 10, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
