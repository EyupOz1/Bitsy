#include "Block.h"
#include "string.h"

/* Mesh block_mesh_create(short Face_Mask)
{

    Mesh mesh = {0};

    float vertices[] = {};

    unsigned short indices[] = {

    }

                               mesh.vertices = (float *)RL_MALLOC(24 * 3 * sizeof(float));
    memcpy(mesh.vertices, vertices, 24 * 3 * sizeof(float));

    mesh.indices = (unsigned short *)RL_MALLOC(36 * sizeof(unsigned short));
    memcpy(mesh.indices, indices, 24 * 3 * sizeof(unsigned short));

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
} */

Mesh Block_Draw()
{

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

        0, 1, 3,
        3, 1, 2,

        1, 5, 2,
        2, 5, 6,

        5, 4, 6,
        6, 4, 7,

        4, 0, 7,
        7, 0, 3,

        3, 2, 7,
        7, 2, 6,

        4, 5, 0,
        0, 5, 1

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
 

Texture2D block_texture_create()
{

    Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);

    return texture;
}


Model blockToModel(Block block)
{

}