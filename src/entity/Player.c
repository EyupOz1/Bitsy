#include "player.h"

void player_init(Player *player)
{
    player->camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    player->camera.target = (Vector3){1.0f, 0.0f, 0.0f};
    player->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    player->camera.fovy = 95.0f;
    player->camera.projection = CAMERA_PERSPECTIVE;
}

void player_update(Player *player, Chunk **loadedChunks, int *loadedChunksCount, Config *cfg)
{
    move(player, cfg);
    look(player, loadedChunks, loadedChunksCount);

    place(player, loadedChunks, loadedChunksCount);

    if (IsKeyPressed(KEY_F))
    {

        cfg->mouseActive = !cfg->mouseActive;
        cfg->mouseActive ? EnableCursor() : DisableCursor();
    }

    if (IsKeyPressed(KEY_F11))
    {
        ToggleFullscreen();
    }
}

void move(Player *player, Config *cfg)
{

    float speed = cfg->flyingSpeed;
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
    CameraYaw(&(player->camera), -mousePositionDelta.x * cfg->mouseSensitivity, 0);
    CameraPitch(&(player->camera), -mousePositionDelta.y * cfg->mouseSensitivity, 1, 0, 0);
}

Chunk* setPlayerRayInfo(Player *player, Chunk **loadedChunks, int *loadedChunksCount)
{
    int x = -1;
    for (int i = 0; i < *loadedChunksCount; i++)
    {
        RayCollision currCollision;

        Matrix m = MatrixTranslate(loadedChunks[i]->pos.x, loadedChunks[i]->pos.y, loadedChunks[i]->pos.z);
        currCollision = GetRayCollisionMesh(player->ray, loadedChunks[i]->currentMesh, MatrixMultiply(m, loadedChunks[i]->currentModel.transform));

        if ((currCollision.hit && player->rayCollision.distance > currCollision.distance))
        {
            player->rayCollision = currCollision;
            x = i;
        }
    }
    if (x != -1)
    {
        return loadedChunks[x];
    }
    return 0;
}

void look(Player *player, Chunk **loadedChunks, int *loadedChunksCount)
{
    player->ray = GetMouseRay((Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2}, player->camera);
    player->rayCollision.distance = 999999;

    Chunk* ch = setPlayerRayInfo(player, loadedChunks, loadedChunksCount);
    if (!player->rayCollision.hit || ch == 0)
    {
        return;
    }

    player->targetBlockPosInWorldSpace = rayCollisionToBlockPos(player->rayCollision);

    player->targetChunk = ch;
    player->targetChunkValid = 1;

    float x = player->targetBlockPosInWorldSpace.x >= 0 ? (int)player->targetBlockPosInWorldSpace.x % CHUNK_SIZE : CHUNK_SIZE + ((int)player->targetBlockPosInWorldSpace.x % CHUNK_SIZE);
    float y = player->targetBlockPosInWorldSpace.y >= 0 ? (int)player->targetBlockPosInWorldSpace.y % CHUNK_SIZE : CHUNK_SIZE + ((int)player->targetBlockPosInWorldSpace.y % CHUNK_SIZE);
    float z = player->targetBlockPosInWorldSpace.z >= 0 ? (int)player->targetBlockPosInWorldSpace.z % CHUNK_SIZE : CHUNK_SIZE + ((int)player->targetBlockPosInWorldSpace.z % CHUNK_SIZE);
    if (x == CHUNK_SIZE)
    {
        x = 0;
    }
    if (y == CHUNK_SIZE)
    {
        y = 0;
    }
    if (z == CHUNK_SIZE)
    {
        z = 0;
    }

    player->targetBlockPosInChunkSpace = (Vector3){x, y, z};
}

void place(Player *player, Chunk **loadedChunks, int *loadedChunksCount)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        Vector3 chunkPosOfBlock = worldPositionToChunk(player->targetBlockPosInWorldSpace);
        Vector3 blockPosInChunk = Vector3Subtract(player->targetBlockPosInWorldSpace, chunkPosOfBlock);

        Vector3 target = player->targetBlockPosInChunkSpace;
        TraceLog(LOG_DEBUG, "Place on: %f, %f, %f", target.x, target.y, target.z);
        chunk_block_add(player->targetChunk, (Block){.BlockID = 1}, target);
        player->targetChunk->dirty = 1;
    }
}
