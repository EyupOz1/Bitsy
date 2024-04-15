#include "player.h"


// Player *playerptr = player_create();
Player* player_create() {

    Player* new_player = RL_MALLOC(sizeof(Player));
    new_player->player_camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    new_player->player_camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    new_player->player_camera.fovy = 60.0f;
    new_player->player_camera.projection = CAMERA_PERSPECTIVE;

    return new_player;
}



