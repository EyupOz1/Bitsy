#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"

#include "string.h"

#include "Block.h"
#include "Player.h"
#include "Chunk.h"
#include "Core.h"

#include "Test.h"

Chunk Chnk = {0};
Player *playerptr;

int main(void)
{

    init(1080, 720, "Bitsy", 120);
    playerptr = player_create();

    test_world2(&Chnk);

    Model ChnkMdl = LoadModelFromMesh(chunk_mesh_create(&Chnk));
    int i = 0, j = 0, k = 0;
    float localVertices[] = {

        1 + i, 1 + j, 1 + k,
        0 + i, 1 + j, 1 + k,
        0 + i, 0 + j, 1 + k,
        1 + i, 0 + j, 1 + k,

        1 + i, 1 + j, 0 + k,
        0 + i, 1 + j, 0 + k,
        0 + i, 0 + j, 0 + k,
        1 + i, 0 + j, 0 + k

    };

    while (!WindowShouldClose())
    {

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(playerptr->player_camera);
            UpdateCamera(&(playerptr->player_camera), CAMERA_FREE);

            DrawPlane((Vector3){0.0f, -10.0f, 0.0f}, (Vector2){32.0f, 32.0f}, GREEN); // Stop losing reference frame

            DrawModelWires(ChnkMdl, (Vector3){0, 0, 0}, 1.0f, DARKGRAY);


            Color clo[] = {GREEN, RED, MAGENTA, PINK, PURPLE, ORANGE, BLUE, MAROON};
            int ix = 0;
            for (int i = 0; i < 8; i++)
            {
                DrawPoint3D((Vector3){localVertices[i * 3], localVertices[i * 3 + 1], localVertices[i * 3 + 2]}, clo[ix++]);
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
