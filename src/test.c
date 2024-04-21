#include "Chunk.h"
#include "Block.h"

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

void test_world2(Chunk *Chnk)
{

    Chnk->Blocks[0][0][0] = (Block){.BlockID = 1};
    Chnk->Blocks[0][1][0] = (Block){.BlockID = 1};
    Chnk->Blocks[0][2][0] = (Block){.BlockID = 1};

    Chnk->Blocks[2][2][2] = (Block){.BlockID = 1};
    Chnk->Blocks[1][2][2] = (Block){.BlockID = 1};
    Chnk->Blocks[3][2][2] = (Block){.BlockID = 1};

    Chnk->Blocks[3][3][3] = (Block){.BlockID = 1};
}

void test_world3(Chunk *Chnk)
{

    Chnk->Blocks[1][1][1] = (Block){.BlockID = 1};

}