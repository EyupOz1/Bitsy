#include "Chunk.hpp"
#include "raylib.h"
#include <iostream>
#include "Utils.hpp"
#include "Defines.hpp"
#include "State.hpp"

void Chunk::Init(Vector3 pos)
{
    this->position = pos;
    this->dirty = true;

    this->mesh.vertexCount = 0;
    this->model.meshCount = 0;

    this->blocks.reserve(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
}

void Chunk::Update()
{
    if (this->dirty && this->blocksPos.size() > 0)
    {
        TraceLog(LOG_DEBUG, "Chunk(%f, %f, %f).genMesh & genModel", ExpandVc3(this->position));
        this->gen();
        this->dirty = false;
    }
}
void Chunk::Draw()
{
    DrawModel(this->model, this->position, 1.0f, WHITE);
}

void Chunk::Destroy()
{

    if (this->model.meshCount != 0)
    {
        UnloadModel(this->model);
    }
}

void Chunk::gen()
{

    if (this->model.meshCount != 0)
    {
        UnloadModel(this->model);
    }

    Mesh mesh = {0};
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
        Vector3 currPos = this->blocksPos[i];
        Block currBlock = this->getBlock(currPos);

        if (currBlock.ID <= 0)
        {
            continue;
        }

        float localVertices[] = {

            1 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,

            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,

            0 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,

            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 0 + currPos.z,

            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,

            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 0 + currPos.z};

        // Tex
        float baseTexcoords[48];
        BlockData::getTexcoords(currBlock, baseTexcoords);

        unsigned char sideCount = 0;
        unsigned char sidesToDraw[] = {
            currPos.x + 1 >= CHUNK_SIZE || getBlock({currPos.x + 1, currPos.y, currPos.z}).ID <= 0,
            currPos.x - 1 < 0 || getBlock({currPos.x - 1, currPos.y, currPos.z}).ID <= 0,
            currPos.y + 1 >= CHUNK_SIZE || getBlock({currPos.x, currPos.y + 1, currPos.z}).ID <= 0,
            currPos.y - 1 < 0 || getBlock({currPos.x, currPos.y - 1, currPos.z}).ID <= 0,
            currPos.z + 1 >= CHUNK_SIZE || getBlock({currPos.x, currPos.y, currPos.z + 1}).ID <= 0,
            currPos.z - 1 < 0 || getBlock({currPos.x, currPos.y, currPos.z - 1}).ID <= 0};

        for (int j = 0; j < 6; j++)
        {
            if (sidesToDraw[j])
            {
                for (int l = 12 * j; l < 12 * (j + 1); l++)
                {
                    vertices.push_back(localVertices[l]);
                    normals.push_back(baseNormals[l]);
                }
                for (int l = 8 * j; l < 8 * (j + 1); l++)
                {
                    texcoords.push_back(baseTexcoords[l]);
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

    TraceLog(LOG_DEBUG, "%i %i %i %i", vertices.size(), normals.size(), indices.size(), texcoords.size());
    mesh.vertices = new float[vertices.size()];
    mesh.normals = new float[normals.size()];
    mesh.indices = new unsigned short[indices.size()];
    mesh.texcoords = new float[texcoords.size()];

    std::copy(vertices.begin(), vertices.end(), mesh.vertices);
    std::copy(normals.begin(), normals.end(), mesh.normals);
    std::copy(indices.begin(), indices.end(), mesh.indices);
    std::copy(texcoords.begin(), texcoords.end(), mesh.texcoords);

    UploadMesh(&mesh, false);
    this->mesh = mesh;

    this->model = LoadModelFromMesh(mesh);
    this->model.materials[0].maps[0].texture = State::get().atlas;
    this->model.materials[0].shader = State::get().shader;
}
Block Chunk::getBlock(Vector3 pos)
{
    int index = (static_cast<int>(pos.z) * CHUNK_SIZE * CHUNK_SIZE) + (static_cast<int>(pos.y) * CHUNK_SIZE) + static_cast<int>(pos.x);
    Block bl = this->blocks[index];

    return bl;
}

bool Chunk::setBlock(Vector3 pos, Block block)
{
    if (
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE || pos.z >= CHUNK_SIZE ||
        pos.x < 0 || pos.y < 0 || pos.z < 0)
    {
        TraceLog(LOG_DEBUG, "On Chunk (%f, %f, %f) cannot set Block %i on (%f, %f, %f)", ExpandVc3(this->position), block.ID, ExpandVc3(pos));
        return false;
    }

    pos = {static_cast<float>(static_cast<int>(pos.x)), static_cast<float>(static_cast<int>(pos.y)), static_cast<float>(static_cast<int>(pos.z))};
    // TraceLog(LOG_DEBUG, "Set Block %i on (%f, %f, %f) in Chunk (%f, %f, %f)", block.ID, ExpandVc3(pos), ExpandVc3(this->position));

    this->blocksPos.push_back(pos);
    int index = (static_cast<int>(pos.z) * CHUNK_SIZE * CHUNK_SIZE) + (static_cast<int>(pos.y) * CHUNK_SIZE) + static_cast<int>(pos.x);
    this->blocks[index] = block;

    this->dirty = true;
    return true;
}

void Chunk::perlin()
{
    if (this->position.y == 0)
    {

        Image noise = GenImagePerlinNoise(CHUNK_SIZE, CHUNK_SIZE, this->position.x, this->position.y, 1);
        for (int i = 0; i < CHUNK_SIZE; i++)
        {
            for (int j = 0; j < CHUNK_SIZE; j++)
            {
                unsigned char height = GetImageColor(noise, i, j).g;

                float x = map(height, 0, 255, 0, CHUNK_SIZE - 1);

                this->setBlock({static_cast<float>(i), x, static_cast<float>(j)}, {3});
                for (int s = x - 1; s >= 0; s--)
                {
                    this->setBlock({static_cast<float>(i), static_cast<float>(s), static_cast<float>(j)}, {2});
                }
            }
        }
        UnloadImage(noise);
    }
}