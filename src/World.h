#pragma once
#include "Chunk.h"
#include "raylib.h"
#include "Player.h"
#include "raymath.h"
#include "stdio.h"
#include "Utils.h"


void world_chunk_update(Player *player, Chunk **loadedChunks, int* loadedChunksCount);
void world_chunk_draw(Chunk **loadedChunks, int *loadedChunksCount, Shader shader, Texture2D tex);