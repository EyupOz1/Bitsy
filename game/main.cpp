#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "Player.hpp"
#include "World/Chunk.hpp"
#include <vector>
#include "World/World.hpp"
#include "Core/Utils.hpp"
#include "World/BlockData.hpp"
#include "Core/Defines.hpp"
#include "Core/State.hpp"

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
    int y = -20;
    int step = 20;
    DrawText(TextFormat("%i", GetFPS()), 0, y += step, 20, BLACK);
    DrawText(TextFormat("playerPos: (%f, %f, %f)", ExpandVc3(player.position)), 0, y += step, 20, BLACK);
    DrawTexture(State::get().atlas, 0, y += step, WHITE);
    DrawText(TextFormat("%i", world.loadedChunks.size()), 0, y += step, 20, BLACK);

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
