#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"
#include "World/Block.hpp"
#include "World/Chunk.hpp"
#include "Core/Utils.hpp"
#include <array>

int map(int input, int in_min, int in_max, int out_min, int out_max)
{
    return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void getBaseNormals(float *inpt)
{
    float baseNormals[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f};

    for (int i = 0; i < 72; ++i)
    {
        inpt[i] = baseNormals[i];
    }
}

void calculateVertices(float *inpt, Vector3Int currPos)
{
    Vector3 pos = Vec3IntToVec3(currPos);

    float localVertices[] = {

        0.5 + pos.x, -0.5 + pos.y, -0.5 + pos.z,
        0.5 + pos.x, -0.5 + pos.y, 0.5 + pos.z,
        0.5 + pos.x, 0.5 + pos.y, 0.5 + pos.z,
        0.5 + pos.x, 0.5 + pos.y, -0.5 + pos.z,

        -0.5 + pos.x, -0.5 + pos.y, -0.5 + pos.z,
        -0.5 + pos.x, 0.5 + pos.y, -0.5 + pos.z,
        -0.5 + pos.x, 0.5 + pos.y, 0.5 + pos.z,
        -0.5 + pos.x, -0.5 + pos.y, 0.5 + pos.z,

        -0.5 + pos.x, 0.5 + pos.y, -0.5 + pos.z,
        0.5 + pos.x, 0.5 + pos.y, -0.5 + pos.z,
        0.5 + pos.x, 0.5 + pos.y, 0.5 + pos.z,
        -0.5 + pos.x, 0.5 + pos.y, 0.5 + pos.z,

        -0.5 + pos.x, -0.5 + pos.y, -0.5 + pos.z,
        -0.5 + pos.x, -0.5 + pos.y, 0.5 + pos.z,
        0.5 + pos.x, -0.5 + pos.y, 0.5 + pos.z,
        0.5 + pos.x, -0.5 + pos.y, -0.5 + pos.z,

        -0.5 + pos.x, -0.5 + pos.y, 0.5 + pos.z,
        -0.5 + pos.x, 0.5 + pos.y, 0.5 + pos.z,
        0.5 + pos.x, 0.5 + pos.y, 0.5 + pos.z,
        0.5 + pos.x, -0.5 + pos.y, 0.5 + pos.z,

        -0.5 + pos.x, -0.5 + pos.y, -0.5 + pos.z,
        0.5 + pos.x, -0.5 + pos.y, -0.5 + pos.z,
        0.5 + pos.x, 0.5 + pos.y, -0.5 + pos.z,
        -0.5 + pos.x, 0.5 + pos.y, -0.5 + pos.z};

    for (int i = 0; i < 72; ++i)
    {
        inpt[i] = localVertices[i];
    }
}



void generateChunkMesh(std::array<Chunk*, 6> neighbourChunks, Chunk* chunk)
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

	for (int i = 0; i < chunk->blocksPos.size(); i++)
	{
		Vector3Int currPos = chunk->blocksPos[i];
		BlockState currBlock = chunk->getBlock(currPos);

		if (currBlock.ID <= 0) { continue; }

		float localVertices[72];
		calculateVertices(localVertices, currPos);

		float baseTexcoords[48];
		getTexCoords(currBlock.ID, baseTexcoords);

		unsigned char sideCount = 0;
		unsigned char sidesToDraw[] = {
			currPos.x + 1 >= CHUNK_SIZE || chunk->getBlock({currPos.x + 1, currPos.y, currPos.z}).ID <= 0,
			currPos.x - 1 < 0 || chunk->getBlock({currPos.x - 1, currPos.y, currPos.z}).ID <= 0,
			currPos.y + 1 >= CHUNK_SIZE || chunk->getBlock({currPos.x, currPos.y + 1, currPos.z}).ID <= 0,
			currPos.y - 1 < 0 || chunk->getBlock({currPos.x, currPos.y - 1, currPos.z}).ID <= 0,
			currPos.z + 1 >= CHUNK_SIZE || chunk->getBlock({currPos.x, currPos.y, currPos.z + 1}).ID <= 0,
			currPos.z - 1 < 0 || chunk->getBlock({currPos.x, currPos.y, currPos.z - 1}).ID <= 0 };


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

	chunk->mesh = mesh;
}
