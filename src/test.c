
#include "Test.h"

void test_world(Chunk *Chnk)
{

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                chunk_block_add(Chnk, (Block){.BlockID = 1}, (Vector3){i, j, k});
            }
        }
    }
}

void test_world2(Chunk *Chnk)
{
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                if (j == 0)
                {
                    chunk_block_add(Chnk, (Block){.BlockID = 1}, (Vector3){i, j, k});
                }
            }
        }
    }
}

void test_world3(Chunk *Chnk)
{
    chunk_block_add(Chnk, (Block){.BlockID = 1}, (Vector3){0, 0, 0});
    chunk_block_add(Chnk, (Block){.BlockID = 1}, (Vector3){CHUNK_SIZE - 1, CHUNK_SIZE - 1, CHUNK_SIZE - 1});
}