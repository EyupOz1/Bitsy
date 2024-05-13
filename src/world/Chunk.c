#include "Chunk.h"

void chunk_create(Chunk *chnk, Vector3 pos, int shouldLoad)
{
    chnk->pos = pos;
    chnk->dirty = 1;
    chnk->shouldLoad = 1;
    chnk->currentMesh = (Mesh){0};
    chnk->currentMesh.vaoId = 0;

    Vector3 newPos = worldPositionToChunk(pos);
    chnk->pos = newPos;

    chnk->BlockPosIndex = 0;

    TraceLog(LOG_DEBUG, "Chunk_new: %f, %f, %f", newPos.x, newPos.y, newPos.z);
}

void chunk_block_add(Chunk *Chnk, Block Blck, Vector3 pos)
{
    if (Chnk->currentMesh.vaoId != 0)
    {
        UnloadMesh(Chnk->currentMesh);
    }

    Chnk->Blocks[(int)pos.x][(int)pos.y][(int)pos.z] = Blck;
    Chnk->BlocksPos[Chnk->BlockPosIndex++] = pos;
    Chnk->dirty = 1;

    // TraceLog(LOG_DEBUG, "Chunk_blockAdd: %f, %f, %f", pos.x, pos.y, pos.z);
}

void chunk_mesh_create(Chunk *Chnk)
{
    Mesh mesh = {0};
    mesh.triangleCount = 0;
    mesh.vertexCount = 0;

    float *vertices = RL_MALLOC(sizeof(float) * Chnk->BlockPosIndex * 72);
    float *normals = RL_MALLOC(sizeof(float) * Chnk->BlockPosIndex * 72);
    unsigned short *indices = RL_MALLOC(sizeof(unsigned short) * Chnk->BlockPosIndex * 72);
    float *texcoords = RL_MALLOC(sizeof(float) * Chnk->BlockPosIndex * 48);

    long int vertex_index = 0;
    long int normals_index = 0;
    long int indices_index = 0;
    long int texcoords_index = 0;

    long int BlockCount = 0;

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
        0.0f, 0.0f, -1.0f

    };

    float xx = 0.0f;
    float yy = 0.0f;
    float baseTexcoords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        yy, xx,
        yy, yy,
        xx, yy,
        xx, xx,

        xx, yy,
        xx, xx,
        yy, xx,
        yy, yy,

        yy, yy,
        xx, yy,
        xx, xx,
        yy, xx,

        yy, xx,
        yy, yy,
        xx, yy,
        xx, xx,

        xx, xx,
        yy, xx,
        yy, yy,
        xx, yy};

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
            1 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            // Neg Z
            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            // Pos Y
            0 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            // Neg Y
            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            // Pos X
            0 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 1 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 1 + currPos.z,
            // Neg Z
            0 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 0 + currPos.y, 0 + currPos.z,
            1 + currPos.x, 1 + currPos.y, 0 + currPos.z,
            0 + currPos.x, 1 + currPos.y, 0 + currPos.z};

        // TODO: Test if block in adjacent chunk is set

        unsigned char sideCount = 0;
        unsigned char sidesToDraw[] = {
            currPos.x + 1 >= CHUNK_SIZE || Chnk->Blocks[(int)(currPos.x + 1)][(int)(currPos.y)][(int)(currPos.z)].BlockID <= 0,
            currPos.x - 1 < 0 || Chnk->Blocks[(int)(currPos.x - 1)][(int)(currPos.y)][(int)(currPos.z)].BlockID <= 0,
            currPos.y + 1 >= CHUNK_SIZE || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y + 1)][(int)(currPos.z)].BlockID <= 0,
            currPos.y - 1 < 0 || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y - 1)][(int)(currPos.z)].BlockID <= 0,
            currPos.z + 1 >= CHUNK_SIZE || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y)][(int)(currPos.z + 1)].BlockID <= 0,
            currPos.z - 1 < 0 || Chnk->Blocks[(int)(currPos.x)][(int)(currPos.y)][(int)(currPos.z - 1)].BlockID <= 0};

        for (int j = 0; j < 6; j++)
        {
            if (sidesToDraw[j])
            {
                for (int l = 12 * j; l < 12 * (j + 1); l++)
                {
                    vertices[vertex_index++] = localVertices[l];
                    normals[normals_index++] = baseNormals[l];
                }
                for (int l = 8 * j; l < 8 * (j + 1); l++)
                {
                    texcoords[texcoords_index++] = baseTexcoords[l];
                }

                indices[indices_index++] = mesh.vertexCount + (4 * sideCount + 3);
                indices[indices_index++] = mesh.vertexCount + (4 * sideCount + 2);
                indices[indices_index++] = mesh.vertexCount + (4 * sideCount);
                indices[indices_index++] = mesh.vertexCount + (4 * sideCount + 2);
                indices[indices_index++] = mesh.vertexCount + (4 * sideCount + 1);
                indices[indices_index++] = mesh.vertexCount + (4 * sideCount);

                mesh.triangleCount += 2;
                sideCount++;
            }
        }

        BlockCount++;
        mesh.vertexCount += sideCount * 4;
    }

    mesh.vertices = (float *)RL_MALLOC(vertex_index * sizeof(float));
    mesh.normals = (float *)RL_MALLOC(normals_index * sizeof(float));
    mesh.indices = (unsigned short *)RL_MALLOC(indices_index * sizeof(unsigned short));
    mesh.texcoords = (float *)RL_MALLOC(texcoords_index * sizeof(float));

    memcpy(mesh.vertices, vertices, vertex_index * sizeof(float));
    memcpy(mesh.normals, normals, normals_index * sizeof(float));
    memcpy(mesh.indices, indices, indices_index * sizeof(unsigned short));
    memcpy(mesh.texcoords, texcoords, texcoords_index * sizeof(float));

    UploadMesh(&mesh, false);
    Chnk->currentMesh = mesh;

    RL_FREE(vertices);
    RL_FREE(indices);
    RL_FREE(normals);
    RL_FREE(texcoords);
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
            int BlockID = 1;
            if (x > 3)
            {
                BlockID = 2;
            }

            chunk_block_add(chunk, (Block){.BlockID = BlockID}, (Vector3){i, x, j});
        }
    }
    UnloadImage(noise);
}

Chunk *chunk_find(Chunk **loadedChunks, int *loadedChunksCount, Vector3 pos)
{
    Vector3 chunk_pos = worldPositionToChunk(pos);
    for (int i = 0; i < *loadedChunksCount; i++)
    {
        if (loadedChunks[i]->pos.x == chunk_pos.x && loadedChunks[i]->pos.y == chunk_pos.y && loadedChunks[i]->pos.z == chunk_pos.z)
        {
            TraceLog(LOG_DEBUG, "Chunk_find: arg: %f, %f, %f res: %f, %f, %f", pos.x, pos.y, pos.z, loadedChunks[i]->pos.x, loadedChunks[i]->pos.y, loadedChunks[i]->pos.z);
            return loadedChunks[i];
        }
    }
    return 0;
}