#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "lib.h"

Camera camera;

void setup()
{
    camera = (Camera){.fovy = 90, .position = (Vector3){0, 0, 0}, .projection = CAMERA_PERSPECTIVE, .target = Vector3One(), .up = (Vector3){0, 1, 0}};
}

void update()
{
    UpdateCamera(&camera, CAMERA_FREE);
    DrawCube(Vector3Zero(), 1, 1, 1, BLACK);
    LibFunction();
}
void ui()
{
}

int main(void)
{
    InitWindow(1080, 720, "Bitsy");
    DisableCursor();
    SetTraceLogLevel(LOG_ALL);
    SetTargetFPS(60);

    setup();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        update();

        EndMode3D();

        ui();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
