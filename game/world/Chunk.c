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
    if (pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE || pos.z >= CHUNK_SIZE)
    {
        TraceLog(LOG_WARNING, "Tried Placing block out of bound");
    }

    if (Chnk->currentMesh.vaoId != 0)
    {
        UnloadMesh(Chnk->currentMesh);
    }

    Chnk->Blocks[(int)pos.x][(int)pos.y][(int)pos.z] = Blck;
    Chnk->BlocksPos[Chnk->BlockPosIndex++] = pos;
    Chnk->dirty = 1;

    
}

block_setTexCoords(Block *block, float *buf)
{
    float texCount = 4.0f;
    float stepSize = 1.0f / texCount;

    float lowerBound_posZ;
    float lowerBound_negZ;
    float lowerBound_posY;
    float lowerBound_negY;
    float lowerBound_posX;
    float lowerBound_negX;
    float upperBound_posZ;
    float upperBound_negZ;
    float upperBound_posY;
    float upperBound_negY;
    float upperBound_posX;
    float upperBound_negX;

    if (block->BlockID == 1)
    {
        upperBound_posZ = 2 * stepSize;
        upperBound_negZ = 2 * stepSize;
        upperBound_posY = 3 * stepSize;
        upperBound_negY = 1 * stepSize;
        upperBound_posX = 2 * stepSize;
        upperBound_negX = 2 * stepSize;

        lowerBound_posZ = 1 * stepSize;
        lowerBound_negZ = 1 * stepSize;
        lowerBound_posY = 2 * stepSize;
        lowerBound_negY = 0 * stepSize;
        lowerBound_posX = 1 * stepSize;
        lowerBound_negX = 1 * stepSize;
    }

    float baseTexcoords[] = {
        lowerBound_posZ, 1.0f,
        upperBound_posZ, 1.0f,
        upperBound_posZ, 0.0f,
        lowerBound_posZ, 0.0f,

        upperBound_negZ, 1.0f, 
        upperBound_negZ, 0.0f,
        lowerBound_negZ, 0.0f,
        lowerBound_negZ, 1.0f, 

        lowerBound_posY, 0.0f,
        lowerBound_posY, 1.0f, 
        upperBound_posY, 1.0f, 
        upperBound_posY, 0.0f,

        upperBound_negY, 0.0f,
        lowerBound_negY, 0.0f,
        lowerBound_negY, 1.0f, 
        upperBound_negY, 1.0f, 

        upperBound_posX, 1.0f, 
        upperBound_posX, 0.0f,
        lowerBound_posX, 0.0f,
        lowerBound_posX, 1.0f, 

        lowerBound_negX, 1.0f, 
        upperBound_negX, 1.0f, 
        upperBound_negX, 0.0f,
        lowerBound_negX, 0.0f

    };

    for (int i = 0; i < 48; i++)
    {
        buf[i] = baseTexcoords[i];
    }
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

   

    for (int i = 0; i < Chnk->BlockPosIndex; i++)
    {
        Vector3 currPos = Chnk->BlocksPos[i];
        Block currBlock = Chnk->Blocks[(int)currPos.x][(int)currPos.y][(int)currPos.z];

        if (currBlock.BlockID <= 0)
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

        

        float lowerBound = 0.5f;
        float upperBound = 1.0f;

        float baseTexcoords[48];

        block_setTexCoords(&currBlock, &baseTexcoords);

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
