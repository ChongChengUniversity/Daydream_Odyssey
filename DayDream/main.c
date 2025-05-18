// main.c
#include "config.h"
#include "game.h"
#include "stateController.h"
#include "assetManager.h"
#include "audioManager.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib:: Minesweeper");
    SetTargetFPS(60); // fps = 1/60
    GameStartup(); // include init audio

    while (!WindowShouldClose()) {
        UpdateMusicStream(music[MUSIC_ONE]);

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
