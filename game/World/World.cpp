#include "World.hpp"
#include "Core/Utils.hpp"
#include <vector>
#include "raymath.h"
#include <algorithm>
#include "Core/State.hpp"
#include "Core/Defines.hpp"

void World::Init() {
    // this->loadedChunks.reserve(State::get().renderDistance);
};


void World::Update(Vector3 playerPos)
{
    // if (GetFPS() % 2 == 0) // Weird way to only update the chunks every second frame
    {
        this->updateLoadedChunks(playerPos);
    }

}

void World::Draw()
{

    int UpperBound = this->loadedChunks.size();
    int renderCount = State::get().renderDistance * State::get().renderDistance * State::get().renderDistance;
    if (UpperBound > renderCount)
    {
        UpperBound = renderCount;
    }

    for (int i = 0; i < UpperBound; i++)
    {
        this->loadedChunks[i]->Draw();
    }
};


void World::place(Vector3 pos, Block &block)
{
        Vector3 res = {roundToChunk(pos.x), roundToChunk(pos.y), roundToChunk(pos.z)};

        int x = this->findChunkByPos(res);
        if (x == -1)
        {
            TraceLog(LOG_DEBUG, "WorldPlace Chunk doesnt exist");
            return;
        }

        
        
        Chunk* ch = this->loadedChunks[x];

        Vector3 chpos = Vector3Subtract(pos, res);
        ch->setBlock(chpos, block);

}

void World::updateLoadedChunks(Vector3 playerPos)
{
    std::vector<Vector3> chunksToLoad;
    this->calculateChunksToLoad(playerPos, chunksToLoad);

    bool chunkAdded = false;

    for (int i = 0; i < chunksToLoad.size(); i++)
    {
        int chunkIndex = this->findChunkByPos(chunksToLoad[i]);

        if (chunkIndex >= 0)
        {
            this->loadedChunks[chunkIndex]->Update();
            continue;
        }

        chunkAdded = true;

        Chunk *newChunk = new Chunk();
        newChunk->Init(chunksToLoad[i]);

        newChunk->perlin();
        newChunk->Update();

        this->loadedChunks.push_back(newChunk);
    }

    if (chunkAdded)
    {

        std::sort(this->loadedChunks.begin(), this->loadedChunks.end(), [&playerPos](const auto &lhs, const auto &rhs)
                  { return Vector3DistanceSqr(Vector3AddValue(lhs->position, CHUNK_SIZE / 2), playerPos) < Vector3DistanceSqr(Vector3AddValue(rhs->position, CHUNK_SIZE / 2), playerPos); });
    }

    if (this->loadedChunks.size() > 500)
    {

        while (!this->loadedChunks.empty())
        {
            this->loadedChunks.back()->Destroy();
            delete this->loadedChunks.back();
            this->loadedChunks.pop_back();
        }
    }
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

                if (Vector3Distance(playerPos, newVec) < renderDistance * CHUNK_SIZE)
                {
                    chunksToLoad.push_back(newVec);
                }
            }
        }
    }
}
