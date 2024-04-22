#include "World.h"

int roundToSixteen(int x)
{
    int nearestMultiple = (x / 16) * 16;

/*     if (x - nearestMultiple > 8)
    {
        nearestMultiple += 16;
    } */

    return nearestMultiple;
}

Chunk *getChunk(World *world, Vector3 pos)
{
    Vector3 pos1 = (Vector3){roundToSixteen(pos.x), roundToSixteen(pos.y), roundToSixteen(pos.z)};
    printf("%f, %f, %f\n", pos1.x, pos1.y, pos1.z);
    for (int i = 0; i < 5; i++)
    {
        
    }
    

    return 0;
}

void World_getChunkFromPlayer(Player *player, World *world)
{
    printf("tset a%f, %f, %f\n", player->player_camera.position.x, player->player_camera.position.y, player->player_camera.position.z);

    Chunk* pos = getChunk(world, player->player_camera.position);
}