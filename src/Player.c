#include "player.h"

void player_create(Player *player)
{
    player->camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    player->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    player->camera.fovy = 60.0f;
    player->camera.projection = CAMERA_PERSPECTIVE;
}

void player_move(Player *player)
{
    if (IsKeyDown(KEY_W))
        CameraMoveForward(&(player->camera), CAMERA_MOVE_SPEED, 1);
    if (IsKeyDown(KEY_A))
        CameraMoveRight(&(player->camera), -CAMERA_MOVE_SPEED, 1);
    if (IsKeyDown(KEY_S))
        CameraMoveForward(&(player->camera), -CAMERA_MOVE_SPEED, 1);
    if (IsKeyDown(KEY_D))
        CameraMoveRight(&(player->camera), CAMERA_MOVE_SPEED, 1);

    if (IsKeyDown(KEY_SPACE))
        CameraMoveUp(&(player->camera), CAMERA_MOVE_SPEED);

    if (IsKeyDown(KEY_LEFT_SHIFT))
        CameraMoveUp(&(player->camera), -CAMERA_MOVE_SPEED);

    Vector2 mousePositionDelta = GetMouseDelta();
    CameraYaw(&(player->camera), -mousePositionDelta.x * CAMERA_MOUSE_MOVE_SENSITIVITY, 0);
    CameraPitch(&(player->camera), -mousePositionDelta.y * CAMERA_MOUSE_MOVE_SENSITIVITY, 1, 0, 0);
}

RayCollision player_interact(Player *player, Chunk **loadedChunks, int *loadedChunksCount)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {

        for (int i = 0; i < *loadedChunksCount; i++)
        {
            Ray ray = GetMouseRay((Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2}, player->camera);
            RayCollision rc;

            Matrix m = MatrixTranslate(loadedChunks[i]->pos.x, loadedChunks[i]->pos.y, loadedChunks[i]->pos.z);
            rc = GetRayCollisionMesh(ray, loadedChunks[i]->currentMesh, MatrixMultiply(m, loadedChunks[i]->currentModel.transform));

            if (rc.hit)
            {
                TraceLog(LOG_DEBUG, TextFormat("Ray hit on pos: %f, %f, %f", rc.point.x, rc.point.y, rc.point.z));
                TraceLog(LOG_DEBUG, TextFormat("normal: %f, %f, %f", rc.normal.x, rc.normal.y, rc.normal.z));

                Vector3 target;
                if (rc.normal.x != 0)
                {
                    target = (Vector3){(rc.normal.x == 1 ? rc.point.x : rc.point.x - 1), floorToInt(rc.point.y), floorToInt(rc.point.z)};
                }
                if (rc.normal.y != 0)
                {
                    target = (Vector3){floorToInt(rc.point.x), (rc.normal.y == 1 ? rc.point.y + 1 : rc.point.y), floorToInt(rc.point.z)};
                }
                if (rc.normal.z != 0)
                {
                    target = (Vector3){floorToInt(rc.point.x), floorToInt(rc.point.y), (rc.normal.z == 1 ? rc.point.z : rc.point.z - 1)};
                }

                TraceLog(LOG_DEBUG, TextFormat("target: %f, %f, %f", target.x, target.y, target.z));
                chunk_block_add(loadedChunks[i], (Block){.BlockID = 1}, (Vector3){target.x, target.y, target.y});
                return rc;
            }
            rc.hit = 0;
        }
    }
    return (RayCollision){0};
}
/*

Vector3 test()
{
Vector3 hits[100];
int hits_index = 0;
Ray ray;

if (IsKeyPressed(KEY_O))
{
    Ray ray = GetMouseRay((Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2}, player->camera);
    RayCollision rc;

    for (int i = 0; i < loadedChunksCount; i++)
    {

        Matrix m = MatrixTranslate(loadedChunks[i]->pos.x, loadedChunks[i]->pos.y, loadedChunks[i]->pos.z);
        rc = GetRayCollisionMesh(ray, loadedChunks[i]->currentMesh, MatrixMultiply(m, loadedChunks[i]->currentModel.transform));

        if (rc.hit)
        {
            TraceLog(LOG_DEBUG, TextFormat("Ray hit on pos: %f, %f, %f", rc.point.x, rc.point.y, rc.point.z));
            hits[hits_index++] = rc.point;
            return (Vector3){round(rc.point.x), round(rc.point.y), round(rc.point.x)};
        }
        rc.hit = 0;
    }
}
return Vector3Zero();



    Vector3 xx = test();
if (xx.x != 0.0f && xx.y != 0.0f && xx.z != 0.0f)
{
    TraceLog(LOG_DEBUG, "%f, %f, %f", xx.x, xx.y, xx.z);
    chunk_block_add(chunk_find(loadedChunks, &loadedChunksCount, xx), (Block){.BlockID = 1}, (Vector3){round(xx.x), round(xx.y), round(xx.z)});
}
}
*/