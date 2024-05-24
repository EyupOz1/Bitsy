#include "player.h"
#include "../GLOBAL.h"

void player_init(Player *player)
{
    player->camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    player->camera.target = (Vector3){1.0f, 0.0f, 0.0f};
    player->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    player->camera.fovy = 95.0f;
    player->camera.projection = CAMERA_PERSPECTIVE;
}

void player_update(Player *player, ChunkSystem *chunkSys)
{
    move(player);
    look(player, chunkSys);

    place(player, chunkSys);

    if (IsKeyPressed(KEY_F))
    {

        GLOBAL.mouseActive = !GLOBAL.mouseActive;
        GLOBAL.mouseActive ? EnableCursor() : DisableCursor();
    }

    if (IsKeyPressed(KEY_F11))
    {
        ToggleFullscreen();
    }
}

void move(Player *player)
{

    float speed = GLOBAL.flyingSpeed;
    if (IsKeyDown(KEY_LEFT_SHIFT))
        speed *= 2;

    if (IsKeyDown(KEY_W))
        CameraMoveForward(&(player->camera), speed, 1);
    if (IsKeyDown(KEY_A))
        CameraMoveRight(&(player->camera), -speed, 1);
    if (IsKeyDown(KEY_S))
        CameraMoveForward(&(player->camera), -speed, 1);
    if (IsKeyDown(KEY_D))
        CameraMoveRight(&(player->camera), speed, 1);

    if (IsKeyDown(KEY_SPACE))
        CameraMoveUp(&(player->camera), speed);

    if (IsKeyDown(KEY_LEFT_CONTROL))
        CameraMoveUp(&(player->camera), -speed);

    Vector2 mousePositionDelta = GetMouseDelta();
    CameraYaw(&(player->camera), -mousePositionDelta.x * GLOBAL.mouseSensitivity, 0);
    CameraPitch(&(player->camera), -mousePositionDelta.y * GLOBAL.mouseSensitivity, 1, 0, 0);
}

Vector3 setPlayerRayInfo(Player *player, ChunkSystem *chunkSys)
{
    int x = -1;
    for (int i = 0; i < chunkSys->loadedChunksCount; i++)
    {

        RayCollision currCollision;

        Matrix m = MatrixTranslate(chunkSys->loadedChunks[i]->pos.x, chunkSys->loadedChunks[i]->pos.y, chunkSys->loadedChunks[i]->pos.z);
        currCollision = GetRayCollisionMesh(player->ray, chunkSys->loadedChunks[i]->currentMesh, MatrixMultiply(m, chunkSys->loadedChunks[i]->currentModel.transform));

        if ((currCollision.hit && player->rayCollision.distance > currCollision.distance))
        {
            player->rayCollision = currCollision;
            x = i;
        }
    }
    if (x != -1)
    {
        return chunkSys->loadedChunks[x]->pos;
    }
    return (Vector3){-1, -1, -1};
}

void look(Player *player, ChunkSystem *chunkSys)
{
    player->ray = GetMouseRay((Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2}, player->camera);
    player->rayCollision.distance = 999999;

    Vector3 chunkPos = setPlayerRayInfo(player, chunkSys);
    if (!player->rayCollision.hit || chunkPos.x == -1)
    {
        return;
    }

    player->targetBlockPosInWorldSpace = rayCollisionToBlockPos(player->rayCollision);

    player->targetChunkPos = chunkPos;
    player->targetChunkValid = 1;

    // FIXME:
    float x = player->targetBlockPosInWorldSpace.x >= 0 ? (int)player->targetBlockPosInWorldSpace.x % CHUNK_SIZE : CHUNK_SIZE + ((int)player->targetBlockPosInWorldSpace.x % CHUNK_SIZE);
    float y = player->targetBlockPosInWorldSpace.y >= 0 ? (int)player->targetBlockPosInWorldSpace.y % CHUNK_SIZE : CHUNK_SIZE + ((int)player->targetBlockPosInWorldSpace.y % CHUNK_SIZE);
    float z = player->targetBlockPosInWorldSpace.z >= 0 ? (int)player->targetBlockPosInWorldSpace.z % CHUNK_SIZE : CHUNK_SIZE + ((int)player->targetBlockPosInWorldSpace.z % CHUNK_SIZE);

    if (player->targetBlockPosInChunkSpace.x == 0 && player->rayCollision.normal.x == 1.0f)
    {
        player->targetChunkPos.x += CHUNK_SIZE;
    }

    if (player->targetBlockPosInChunkSpace.x == CHUNK_SIZE - 1 && player->rayCollision.normal.x == -1.0f)
    {
        player->targetChunkPos.x -= CHUNK_SIZE;
    }

    if (player->targetBlockPosInChunkSpace.y == 0 && player->rayCollision.normal.y == 1.0f)
    {
        player->targetChunkPos.y += CHUNK_SIZE;
    }

    if (player->targetBlockPosInChunkSpace.y == CHUNK_SIZE - 1 && player->rayCollision.normal.y == -1.0f)
    {
        player->targetChunkPos.y -= CHUNK_SIZE;
    }

    if (player->targetBlockPosInChunkSpace.z == 0 && player->rayCollision.normal.z == 1.0f)
    {
        player->targetChunkPos.z += CHUNK_SIZE;
    }

    if (player->targetBlockPosInChunkSpace.z == CHUNK_SIZE - 1 && player->rayCollision.normal.z == -1.0f)
    {
        player->targetChunkPos.z -= CHUNK_SIZE;
    }

    player->targetBlockPosInChunkSpace = (Vector3){x, y, z};
}

void place(Player *player, ChunkSystem *chunkSys)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        Chunk *targetChunk = chunk_find(chunkSys, player->targetChunkPos);
        Vector3 target = player->targetBlockPosInChunkSpace;
        TraceLog(LOG_DEBUG, "Player_place: %f, %f, %f", target.x, target.y, target.z);
        chunk_block_add(targetChunk, (Block){.BlockID = 1}, target);
        targetChunk->dirty = 1;
    }
}
