#include "World.hpp"
#include "Utils.hpp"
#include <vector>
#include "raymath.h"
#include <algorithm>
#include "State.hpp"
#include "Defines.hpp"

void World::Init() {};

void World::Draw()
{
    int lower = this->loadedChunks.size();
    for (int i = 0; i < lower; i++)
    {
        this->loadedChunks[i]->Draw();
    }
};

void World::calculateChunksToLoad(Vector3 playerPos, std::vector<Vector3> &chunksToLoad)
{
    int renderDistance = State::get().renderDistance;

    std::vector<int> possibleDistances;

    int f = 1;
    possibleDistances.push_back(0);
    for (int i = possibleDistances.size(); i < renderDistance; i++)
    {
        if (i % 2 == 0)
        {
            possibleDistances.push_back(CHUNK_SIZE * f++);
        }
        else
        {
            possibleDistances.push_back(-(CHUNK_SIZE * f));
        }
    }

    for (int i = 0; i < possibleDistances.size(); i++)
    {
        for (int j = 0; j < possibleDistances.size(); j++)
        {
            for (int k = 0; k < possibleDistances.size(); k++)
            {
                Vector3 newVec = Vector3Add(
                    {roundToChunk(playerPos.x), roundToChunk(playerPos.y), roundToChunk(playerPos.z)},
                    {static_cast<float>(possibleDistances[i]), static_cast<float>(possibleDistances[j]), static_cast<float>(possibleDistances[k])});

                chunksToLoad.push_back(newVec);
            }
        }
    }
}

void World::Update(Vector3 playerPos)
{

    std::vector<Vector3> chunksToLoad;
    this->calculateChunksToLoad(playerPos, chunksToLoad);

    int s = chunksToLoad.size();

    for (int i = 0; i < chunksToLoad.size(); i++)
    {
        int chunkIndex = this->findChunkByPos(chunksToLoad[i]);

        if (chunkIndex >= 0)
        {
            this->loadedChunks[chunkIndex]->Update();
            continue;
        }

        Chunk *newChunk = new Chunk();
        newChunk->Init(chunksToLoad[i]);

        newChunk->perlin();
        newChunk->Update();

        this->loadedChunks.push_back(newChunk);
    }
    std::sort(this->loadedChunks.begin(), this->loadedChunks.end(), [&playerPos](const auto &lhs, const auto &rhs)
              { return Vector3DistanceSqr(Vector3AddValue(lhs->position, CHUNK_SIZE / 2), playerPos) < Vector3DistanceSqr(Vector3AddValue(rhs->position, CHUNK_SIZE / 2), playerPos); });

    // TraceLog(LOG_DEBUG, "Size: %i, FE: %f, %f, %f, LAST: %f, %f, %f", this->loadedChunks.size(), ExpandVc3(this->loadedChunks[0]->position), ExpandVc3(this->loadedChunks.back()->position));
    int x = this->loadedChunks.size();

    int renderDist = State::get().renderDistance;
    for (int i = this->loadedChunks.size() - 1; i >= renderDist * renderDist * renderDist + 1; --i)
    {
        //TraceLog(LOG_DEBUG, "Del %i", i);
        this->loadedChunks[i]->Destroy();
        this->loadedChunks.erase(this->loadedChunks.end());
    }

    int a = this->loadedChunks.size();

    // TraceLog(LOG_DEBUG, "X");
}

unsigned char Vector3Compare(Vector3 a, Vector3 b)
{
    if (a.x == b.x && a.y == b.y && a.z == b.z)
    {
        return 1;
    }

    return 0;
}

int World::findChunkByPos(Vector3 pos)
{
    Vector3 chunk_pos = {roundToChunk(pos.x), roundToChunk(pos.y), roundToChunk(pos.z)};
    for (int i = 0; i < this->loadedChunks.size(); i++)
    {
        if (Vector3Compare(chunk_pos, this->loadedChunks[i]->position))
        {
            // TraceLog(LOG_DEBUG, "Chunk_find: arg: %f, %f, %f res: %f, %f, %f", pos.x, pos.y, pos.z, chunkSys->loadedChunks[i]->pos.x, chunkSys->loadedChunks[i]->pos.y, chunkSys->loadedChunks[i]->pos.z);
            return i;
        }
    }
    return -1;
}
