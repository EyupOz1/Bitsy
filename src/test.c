
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
                    Chnk->Blocks[i][j][k] = (Block){.BlockID = 1};
                }
            }
        }
    }
}

void test_world3(Chunk *Chnk)
{

    Chnk->Blocks[0][0][0] = (Block){.BlockID = 1};
    Chnk->Blocks[CHUNK_SIZE - 1][CHUNK_SIZE - 1][CHUNK_SIZE - 1] = (Block){.BlockID = 1};
}