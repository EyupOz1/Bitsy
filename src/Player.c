#include "player.h"

void player_create(Player *player)
{
    player->camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    player->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    player->camera.fovy = 60.0f;
    player->camera.projection = CAMERA_PERSPECTIVE;
}

void player_update(Player *player)
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
