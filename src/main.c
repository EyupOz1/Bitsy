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
int loadedChunkCount = 0;
Chunk *loadedChunk[2000];

int main(void)
{

    init(1080, 720, "Bitsy", 120);
    playerptr = player_create();

    Ray ray;
    RayCollision rc;
    char test[] = "Hallo";
    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(playerptr->player_camera);
        player_update(&(playerptr->player_camera), CAMERA_FREE);

        world_chunk_update(playerptr, loadedChunk, &loadedChunkCount);

        for (int i = 0; i < loadedChunkCount; i++)
        {
            if (loadedChunk[i]->dirty && loadedChunk[i]->shouldLoad)
            {
                chunk_mesh_create(loadedChunk[i]);
                loadedChunk[i]->currentModel = LoadModelFromMesh(loadedChunk[i]->currentMesh);
                loadedChunk[i]->dirty = 0;
            }
            if (loadedChunk[i]->shouldLoad)
            {
                DrawModel(loadedChunk[i]->currentModel, loadedChunk[i]->pos, 1.0f, PURPLE);
                loadedChunk[i]->shouldLoad = 0;
            }
        }

        DrawPlane((Vector3){0.0f, -10.0f, 0.0f}, (Vector2){32.0f, 32.0f}, GREEN); // Stop losing reference frame

        if (IsKeyDown(KEY_O))
        {
            ray = GetMouseRay((Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2}, playerptr->player_camera);
            for (int i = 0; i < loadedChunkCount; i++)
            {
                for (int j = 0; j < loadedChunk[i]->currentModel.meshCount; j++)
                {
                    rc = GetRayCollisionMesh(ray, loadedChunk[i]->currentModel.meshes[j], loadedChunk[i]->currentModel.transform);
                    if (rc.hit)
                    {

                        break;
                    }
                }
                if (rc.hit)
                {
                    break;
                }
            }
        }

        DrawPoint3D(rc.point, BLACK);

        DrawRay(ray, BLUE);
        EndMode3D();

        DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", playerptr->player_camera.position.x, playerptr->player_camera.position.y, playerptr->player_camera.position.z), 610, 60, 10, BLACK);
        DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", playerptr->player_camera.target.x, playerptr->player_camera.target.y, playerptr->player_camera.target.z), 610, 75, 10, BLACK);
        DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", playerptr->player_camera.up.x, playerptr->player_camera.up.y, playerptr->player_camera.up.z), 610, 90, 10, BLACK);

        Vector3 pos1 = world_PosToChunk(playerptr->player_camera.position);
        DrawText(TextFormat("%f, %f, %f", pos1.x, pos1.y, pos1.z), 0, 0, 10, BLACK);

        DrawText(TextFormat("%f, %f, %f\n", rc.point.x, rc.point.y, rc.point.z), 0, 50, 10, BLACK);
        DrawText(test, 0, 80, 10, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
