#pragma once

#include "raylib.h"
#include "Chunk.h"
#include "../entity/Player.h"

void chunkSystem_init();
void chunkSystem_update(Player *player, Chunk **loadedChunks, int *loadedChunksCount, Shader shader, Texture2D tex);