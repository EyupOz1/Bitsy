#pragma once
#include "Chunk.h"
#include "raylib.h"
#include "Player.h"
#include "raymath.h"
#include "stdio.h"
#include "Test.h"


Vector3 world_PosToChunk(Vector3 pos);
void world_chunk_update(Player *player, Chunk **loadedChunks, int* loadedChunksCount);
void world_chunk_draw(Chunk **loadedChunks, int *loadedChunksCount);