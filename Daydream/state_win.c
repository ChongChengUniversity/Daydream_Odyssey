#include "raylib.h"
#include "stateController.h"
#include "config.h"
#include "audioManager.h"
#include "levelManager.h"
#include "CardManager.h"

const char* labelGameWin = "YOU WIN";
static const char* labelEnter = "PRESS ENTER FOR MAIN MENU";

static void EnterWin() {}

static void UpdateWin() {
    if (IsKeyPressed(KEY_ENTER))
    {
        GamePlaySound(SOUND_TWO);
        InitLevelManager();  //  加這行：重設到第一關
        GOTO(MAIN_MENU);
    }
}

static void RenderWin() {
    DrawAllCards(); // 改這裡
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.8f));
    DrawText(labelGameWin, SCREEN_WIDTH / 2 - MeasureText(labelGameWin, 60) / 2, SCREEN_HEIGHT / 2 - 10, 60, DARKGRAY);
    DrawText(labelEnter, SCREEN_WIDTH / 2 - MeasureText(labelEnter, 34) / 2, (int)(SCREEN_HEIGHT * 0.75f) - 10, 34, DARKGRAY);
}

static void ExitWin() {}

const GameState STATE_WIN = {
    .enter = EnterWin,
    .update = UpdateWin,
    .render = RenderWin,
    .exit = ExitWin
};
