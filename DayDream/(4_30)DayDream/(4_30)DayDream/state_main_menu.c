#include "raylib.h"
#include "stateController.h"
#include "config.h"
#include "audioManager.h"

static void EnterMainMenu() {
    // 例如播放背景音樂、重設變數等
}

static void UpdateMainMenu() {
    if (IsKeyPressed(KEY_N)) {
        GamePlaySound(SOUND_TWO);
        GOTO(PLAYING);
    }
    else if (IsKeyPressed(KEY_O)) {
        GamePlaySound(SOUND_TWO);
        GOTO(OPTION_MENU);
    }
}

static void RenderMainMenu() {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKBLUE);
    DrawText("DAYDREAM", 20, 20, 40, WHITE);
    DrawText("[N]ew Game", 120, 220, 20, WHITE);
    DrawText("[O]ptions", 120, 250, 20, WHITE);
    DrawText("ESC to QUIT", 120, 280, 20, WHITE);
}

static void ExitMainMenu() {
    // 例如停止背景音樂等
}

const GameState STATE_MAIN_MENU = {
    .enter = EnterMainMenu,
    .update = UpdateMainMenu,
    .render = RenderMainMenu,
    .exit = ExitMainMenu
};