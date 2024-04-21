#include "raylib.h"
#include "Block.h"
#include "Chunk.h"
#include "main.h"

Mesh chunk_mesh_create(Chunk *Chnk)
{

    int vert_i = 0;
    int ind_i = 0;
    int vertices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    unsigned short indices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

    Mesh chnk_mesh = {0};

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                if (Chnk->Blocks[i][j][k].BlockID < 1)
                {
                    continue;
                }

                if (j > 0 && Chnk->Blocks[i][j - 1][k].BlockID < 1) // FIXME: What if unassigned stack coincedently is 0?
                {
                    chnk_mesh.triangleCount += 2;
                    int cpy = vert_i;

                    // 0
                    vertices[vert_i++] = 0 + i;
                    vertices[vert_i++] = 0 + j;
                    vertices[vert_i++] = 0 + k;
                    // 6
                    vertices[vert_i++] = 1 + i;
                    vertices[vert_i++] = 0 + j;
                    vertices[vert_i++] = 1 + k;
                    // 7
                    vertices[vert_i++] = 0 + i;
                    vertices[vert_i++] = 0 + j;
                    vertices[vert_i++] = 1 + k;
                    // 1
                    vertices[vert_i++] = 1 + i;
                    vertices[vert_i++] = 0 + j;
                    vertices[vert_i++] = 0 + k;

                    int null = cpy;
                    int six = null + 3 ;
                    int seven = six + 3;
                    int one = seven + 3;

                    indices[ind_i++] = null;
                    indices[ind_i++] = six;
                    indices[ind_i++] = seven;
                    indices[ind_i++] = null;
                    indices[ind_i++] = one;
                    indices[ind_i++] = six;
                }
            }
        }
    }

int ve = 0;
    for (int i = 0; i < vert_i; i++)
    {

        printf("%i,", vertices[i]);
        ve++;
        if (ve==3)
        {
            ve = 0;
            printf("\n");
        }
        
    }

    int ze = 0;
    for (int i = 0; i < ind_i; i++)
    {

        printf("%i,", indices[i]);
        ze++;
        if (ze==3)
        {
            ze = 0;
            printf("\n");
        }
        
    }
    

    chnk_mesh.vertexCount = vert_i / 3;

    chnk_mesh.vertices = (float *)RL_MALLOC((vert_i) * sizeof(int));
    chnk_mesh.indices = (unsigned short *)RL_MALLOC((ind_i ) * sizeof(unsigned short));

    memcpy(chnk_mesh.vertices, vertices, (vert_i) * sizeof(int));
    memcpy(chnk_mesh.indices, indices, (ind_i ) * sizeof(unsigned short));

    UploadMesh(&chnk_mesh, false);
    return chnk_mesh;
}