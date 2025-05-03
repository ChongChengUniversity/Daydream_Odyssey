#include "raylib.h"
#include "stateController.h"
#include "config.h"
#include "audioManager.h"
#include "CardManager.h"
#include "levelManager.h"

static const char* labelGameLose = "GAME OVER";
static const char* labelEnter = "TRY AGAIN (PRESS ENTER)";

static void EnterLose() {}

static void UpdateLose() {
    if (IsKeyPressed(KEY_ENTER))
    {
        GamePlaySound(SOUND_TWO);
        InitLevelManager();
        ResetAllCards();
        GOTO(PLAYING);
    }
}

static void RenderLose() {
    DrawAllCards();
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.8f));
    DrawText(labelGameLose, SCREEN_WIDTH / 2 - MeasureText(labelGameLose, 60) / 2, SCREEN_HEIGHT / 2 - 10, 60, DARKGRAY);
    DrawText(labelEnter, SCREEN_WIDTH / 2 - MeasureText(labelEnter, 34) / 2, (int)(SCREEN_HEIGHT * 0.75f) - 10, 34, DARKGRAY);
}

static void ExitLose() {}

const GameState STATE_LOSE = {
    .enter = EnterLose,
    .update = UpdateLose,
    .render = RenderLose,
    .exit = ExitLose
};
