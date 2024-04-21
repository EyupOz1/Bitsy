#include "Chunk.h"
Mesh chunk_mesh_create(Chunk *Chnk)
{

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                if (Chnk->Blocks[i][j][k].BlockID > 0)
                {
                    
                }
            }
        }
    }

    Mesh mesh = {0};
    mesh.triangleCount = 12;
    mesh.vertexCount = 8;

    float vertices[] = {

        1, 1, 1,
        0, 1, 1,
        0, 0, 1,
        1, 0, 1,

        1, 1, 0,
        0, 1, 0,
        0, 0, 0,
        1, 0, 0

    };

    float normals[] = {

        0, 0, 1,
        1, 0, 0,
        0, 0, -1,
        -1, 0, 0,
        0, 1, 0,
        0, -1, 0

    };

    unsigned short indices[] = {
        //+X
        4,
        0,
        7,
        7,
        0,
        3,

        //-X
        1,
        5,
        2,
        2,
        5,
        6,

        //+Y
        4,
        5,
        0,
        0,
        5,
        1,

        //-Y
        3,
        2,
        7,
        7,
        2,
        6,

        //+Z
        0,
        1,
        3,
        3,
        1,
        2,

        //-Z
        5,
        4,
        6,
        6,
        4,
        7,
    };

    mesh.vertices = (float *)RL_MALLOC(8 * 3 * sizeof(float));
    mesh.indices = (unsigned short *)RL_MALLOC(mesh.triangleCount * 3 * sizeof(unsigned short));
    mesh.normals = (float *)RL_MALLOC(6 * 3 * sizeof(float));

    memcpy(mesh.vertices, vertices, 8 * 3 * sizeof(float));
    memcpy(mesh.indices, indices, mesh.triangleCount * 3 * sizeof(unsigned short));
    memcpy(mesh.normals, normals, 6 * 3 * sizeof(float));

    UploadMesh(&mesh, false);

    return mesh;
}