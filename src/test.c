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
            Chnk->Blocks[i][HighestValue][j] = (Block){.BlockID = 1};
        }
    }
}