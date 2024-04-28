#include "Chunk.h"

Chunk chunk_create(Chunk *chnk, Vector3 pos)
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

    float vertices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 3 * BLOCK_VERTICES_COUNT] = {0};
    unsigned short indices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 3 * BLOCK_INDICES_COUNT] = {0};

    long int indices_index = 0;
    long int vertex_index = 0;

    long int BlockCount = 0;

    for (int i = 0; i < Chnk->BlockPosIndex; i++)
    {
        Vector3 currPos = Chnk->BlocksPos[i];
        Block currBlock = Chnk->Blocks[(int)currPos.x][(int)currPos.y][(int)currPos.z];

        if (currBlock.BlockID <= 0)
        {
            continue;
        }

        float localVertices[] = {

            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,

            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 0 + currPos.z

        };

        unsigned short localIndices[] = {

            //+X
            4 + 8 * BlockCount,
            0 + 8 * BlockCount,
            7 + 8 * BlockCount,
            7 + 8 * BlockCount,
            0 + 8 * BlockCount,
            3 + 8 * BlockCount,

            //-X
            1 + 8 * BlockCount,
            5 + 8 * BlockCount,
            2 + 8 * BlockCount,
            2 + 8 * BlockCount,
            5 + 8 * BlockCount,
            6 + 8 * BlockCount,

            //+Y
            4 + 8 * BlockCount,
            5 + 8 * BlockCount,
            0 + 8 * BlockCount,
            0 + 8 * BlockCount,
            5 + 8 * BlockCount,
            1 + 8 * BlockCount,

            //-Y
            3 + 8 * BlockCount,
            2 + 8 * BlockCount,
            7 + 8 * BlockCount,
            7 + 8 * BlockCount,
            2 + 8 * BlockCount,
            6 + 8 * BlockCount,

            //+Z
            0 + 8 * BlockCount,
            1 + 8 * BlockCount,
            3 + 8 * BlockCount,
            3 + 8 * BlockCount,
            1 + 8 * BlockCount,
            2 + 8 * BlockCount,

            //-Z
            5 + 8 * BlockCount,
            4 + 8 * BlockCount,
            6 + 8 * BlockCount,
            6 + 8 * BlockCount,
            4 + 8 * BlockCount,
            7 + 8 * BlockCount,
        };

        // TODO: Test if block in adjacent chunk is set

        unsigned char blockUnderground = 1;

        if (currPos.x + 1 >= CHUNK_SIZE || Chnk->Blocks[(int)(currPos.x + 1)][(int)(currPos.y)][(int)(currPos.z)].BlockID <= 0)
        {
            for (int l = 0; l < 6; l++)
            {
                indices[indices_index++] = localIndices[l];
            }
            mesh.triangleCount += 2;
            blockUnderground = 0;
        }

        if (currPos.x - 1 < 0 || Chnk->Blocks[(int)(currPos.x - 1)][(int)(currPos.y)][(int)(currPos.z)].BlockID <= 0)
        {
            for (int l = 6; l < 12; l++)
            {
                indices[indices_index++] = localIndices[l];
            }
            mesh.triangleCount += 2;
            blockUnderground = 0;
        }

        if (currPos.y + 1 >= CHUNK_SIZE || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y + 1)][(int)(currPos.z)].BlockID <= 0)
        {
            for (int l = 12; l < 18; l++)
            {
                indices[indices_index++] = localIndices[l];
            }
            mesh.triangleCount += 2;
            blockUnderground = 0;
        }

        if (currPos.y - 1 < 0 || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y - 1)][(int)(currPos.z)].BlockID <= 0)
        {
            for (int l = 18; l < 24; l++)
            {
                indices[indices_index++] = localIndices[l];
            }
            mesh.triangleCount += 2;
            blockUnderground = 0;
        }

        if (currPos.z + 1 >= CHUNK_SIZE || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y)][(int)(currPos.z + 1)].BlockID <= 0)
        {
            for (int l = 24; l < 30; l++)
            {
                indices[indices_index++] = localIndices[l];
            }
            mesh.triangleCount += 2;
            blockUnderground = 0;
        }

        if (currPos.z - 1 < 0 || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y)][(int)(currPos.z - 1)].BlockID <= 0)
        {
            for (int l = 30; l < 36; l++)
            {
                indices[indices_index++] = localIndices[l];
            }
            mesh.triangleCount += 2;
            blockUnderground = 0;
        }

        if (!blockUnderground)
        {
            memcpy(&vertices[vertex_index], localVertices, BLOCK_INDICES_COUNT * sizeof(float));
            vertex_index += BLOCK_INDICES_COUNT;
        }

        BlockCount++;
    }

    mesh.vertexCount = vertex_index / 3;

    mesh.vertices = (float *)RL_MALLOC(vertex_index * sizeof(float));
    mesh.indices = (unsigned short *)RL_MALLOC(indices_index * sizeof(unsigned short));

    memcpy(mesh.vertices, vertices, vertex_index * sizeof(float));
    memcpy(mesh.indices, indices, indices_index * sizeof(unsigned short));

    UploadMesh(&mesh, false);
    Chnk->currentMesh = mesh;
}
int map(int input, int in_min, int in_max, int out_min, int out_max) {
    return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void chunk_perlin_generate(Chunk *chunk)
{
    Image noise = GenImagePerlinNoise(CHUNK_SIZE, CHUNK_SIZE, 0, 0, 1);
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            unsigned char height = GetImageColor(noise, i, j).g;
            
            float x = map(height, 0, 255, 0, CHUNK_SIZE-1);
            chunk_block_add(chunk, (Block){.BlockID = 1}, (Vector3){i, x, j});
        }
    }
}