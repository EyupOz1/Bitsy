#include "World.hpp"
#include "Core/Utils.hpp"
#include <vector>
#include "raymath.h"
#include "Core/Defines.hpp"
#include "Core/Math/Vector3Int.hpp"

void World::Update(Vector3Int playerChunkPos)
{
    std::vector<Vector3Int> chunksToLoad;

    int renderRadius = (RENDER_DISTANCE - 1) / 2;
    for (int i = -renderRadius; i <= renderRadius; i++)
    {
        for (int j = -renderRadius; j <= renderRadius; j++)
        {
            for (int k = -renderRadius; k <= renderRadius; k++)
            {
                chunksToLoad.push_back(Vector3IntAdd(playerChunkPos, {i * CHUNK_SIZE, j * CHUNK_SIZE, k * CHUNK_SIZE}));
            }
        }
    }

        for (int i = 0; i < chunksToLoad.size(); i++)
    {
        bool alreadyExists = false;
        for (int j = 0; j < this->loadedChunks.size(); j++)
        {
            if (Vector3IntCompare(chunksToLoad[i], this->loadedChunks[j]->position))
            {
                alreadyExists = true;
                break;
            }
        }
        if (!alreadyExists)
        {

            Chunk *newChunk = new Chunk();
            newChunk->Init(chunksToLoad[i]);
            this->loadedChunks.push_back(newChunk);
        }
        
    } 

    for (int i = 0; i < this->loadedChunks.size(); i++)
    {
        bool exists = false;
        for (int j = 0; j < chunksToLoad.size(); j++)
        {
            if (Vector3IntCompare(chunksToLoad[j], this->loadedChunks[i]->position))
            {
                exists = true;
                break;
            }
        }
        if (!exists)
        {
            this->loadedChunks[i]->Destroy();
            this->loadedChunks.erase(this->loadedChunks.begin() + i);
            break;
        }
        
    }


}
