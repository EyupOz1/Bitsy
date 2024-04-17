#include "Block.h"
#include "string.h"
#include <stdio.h>
/*
Mesh block_mesh_create(short Face_Mask)
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
void printBits(unsigned char value) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}



Mesh Block_Draw(unsigned char bitmask)
{

    unsigned char bitcpy = bitmask;

    // Count positive bits
    int total = 0;

    for (total = 0; bitcpy; total++)
    {
        bitcpy &= bitcpy - 1;
    }

    printf("%i\n\n\n%i", total, bitmask);

    printBits(bitmask);

    Mesh mesh = {0};
    mesh.triangleCount = total * 2;
    mesh.vertexCount = 8;

    float vertices[] = {

        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,
        0, 1, 1,
        1, 1, 1,
        1, 0, 1,
        0, 0, 1

    };

    unsigned short indices[total];
    int index = 0;

    if (bitmask & FRONT_BIT)
    {
        indices[index++] = 0;
        indices[index++] = 2;
        indices[index++] = 1;
        indices[index++] = 0;
        indices[index++] = 3;
        indices[index++] = 2;
    }
    if (bitmask & TOP_BIT)
    {
        indices[index++] = 2;
        indices[index++] = 3;
        indices[index++] = 4;
        indices[index++] = 2;
        indices[index++] = 4;
        indices[index++] = 5;
    }

    /*
    unsigned short indices[] = {
        0, 2, 1, // face front
        0, 3, 2,
        2, 3, 4, // face top
        2, 4, 5,
        1, 2, 5, // face right
        1, 5, 6,
        0, 7, 4, // face left
        0, 4, 3,
        5, 4, 7, // face back
        5, 7, 6,
        0, 6, 7, // face bottom
        0, 1, 6

    };
    */
    mesh.vertices = (float *)RL_MALLOC(8 * 3 * sizeof(float));
    mesh.indices = (unsigned short *)RL_MALLOC(mesh.triangleCount * 3 * sizeof(unsigned short));

    memcpy(mesh.vertices, vertices, 8 * 3 * sizeof(float));
    memcpy(mesh.indices, indices, mesh.triangleCount * 3 * sizeof(unsigned short));

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