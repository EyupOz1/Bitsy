#include "../world/Chunk.h"
#include "raymath.h"

void debug_chunk_show(Chunk *chunk)
{
  Vector3 pos[] = {
      Vector3Add(chunk->pos, (Vector3){0, 0, 0}),
      Vector3Add(chunk->pos, (Vector3){CHUNK_SIZE, 0, 0}),
      Vector3Add(chunk->pos, (Vector3){0, 0, CHUNK_SIZE}),
      Vector3Add(chunk->pos, (Vector3){CHUNK_SIZE, 0, CHUNK_SIZE}),
      Vector3Add(chunk->pos, (Vector3){0, CHUNK_SIZE, 0}),
      Vector3Add(chunk->pos, (Vector3){CHUNK_SIZE, CHUNK_SIZE, 0}),
      Vector3Add(chunk->pos, (Vector3){0, CHUNK_SIZE, CHUNK_SIZE}),
      Vector3Add(chunk->pos, (Vector3){CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}),

  };

  /*     DrawLine3D(chunk->pos, Vector3Add(chunk->pos, (Vector3){CHUNK_SIZE, 0,
     0}), GREEN); DrawLine3D(chunk->pos, Vector3Add(chunk->pos, (Vector3){0, 0,
     CHUNK_SIZE}), GREEN); DrawLine3D(chunk->pos, Vector3Add(chunk->pos,
     (Vector3){CHUNK_SIZE, 0, 0}), GREEN); DrawLine3D(chunk->pos,
     Vector3Add(chunk->pos, (Vector3){0, 0, CHUNK_SIZE}), GREEN); */

  for (int i = 0; i < CHUNK_SIZE; i++)
  {
    DrawSphere((Vector3){chunk->pos.x + i, 0, 0}, 0.1f, BLUE);
    DrawSphere((Vector3){0, 0, chunk->pos.z + i}, 0.1f, BLUE);
    DrawSphere((Vector3){0, chunk->pos.z + i, 0}, 0.1f, BLUE);
  }
}

Mesh mesh_block()
{

  Mesh mesh = {0};
  float vertices[] = {
      // Pos Z
      1, 0, 0,
      1, 0, 1,
      1, 1, 1,
      1, 1, 0,
      // Neg Z
      0, 0, 0,
      0, 1, 0,
      0, 1, 1,
      0, 0, 1,
      // Pos Y
      0, 1, 0,
      1, 1, 0,
      1, 1, 1,
      0, 1, 1,
      // Neg Y
      0, 0, 0,
      0, 0, 1,
      1, 0, 1,
      1, 0, 0,
      // Pos X
      0, 0, 1,
      0, 1, 1,
      1, 1, 1,
      1, 0, 1,
      // Neg Z
      0, 0, 0,
      1, 0, 0,
      1, 1, 0,
      0, 1, 0};

  mesh.vertices = (float *)RL_MALLOC(24 * 3 * sizeof(float));
  memcpy(mesh.vertices, vertices, 24 * 3 * sizeof(float));

  mesh.indices = (unsigned short *)RL_MALLOC(36 * sizeof(unsigned short));

  int k = 0;
  for (int i = 0; i < 36; i += 6)
  {
    mesh.indices[i + 5] = 4 * k;
    mesh.indices[i + 4] = 4 * k + 1;
    mesh.indices[i + 3] = 4 * k + 2;
    mesh.indices[i + 2] = 4 * k;
    mesh.indices[i + 1] = 4 * k + 2;
    mesh.indices[i] = 4 * k + 3;

    k++;
  }

  mesh.vertexCount = 24;
  mesh.triangleCount = 12;

  UploadMesh(&mesh, false);

  return mesh;
}