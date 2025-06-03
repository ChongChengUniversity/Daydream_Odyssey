#include "config.h"
#include "game.h"
#include "stateController.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib:: Minesweeper");
    SetTargetFPS(60);//把while(!WindowShouldClose)控制在每1/60秒跑一次
    GameStartup();

    while (!WindowShouldClose()) {
        if (currentState && currentState->update) currentState->update();

        BeginDrawing();
        ClearBackground(DARKGREEN);
        if (currentState && currentState->render) currentState->render();
        EndDrawing();
    }

    GameShutdown();
    CloseWindow();

    return 0;
}
