#include "player.h"

Player *player_create()
{

    Player *new_player = RL_MALLOC(sizeof(Player));
    new_player->player_camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    new_player->player_camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    new_player->player_camera.fovy = 60.0f;
    new_player->player_camera.projection = CAMERA_PERSPECTIVE;

    return new_player;
}

void player_update(Camera *camera, int mode)
{

    Vector2 mousePositionDelta = GetMouseDelta();

    bool moveInWorldPlane = ((mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON));
    bool rotateAroundTarget = ((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    bool lockView = ((mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    bool rotateUp = false;

    // Camera rotation
    if (IsKeyDown(KEY_DOWN))
        CameraPitch(camera, -CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
    if (IsKeyDown(KEY_UP))
        CameraPitch(camera, CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
    if (IsKeyDown(KEY_RIGHT))
        CameraYaw(camera, -CAMERA_ROTATION_SPEED, rotateAroundTarget);
    if (IsKeyDown(KEY_LEFT))
        CameraYaw(camera, CAMERA_ROTATION_SPEED, rotateAroundTarget);
    if (IsKeyDown(KEY_Q))
        CameraRoll(camera, -CAMERA_ROTATION_SPEED);
    if (IsKeyDown(KEY_E))
        CameraRoll(camera, CAMERA_ROTATION_SPEED);

    // Camera movement
    if (!IsGamepadAvailable(0))
    {
        // Camera pan (for CAMERA_FREE)
        if ((mode == CAMERA_FREE) && (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)))
        {
            const Vector2 mouseDelta = GetMouseDelta();
            if (mouseDelta.x > 0.0f)
                CameraMoveRight(camera, CAMERA_PAN_SPEED, moveInWorldPlane);
            if (mouseDelta.x < 0.0f)
                CameraMoveRight(camera, -CAMERA_PAN_SPEED, moveInWorldPlane);
            if (mouseDelta.y > 0.0f)
                CameraMoveUp(camera, -CAMERA_PAN_SPEED);
            if (mouseDelta.y < 0.0f)
                CameraMoveUp(camera, CAMERA_PAN_SPEED);
        }
        else
        {
            // Mouse support
            CameraYaw(camera, -mousePositionDelta.x * CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
            CameraPitch(camera, -mousePositionDelta.y * CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);
        }

        // Keyboard support
        if (IsKeyDown(KEY_W))
            CameraMoveForward(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
        if (IsKeyDown(KEY_A))
            CameraMoveRight(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
        if (IsKeyDown(KEY_S))
            CameraMoveForward(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
        if (IsKeyDown(KEY_D))
            CameraMoveRight(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
    }
    else
    {
        // Gamepad controller support
        CameraYaw(camera, -(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) * 2) * CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
        CameraPitch(camera, -(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) * 2) * CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);

        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) <= -0.25f)
            CameraMoveForward(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) <= -0.25f)
            CameraMoveRight(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) >= 0.25f)
            CameraMoveForward(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) >= 0.25f)
            CameraMoveRight(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
    }

    if (mode == CAMERA_FREE)
    {
        if (IsKeyDown(KEY_SPACE))
            CameraMoveUp(camera, CAMERA_MOVE_SPEED);
        if (IsKeyDown(KEY_LEFT_CONTROL))
            CameraMoveUp(camera, -CAMERA_MOVE_SPEED);
    }

    if ((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL) || (mode == CAMERA_FREE))
    {
        // Zoom target distance
        CameraMoveToTarget(camera, -GetMouseWheelMove());
        if (IsKeyPressed(KEY_KP_SUBTRACT))
            CameraMoveToTarget(camera, 2.0f);
        if (IsKeyPressed(KEY_KP_ADD))
            CameraMoveToTarget(camera, -2.0f);
    }
}

Ray Player_keys(Player *player)
{

}
