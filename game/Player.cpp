#include "Player.hpp"
#include "State.hpp"
#include "rcamera.h"
#include "raymath.h"
#include "Defines.hpp"
#include "Utils.hpp"

void Player::Init()
{
    this->camera.position = {0.1f, 0.0f, 0.0f};
    this->camera.target = {1.0f, 0.0f, 0.0f};
    this->camera.up = {0.0f, 1.0f, 0.0f};
    this->camera.fovy = State::get().fieldOfView;
    this->camera.projection = CAMERA_PERSPECTIVE;

    this->light = CreateLight(LIGHT_POINT, this->camera.position, Vector3Zero(), WHITE, State::get().shader);
}

void Player::Update()
{

    this->camera.position = this->position;

    move();

    this->position = this->camera.position;

    float cameraPos[3] = {camera.position.x, camera.position.y, camera.position.z};
    SetShaderValue(State::get().shader, State::get().shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    this->light.position = this->position;
    UpdateLightValues(State::get().shader, this->light);
}

void Player::move()
{
    State &state = State::get();

    float movementSpeed = state.movementSpeed;
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
    CameraYaw(&camera, -mousePositionDelta.x * state.mouseSensitivity, 0);
    CameraPitch(&camera, -mousePositionDelta.y * state.mouseSensitivity, 1, 0, 0);
}
