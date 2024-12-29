#include "Core/Defines.hpp"
#include "Core/Utils.hpp"
#include "Player.hpp"
#include "raymath.h"
#include "rcamera.h"
#include "raylib.h"
#include "World/World.hpp"
#include <cmath>
#include "Core/DebugMenu.hpp"

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

	DebugMenu::getInstance().setEntry(1, [this]() { return TextFormat("Position: (%f, %f, %f)", this->position.x, this->position.y, this->position.z); });

	Ray ray = GetMouseRay({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, this->camera);
	std::vector<Chunk*> hittedChunks;
	for (Chunk* chunk : world->activeChunks)
	{
		
		BoundingBox boundingBox = {
			{ (float)chunk->position.x - .5f, 0 - .5f, (float)chunk->position.y - .5f },
			{ (float)chunk->position.x + CHUNK_SIZE_XZ - .5f, CHUNK_SIZE_Y - .5f, (float)chunk->position.y + CHUNK_SIZE_XZ - .5f }
		};

		RayCollision rayCollision = GetRayCollisionBox(ray, boundingBox);
		if (rayCollision.hit)
		{
			DrawBoundingBox(boundingBox, BLACK);
			hittedChunks.push_back(chunk);
		}
	}

	Chunk* targetChunk;
	RayCollision rayCollision;
	for (Chunk* chunk : hittedChunks)
	{
		Matrix m = MatrixTranslate((float)chunk->position.x, 0.0f, (float)chunk->position.y);
		rayCollision = GetRayCollisionMesh(ray, chunk->mesh, m);
		if (rayCollision.hit)
		{
			DrawSphere(rayCollision.point, .1f, RED);
			targetChunk = chunk;

			Vector3 lookingAtBlock = rayCollision.point;

			if (rayCollision.normal.x == 1.0f || rayCollision.normal.x == -1.0f)
			{
				lookingAtBlock.x -= .5f;
				lookingAtBlock.y += .5f;
				lookingAtBlock.z += .5f;
				if (lookingAtBlock.x > 1)
				{
					lookingAtBlock.x--;
				}

			}
			if (rayCollision.normal.y == 1.0f || rayCollision.normal.y == -1.0f)
			{
				lookingAtBlock.x += .5f;
				lookingAtBlock.y -= .5f;
				lookingAtBlock.z += .5f;
				if (lookingAtBlock.y > 1)
				{
					lookingAtBlock.y--;
				}
			}
			if (rayCollision.normal.z == 1.0f || rayCollision.normal.z == -1.0f)
			{
				lookingAtBlock.x += .5f;
				lookingAtBlock.y += .5f;
				lookingAtBlock.z -= .5f;
				if (lookingAtBlock.z > 1)
				{
					lookingAtBlock.z--;
				}
			}
			Vector3Int lookingAtBlockInt = { (int)lookingAtBlock.x,(int)lookingAtBlock.y, (int)lookingAtBlock.z };
			Vector3Int test = lookingAtBlockInt;
			if (lookingAtBlockInt.x < 1)
			{
				lookingAtBlockInt.x = lookingAtBlockInt.x - (lookingAtBlockInt.x % CHUNK_SIZE_XZ);
			}
			if (lookingAtBlockInt.y < 1)
			{
				lookingAtBlockInt.y = lookingAtBlockInt.y - (lookingAtBlockInt.y % CHUNK_SIZE_XZ);
			}

			if (lookingAtBlockInt.z < 1)
			{
				lookingAtBlockInt.z = lookingAtBlockInt.z - (lookingAtBlockInt.z % CHUNK_SIZE_XZ);
			}

			if (IsKeyPressed(KEY_LEFT_SHIFT))
			{
				TraceLog(2, "WorldSpace: %f, %f, %f", ExpandVc3(rayCollision.point));
				TraceLog(2, "Normal: %f, %f, %f", ExpandVc3(rayCollision.normal));
				TraceLog(2, "Looking at Block %f, %f, %f", ExpandVc3(lookingAtBlock));
				TraceLog(2, "Looking at Block Before %i, %i, %i", ExpandVc3(test));
				TraceLog(2, "Looking at Block After %i, %i, %i", ExpandVc3(lookingAtBlockInt));

			}

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
