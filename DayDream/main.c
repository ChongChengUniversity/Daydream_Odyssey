// main.c
#include "config.h"
#include "game.h"
#include "stateController.h"
#include "assetManager.h"
#include "audioManager.h"
#include "story.h"

// 新增一個標誌來處理 Bad End 對話結束後的跳轉
static bool badEndDialogueActive = false;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Daydream Odyssey");
    SetTargetFPS(60); // fps = 1/60
    GameStartup();    // include init audio

    InitStorySystem();

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music[MUSIC_ONE]);

        // 優先處理對話，然後是結局選擇，最後是遊戲狀態
        if (IsDialogueActive() && GetCurrentGameState() != ENDING_CHOICE)
        { // 如果不是在結局選擇狀態，才讓 story 獨立更新
            UpdateStory();
        }
        else if (GetCurrentGameState() == ENDING_CHOICE)
        {
            // 在結局選擇狀態下，由 endingChoice.c 處理 UpdateStory()
            currentState->update();
        }
        else if (currentState && currentState->update)
        {
            currentState->update();
        }

        BeginDrawing();
        ClearBackground(DARKGREEN);

        // rendering
        if (currentState && currentState->render)
            currentState->render();

        // 如果當前不在結局選擇狀態，則繪製故事對話框
        // 結局選擇狀態會在其自身的 Render 函式中呼叫 RenderStory
        if (GetCurrentGameState() != ENDING_CHOICE)
        {
            RenderStory(); // render story scene
        }

        // 處理 Bad End 對話結束後的跳轉
        if (badEndDialogueActive && GetDialogueState() == DIALOGUE_STATE_NONE)
        {
            badEndDialogueActive = false; // 對話結束，重置標誌
            GOTO(LOSE);                   // 跳轉到失敗畫面
        }

        EndDrawing();
    }

    GameShutdown();
    CloseWindow();

    return 0;
}
