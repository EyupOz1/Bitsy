#include "Chunk.h"

void chunk_create(Chunk *chnk, Vector3 pos)
{
    chnk->pos = pos;
    chnk->dirty = 1;

    Vector3 newPos = (Vector3){(pos.x / CHUNK_SIZE) * CHUNK_SIZE, (pos.y / CHUNK_SIZE) * CHUNK_SIZE, (pos.z / CHUNK_SIZE) * CHUNK_SIZE};
    chnk->pos = newPos;

    chnk->BlockPosIndex = 0;
}

void chunk_block_add(Chunk *Chnk, Block Blck, Vector3 pos)
{
    Chnk->Blocks[(int)pos.x][(int)pos.y][(int)pos.z] = Blck;
    Chnk->BlocksPos[Chnk->BlockPosIndex++] = pos;
}

void chunk_mesh_create(Chunk *Chnk)
{

    Mesh mesh = {0};
    mesh.triangleCount = 0;
    mesh.vertexCount = 0;

    float *vertices = RL_MALLOC(sizeof(float) * Chnk->BlockPosIndex * 72);
    float *normals = RL_MALLOC(sizeof(float) * Chnk->BlockPosIndex * 72);
    unsigned short *indices = RL_MALLOC(sizeof(unsigned short) * Chnk->BlockPosIndex * 72);

    long int indices_index = 0;
    long int vertex_index = 0;
    long int normals_index = 0;

    long int k = 0;
    long int j = 0;

    long int BlockCount = 0;

    float localNormals[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f};

    for (int i = 0; i < Chnk->BlockPosIndex; i++)
    {
        Vector3 currPos = Chnk->BlocksPos[i];
        Block currBlock = Chnk->Blocks[(int)currPos.x][(int)currPos.y][(int)currPos.z];

        if (currBlock.BlockID <= 0)
        {
            continue;
        }
        float localVertices[] = {
            // Pos Z
            0 + currPos.z, 0 + currPos.y, 1 + currPos.x,
            1 + currPos.z, 0 + currPos.y, 1 + currPos.x,
            1 + currPos.z, 1 + currPos.y, 1 + currPos.x,
            0 + currPos.z, 1 + currPos.y, 1 + currPos.x,
            // Neg Z
            0 + currPos.z, 0 + currPos.y, 0 + currPos.x,
            0 + currPos.z, 1 + currPos.y, 0 + currPos.x,
            1 + currPos.z, 1 + currPos.y, 0 + currPos.x,
            1 + currPos.z, 0 + currPos.y, 0 + currPos.x,
            // Pos Y
            0 + currPos.z, 1 + currPos.y, 0 + currPos.x,
            0 + currPos.z, 1 + currPos.y, 1 + currPos.x,
            1 + currPos.z, 1 + currPos.y, 1 + currPos.x,
            1 + currPos.z, 1 + currPos.y, 0 + currPos.x,
            // Neg Y
            0 + currPos.z, 0 + currPos.y, 0 + currPos.x,
            1 + currPos.z, 0 + currPos.y, 0 + currPos.x,
            1 + currPos.z, 0 + currPos.y, 1 + currPos.x,
            0 + currPos.z, 0 + currPos.y, 1 + currPos.x,
            // Pos X
            1 + currPos.z, 0 + currPos.y, 0 + currPos.x,
            1 + currPos.z, 1 + currPos.y, 0 + currPos.x,
            1 + currPos.z, 1 + currPos.y, 1 + currPos.x,
            1 + currPos.z, 0 + currPos.y, 1 + currPos.x,
            // Neg Z
            0 + currPos.z, 0 + currPos.y, 0 + currPos.x,
            0 + currPos.z, 0 + currPos.y, 1 + currPos.x,
            0 + currPos.z, 1 + currPos.y, 1 + currPos.x,
            0 + currPos.z, 1 + currPos.y, 0 + currPos.x};

        // TODO: Test if block in adjacent chunk is set

        unsigned char sideCount = 0;
        unsigned char pos_x = currPos.x + 1 >= CHUNK_SIZE || Chnk->Blocks[(int)(currPos.x + 1)][(int)(currPos.y)][(int)(currPos.z)].BlockID <= 0;
        unsigned char neg_x = currPos.x - 1 < 0 || Chnk->Blocks[(int)(currPos.x - 1)][(int)(currPos.y)][(int)(currPos.z)].BlockID <= 0;
        unsigned char pos_y = currPos.y + 1 >= CHUNK_SIZE || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y + 1)][(int)(currPos.z)].BlockID <= 0;
        unsigned char neg_y = currPos.y - 1 < 0 || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y - 1)][(int)(currPos.z)].BlockID <= 0;
        unsigned char pos_z = currPos.z + 1 >= CHUNK_SIZE || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y)][(int)(currPos.z + 1)].BlockID <= 0;
        unsigned char neg_z = currPos.z - 1 < 0 || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y)][(int)(currPos.z - 1)].BlockID <= 0;

        int x = 12;
        if (pos_x)
        {
            for (int l = x * 0; l < x * 1; l++)
            {
                vertices[vertex_index++] = localVertices[l];
                normals[normals_index++] = localNormals[l];
            }
            mesh.triangleCount += 2;
            sideCount++;
        }

        if (neg_x)
        {
            for (int l = x * 1; l < x * 2; l++)
            {
                vertices[vertex_index++] = localVertices[l];
                normals[normals_index++] = localNormals[l];
            }
            mesh.triangleCount += 2;
            sideCount++;
        }

        if (pos_y)
        {
            for (int l = x * 2; l < x * 3; l++)
            {
                vertices[vertex_index++] = localVertices[l];
                normals[normals_index++] = localNormals[l];
            }
            mesh.triangleCount += 2;
            sideCount++;
        }

        if (neg_y)
        {
            for (int l = x * 3; l < x * 4; l++)
            {
                vertices[vertex_index++] = localVertices[l];
                normals[normals_index++] = localNormals[l];
            }
            mesh.triangleCount += 2;
            sideCount++;
        }

        if (pos_z)
        {
            for (int l = x * 4; l < x * 5; l++)
            {
                vertices[vertex_index++] = localVertices[l];
                normals[normals_index++] = localNormals[l];
            }
            mesh.triangleCount += 2;
            sideCount++;
        }

        if (neg_z)
        {
            for (int l = x * 5; l < x * 6; l++)
            {
                vertices[vertex_index++] = localVertices[l];
                normals[normals_index++] = localNormals[l];
            }
            mesh.triangleCount += 2;
            sideCount++;
        }

        int old_j = j;
        // Indices can be initialized right now
        for (; j - old_j < sideCount * 6; j += 6)
        {
            indices[j] = 4 * k;
            indices[j + 1] = 4 * k + 1;
            indices[j + 2] = 4 * k + 2;
            indices[j + 3] = 4 * k;
            indices[j + 4] = 4 * k + 2;
            indices[j + 5] = 4 * k + 3;

            indices_index += 6;

            k++;
        }

        BlockCount++;
        mesh.vertexCount += sideCount * 4;
    }

    mesh.vertices = (float *)RL_MALLOC(vertex_index * sizeof(float));
    mesh.normals = (float *)RL_MALLOC(normals_index * sizeof(float));
    mesh.indices = (unsigned short *)RL_MALLOC(indices_index * sizeof(unsigned short));

    memcpy(mesh.vertices, vertices, vertex_index * sizeof(float));
    memcpy(mesh.normals, normals, normals_index * sizeof(float));
    memcpy(mesh.indices, indices, indices_index * sizeof(unsigned short));

    UploadMesh(&mesh, false);
    Chnk->currentMesh = mesh;

    RL_FREE(vertices);
    RL_FREE(indices);
    RL_FREE(normals);
}

int map(int input, int in_min, int in_max, int out_min, int out_max)
{
    return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void chunk_perlin_generate(Chunk *chunk)
{
    Image noise = GenImagePerlinNoise(CHUNK_SIZE, CHUNK_SIZE, chunk->pos.x, chunk->pos.y, 1);
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            unsigned char height = GetImageColor(noise, i, j).g;

            float x = map(height, 0, 255, 0, CHUNK_SIZE - 1);
            chunk_block_add(chunk, (Block){.BlockID = 1}, (Vector3){i, x, j});
        }
    }
    UnloadImage(noise);
}