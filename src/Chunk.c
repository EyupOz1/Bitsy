#include "Chunk.h"
Mesh chunk_mesh_create(Chunk *Chnk)
{

    Mesh mesh = {0};
    mesh.triangleCount = 0;
    mesh.vertexCount = 0;

    float vertices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 3] = {0};
    unsigned short indices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 3] = {0};

    long int BlockCount = 0;

    long int indices_index = 0;
    long int vertex_index = 0;

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                if (Chnk->Blocks[i][j][k].BlockID > 0)
                {
                    printf("Found Block: %i\n", Chnk->Blocks[i][j][k].BlockID);

                    float localVertices[] = {

                        1 + i, 1 + j, 1 + k,
                        0 + i, 1 + j, 1 + k,
                        0 + i, 0 + j, 1 + k,
                        1 + i, 0 + j, 1 + k,

                        1 + i, 1 + j, 0 + k,
                        0 + i, 1 + j, 0 + k,
                        0 + i, 0 + j, 0 + k,
                        1 + i, 0 + j, 0 + k

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

                    for (int index = 0; index < 24; index++)
                    {
                        vertices[vertex_index++] = localVertices[index];
                    }

                    if (i + 1 >= CHUNK_SIZE || Chnk->Blocks[i + 1][j][k].BlockID == 0)
                    {
                        for (int l = 0; l < 6; l++)
                        {
                            indices[indices_index++] = localIndices[l];
                        }
                        mesh.triangleCount += 2;
                    }

                    if (i - 1 >= CHUNK_SIZE || Chnk->Blocks[i + -1][j][k].BlockID == 0)
                    {
                        for (int l = 6; l < 12; l++)
                        {
                            indices[indices_index++] = localIndices[l];
                        }
                        mesh.triangleCount += 2;
                    }

                    if (j + 1 >= CHUNK_SIZE || Chnk->Blocks[i][j + 1][k].BlockID == 0)
                    {
                        for (int l = 12; l < 18; l++)
                        {
                            indices[indices_index++] = localIndices[l];
                        }
                        mesh.triangleCount += 2;
                    }

                    if (j - 1 >= CHUNK_SIZE || Chnk->Blocks[i][j - 1][k].BlockID == 0)
                    {
                        for (int l = 18; l < 24; l++)
                        {
                            indices[indices_index++] = localIndices[l];
                        }
                        mesh.triangleCount += 2;
                    }

                    if (k + 1 >= CHUNK_SIZE || Chnk->Blocks[i][j][k + 1].BlockID == 0)
                    {
                        for (int l = 24; l < 30; l++)
                        {
                            indices[indices_index++] = localIndices[l];
                        }
                        mesh.triangleCount += 2;
                    }

                    if (k - 1 >= CHUNK_SIZE || Chnk->Blocks[i][j][k - 1].BlockID == 0)
                    {
                        for (int l = 30; l < 36; l++)
                        {
                            indices[indices_index++] = localIndices[l];
                        }
                        mesh.triangleCount += 2;
                    }

                    BlockCount++;
                }
            }
        }
    }

    for (int i = 0; i < indices_index; i++)
    {
        if (i % 6 == 0)
        {
            printf("\n");
        }

        printf("%u, ", indices[i]);
    }
    printf("\n");

    for (int i = 0; i < vertex_index; i++)
    {
        if (i % 3 == 0)
        {

            if (i % 24 == 0)
            {
                printf("\n");
            }

            printf("\n");
        }
        printf("%.2f, ", vertices[i]);
    }
    printf("\n");

    mesh.vertexCount = vertex_index / 3;

    mesh.vertices = (float *)RL_MALLOC(vertex_index * sizeof(float));
    mesh.indices = (unsigned short *)RL_MALLOC(indices_index * sizeof(unsigned short));

    memcpy(mesh.vertices, vertices, vertex_index * sizeof(float));
    memcpy(mesh.indices, indices, indices_index * sizeof(unsigned short));

    UploadMesh(&mesh, false);

    return mesh;
}