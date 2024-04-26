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
Chunk *loadedChunk[30];

int main(void)
{
    init(1080, 720, "Bitsy", 120);
    playerptr = player_create();

    Chunk ch = chunk_create((Vector3){0, 0, 0});
    Chunk ch1 = chunk_create((Vector3){0, CHUNK_SIZE, 0});
    loadedChunk[loadedChunkCount++] = &ch;
    loadedChunk[loadedChunkCount++] = &ch1;

    test_world2(loadedChunk[0]);
    test_world2(loadedChunk[1]);


    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(playerptr->player_camera);
        player_update(&(playerptr->player_camera), CAMERA_FREE);

        Vector3 pos1 = getChunkPos(playerptr->player_camera.position);

        world_chunk_update(playerptr, loadedChunk, loadedChunkCount);

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
