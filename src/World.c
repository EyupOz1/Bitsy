#include "World.h"

Vector3 getChunkPos(Vector3 pos)
{
    return (Vector3){(int)(pos.x / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.y / CHUNK_SIZE) * CHUNK_SIZE, (int)(pos.z / CHUNK_SIZE) * CHUNK_SIZE};
}



void world_chunk_update(World);
