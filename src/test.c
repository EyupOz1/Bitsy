#include "Chunk.h"
#include "Block.h"
#include "main.h"

void test_world(Chunk *Chnk)
{

    const int HighestValue = (CHUNK_SIZE)-1;

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                Chnk->Blocks[i][j][k] = (Block){.BlockID = 1};
            }
        }
    }
}