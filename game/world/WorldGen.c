#include "WorldGen.h"

void worldGen_generate(Chunk *chunk)
{
    if (chunk->pos.y == 0)
    {

        Image noise = GenImagePerlinNoise(CHUNK_SIZE, CHUNK_SIZE, chunk->pos.x, chunk->pos.y, 1);
        for (int i = 0; i < CHUNK_SIZE; i++)
        {
            for (int j = 0; j < CHUNK_SIZE; j++)
            {
                unsigned char height = GetImageColor(noise, i, j).g;

                float x = map(height, 0, 255, 0, CHUNK_SIZE - 1);

                chunk_block_add(chunk, (Block){.BlockID = 1}, (Vector3){i, x, j});
                for (int s = x - 1; s >= 0; s--)
                {
                    chunk_block_add(chunk, (Block){.BlockID = 2}, (Vector3){i, s, j});
                }
            }
        }
        UnloadImage(noise);
    }
}
