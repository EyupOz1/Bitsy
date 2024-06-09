#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "Player.hpp"
#include "World/Chunk.hpp"
#include <vector>
#include "World/World.hpp"
#include "Utils.hpp"
#include "World/BlockData.hpp"
#include "Defines.hpp"
#include "State.hpp"

Player player;
World world;

void setup()
{
    State::get();

    player.Init();
    world.Init();
}

void update()
{
    player.Update();
    world.Update(player.position);
    world.Draw();
}
void ui()
{
    int y = 0;
    int step = 20;
    DrawText(TextFormat("playerPos: (%f, %f, %f)", ExpandVc3(player.position)), 0, y += step, 20, BLACK);
    DrawTexture(State::get().atlas, 0, y += step, WHITE);
}

int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1080, 720, "Bitsy");
    DisableCursor();
    SetTargetFPS(144);
    SetTraceLogLevel(LOG_ALL);

    setup();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode3D(player.camera);
        update();
        EndMode3D();

        ui();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
