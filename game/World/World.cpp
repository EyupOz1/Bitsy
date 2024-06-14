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
    this->updateLoadedChunks(playerPos);
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
/*
void World::place(Vector3Int pos, Block &block)
{
    Vector3Int res = pos;

    int x = this->findChunkByPos(res);
    if (x == -1)
    {
        TraceLog(LOG_DEBUG, "WorldPlace Chunk doesnt exist");
        return;
    }

    Chunk *ch = this->loadedChunks[x];

    Vector3 chpos = Vector3Subtract(pos.toVec3(), res.toVec3());
    ch->setBlock(Vector3Int::Vec3ToVec3Int(chpos), block, true);
}
*/

void World::updateLoadedChunks(Vector3 playerPos)
{
    std::vector<Vector3Int> chunksToLoad;
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
                  { return Vector3DistanceSqr(Vector3AddValue(Vec3IntToVec3(lhs->position), CHUNK_SIZE / 2), playerPos) < Vector3DistanceSqr(Vector3AddValue(Vec3IntToVec3(rhs->position), CHUNK_SIZE / 2), playerPos); });
    }

    if (this->loadedChunks.size() > 512)
    {

        while (this->loadedChunks.size() > chunksToLoad.size())
        {
            this->loadedChunks.back()->Destroy();
            delete this->loadedChunks.back();
            this->loadedChunks.pop_back();
        }
    }
}

int World::findChunkByPos(Vector3Int pos)
{
    Vector3Int chunk_pos = {roundToChunk(pos.x), roundToChunk(pos.y), roundToChunk(pos.z)};
    for (int i = 0; i < this->loadedChunks.size(); i++)
    {
        if (Vector3IntCompare(chunk_pos, this->loadedChunks[i]->position))
        {
            // TraceLog(LOG_DEBUG, "Chunk_find: arg: %f, %f, %f res: %f, %f, %f", pos.x, pos.y, pos.z, chunkSys->loadedChunks[i]->pos.x, chunkSys->loadedChunks[i]->pos.y, chunkSys->loadedChunks[i]->pos.z);
            return i;
        }
    }
    return -1;
}

void World::calculateChunksToLoad(Vector3 playerPos, std::vector<Vector3Int> &chunksToLoad)
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
                Vector3Int newVec = {
                    roundToChunk(playerPos.x) + possibleDistances[i],
                    roundToChunk(playerPos.y) + possibleDistances[j],
                    roundToChunk(playerPos.z) + possibleDistances[k]};

                if (Vector3Distance(playerPos, Vec3IntToVec3(newVec)) < renderDistance * CHUNK_SIZE)
                {
                    chunksToLoad.push_back(newVec);
                }
            }
        }
    }
}
