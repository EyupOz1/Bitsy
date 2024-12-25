#include "Core/Defines.hpp"
#include "Core/Utils.hpp"
#include "Player.hpp"
#include "raymath.h"
#include "rcamera.h"
#include "World/World.hpp"

void Player::Init()
{
	this->camera.position = { 0.1f, 100.0f, 0.0f };
	this->camera.target = { 1.0f, 0.0f, 0.0f };
	this->camera.up = { 0.0f, 1.0f, 0.0f };
	this->camera.fovy = PLAYER_FOV;
	this->camera.projection = CAMERA_PERSPECTIVE;

	this->currentChunkPos = { 0, 0 };
	this->lastChunkPos = { 0, 0 };
}

void Player::Update(World* world)
{
	this->move();
	this->currentChunkPos = roundToChunkVec(Vector2{ this->position.x, this->position.z });
	Ray ray = GetMouseRay({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, this->camera);
	std::vector<Chunk*> hittedChunks;
	for (Chunk* chunk : world->activeChunks)
	{
		
		BoundingBox boundingBox = {
			{ (float)chunk->position.x, 0, (float)chunk->position.y },
			{ (float)chunk->position.x + CHUNK_SIZE_XZ, CHUNK_SIZE_Y, (float)chunk->position.y + CHUNK_SIZE_XZ }
		};

		RayCollision rayCollision = GetRayCollisionBox(ray, boundingBox);
		if (rayCollision.hit)
		{
			DrawBoundingBox(boundingBox, BLACK);
			hittedChunks.push_back(chunk);
		}
	}

	for (Chunk* chunk : hittedChunks)
	{
		Matrix m = MatrixTranslate((float)chunk->position.x, 0.0f, (float)chunk->position.y);
		RayCollision rayCollision = GetRayCollisionMesh(ray, chunk->mesh, m);
		if (rayCollision.hit)
		{
			DrawSphere(rayCollision.point, .4f, RED);
		}
	}
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
