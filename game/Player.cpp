#include "Player.hpp"
#include "rcamera.h"
#include "raymath.h"
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"

void Player::Init()
{
    this->camera.position = {0.1f, 0.0f, 0.0f};
    this->camera.target = {1.0f, 0.0f, 0.0f};
    this->camera.up = {0.0f, 1.0f, 0.0f};
    this->camera.fovy = PLAYER_FOV;
    this->camera.projection = CAMERA_PERSPECTIVE;

    this->currentChunkPos = {0, 0, 0};
    this->lastChunkPos = {0, 0, 0};
}

void Player::Update()
{
    this->move();
    this->currentChunkPos = roundToChunkVec(this->position);

}

void Player::move()
{
    this->camera.position = this->position;
    float movementSpeed = PLAYER_MOVEMENT_SPEED * GetFrameTime();
    if (IsKeyDown(KEY_LEFT_SHIFT))
        movementSpeed *= 4;

    if (IsKeyDown(KEY_W))
        CameraMoveForward(&camera, movementSpeed, 1);
    if (IsKeyDown(KEY_A))
        CameraMoveRight(&camera, -movementSpeed, 1);
    if (IsKeyDown(KEY_S))
        CameraMoveForward(&camera, -movementSpeed, 1);
    if (IsKeyDown(KEY_D))
        CameraMoveRight(&camera, movementSpeed, 1);

    if (IsKeyDown(KEY_SPACE))
        CameraMoveUp(&camera, movementSpeed);

    if (IsKeyDown(KEY_LEFT_CONTROL))
        CameraMoveUp(&camera, -movementSpeed);

    Vector2 mousePositionDelta = GetMouseDelta();
    CameraYaw(&camera, -mousePositionDelta.x * PLAYER_MOUSE_SENSITIVITY_SPEED, 0);
    CameraPitch(&camera, -mousePositionDelta.y * PLAYER_MOUSE_SENSITIVITY_SPEED, 1, 0, 0);
    this->position = this->camera.position;
}
