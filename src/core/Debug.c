#include "../world/Chunk.h"
#include "raymath.h"

void debug_chunk_show(Chunk *chunk) {
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

  for (int i = 0; i < CHUNK_SIZE; i++) {
    DrawSphere((Vector3){chunk->pos.x + i, 0, 0}, 0.1f, BLUE);
    DrawSphere((Vector3){0, 0, chunk->pos.z + i}, 0.1f, BLUE);
    DrawSphere((Vector3){0, chunk->pos.z + i, 0}, 0.1f, BLUE);
  }
}
