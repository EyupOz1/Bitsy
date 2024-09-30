#include "Chunk.hpp"
#include "raylib.h"
#include <iostream>
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
#include "Core/Utils.hpp"

// Basic

void Chunk::Init(Vector3Int pos)
{
	TraceLog(LOG_DEBUG, "New Chunk: %i, %i, %i", ExpandVc3(pos));

	this->position = pos;
	this->blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);

	this->mesh.vertexCount = 0;
	this->model.meshCount = 0;

	this->UpdateBlocks();
	this->status = CHUNK_CreateMesh;
}

void Chunk::Destroy()
{
	TraceLog(LOG_DEBUG, "Destroyed: %i, %i, %i", ExpandVc3(this->position));
	if (this->model.meshCount != 0)
	{
		UnloadModel(this->model);
	}
	this->model.meshCount = 0;

}

void Chunk::UpdateBlocks()
{
	if (this->position.y == 0)
	{

		Image noise = GenImagePerlinNoise(CHUNK_SIZE, CHUNK_SIZE, this->position.x, this->position.z, 1);
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				unsigned char height = GetImageColor(noise, i, j).g;

				int x = map(height, 0, 255, 0, CHUNK_SIZE - 1);

				this->setBlock({ i, x, j }, { 3 }, true);
				for (int s = x - 1; s >= 0; s--)
				{
					this->setBlock({ i, s, j }, { 2 }, true);
				}
			}
		}
		UnloadImage(noise);
	}
	else if (this->position.y < 0)
	{
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					this->setBlock({ i, j, k }, { 2 }, true);
				}
			}
		}
	}
}

Block Chunk::getBlock(Vector3Int pos)
{
	int index = (static_cast<int>(pos.z) * CHUNK_SIZE * CHUNK_SIZE) + (static_cast<int>(pos.y) * CHUNK_SIZE) + static_cast<int>(pos.x);
	Block bl = this->blocks[index];

	return bl;
}

bool Chunk::setBlock(Vector3Int pos, Block block, bool shouldReplace)
{
	if (
		pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE || pos.z >= CHUNK_SIZE ||
		pos.x < 0 || pos.y < 0 || pos.z < 0)
	{
		TraceLog(LOG_DEBUG, "On Chunk (%f, %f, %f) cannot set Block %i on (%f, %f, %f)", ExpandVc3(this->position), block.ID, ExpandVc3(pos));
		return false;
	}

	this->blocksPos.push_back(pos);
	int index = (pos.z * CHUNK_SIZE * CHUNK_SIZE) + (pos.y * CHUNK_SIZE) + pos.x;
	this->blocks[index] = block;

	return true;
}

void Chunk::generateMesh()
{

	Mesh mesh = { 0 };
	mesh.triangleCount = 0;
	mesh.vertexCount = 0;

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<unsigned short> indices;
	std::vector<float> texcoords;

	float baseNormals[72];
	getBaseNormals(baseNormals);

	for (int i = 0; i < this->blocksPos.size(); i++)
	{
		Vector3Int currPos = this->blocksPos[i];
		Block currBlock = this->getBlock(currPos);

		if (currBlock.ID <= 0)
		{
			continue;
		}

		float localVertices[72];
		calculateVertices(localVertices, currPos);

		// Tex
		float baseTexcoords[48];
		getTexcoords(currBlock, baseTexcoords);

		unsigned char sideCount = 0;
		unsigned char sidesToDraw[] = {
			currPos.x + 1 >= CHUNK_SIZE || getBlock({currPos.x + 1, currPos.y, currPos.z}).ID <= 0,
			currPos.x - 1 < 0 || getBlock({currPos.x - 1, currPos.y, currPos.z}).ID <= 0,
			currPos.y + 1 >= CHUNK_SIZE || getBlock({currPos.x, currPos.y + 1, currPos.z}).ID <= 0,
			currPos.y - 1 < 0 || getBlock({currPos.x, currPos.y - 1, currPos.z}).ID <= 0,
			currPos.z + 1 >= CHUNK_SIZE || getBlock({currPos.x, currPos.y, currPos.z + 1}).ID <= 0,
			currPos.z - 1 < 0 || getBlock({currPos.x, currPos.y, currPos.z - 1}).ID <= 0 };

		for (int j = 0; j < 6; j++)
		{
			if (sidesToDraw[j])
			{
				for (int k = 12 * j; k < 12 * (j + 1); k++)
				{
					vertices.push_back(localVertices[k]);
					normals.push_back(baseNormals[k]);
				}
				for (int k = 8 * j; k < 8 * (j + 1); k++)
				{
					texcoords.push_back(baseTexcoords[k]);
				}

				indices.push_back(mesh.vertexCount + (4 * sideCount + 3));
				indices.push_back(mesh.vertexCount + (4 * sideCount + 2));
				indices.push_back(mesh.vertexCount + (4 * sideCount));
				indices.push_back(mesh.vertexCount + (4 * sideCount + 2));
				indices.push_back(mesh.vertexCount + (4 * sideCount + 1));
				indices.push_back(mesh.vertexCount + (4 * sideCount));

				mesh.triangleCount += 2;
				sideCount++;
			}
		}

		mesh.vertexCount += sideCount * 4;
	}

	mesh.vertices = new float[vertices.size()];
	mesh.normals = new float[normals.size()];
	mesh.indices = new unsigned short[indices.size()];
	mesh.texcoords = new float[texcoords.size()];

	std::copy(vertices.begin(), vertices.end(), mesh.vertices);
	std::copy(normals.begin(), normals.end(), mesh.normals);
	std::copy(indices.begin(), indices.end(), mesh.indices);
	std::copy(texcoords.begin(), texcoords.end(), mesh.texcoords);

	this->mesh = mesh;

}
