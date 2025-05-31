// openingScene.c
#include "raylib.h"
#include "stateController.h"
#include "dialogues.h"
#include <stdio.h>
#include <string.h>

// 對話資料
static DialogueLine* openingLines = NULL;
static int totalLines = 0;

static int currentLineIndex = 0;
static int currentCharIndex = 0;
static float charTimer = 0.0f;
static const float charDelay = 0.03f;

static bool isDone = false;

static void EnterOpening(void)
{
    openingLines = openingDialogue;
    totalLines = openingDialogueCount;

    currentLineIndex = 0;
    currentCharIndex = 0;
    charTimer = 0.0f;
    isDone = false;
}

static void UpdateOpening(void)
{
    if (isDone) return;

    charTimer += GetFrameTime();
    if (charTimer >= charDelay) {
        charTimer = 0.0f;
        const char* text = openingLines[currentLineIndex].text;
        if (currentCharIndex < (int)strlen(text)) {
            currentCharIndex++;
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        const char* text = openingLines[currentLineIndex].text;
        if (currentCharIndex < (int)strlen(text)) {
            currentCharIndex = strlen(text); // 顯示完整
        } else {
            currentLineIndex++;
            currentCharIndex = 0;
            charTimer = 0.0f;
            if (currentLineIndex >= totalLines) {
                isDone = true;
                GOTO(PLAYING); // 切到遊戲狀態
            }
        }
    }
}

static void RenderOpening(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    if (currentLineIndex < totalLines) {
        const char* text = openingLines[currentLineIndex].text;
        Rectangle bounds = {
            .x = 50,
            .y = GetScreenHeight() / 2 - 100,
            .width = GetScreenWidth() - 100,
            .height = 200
        };
        DrawWrappedTextWithLimit(text, bounds, 28, WHITE, currentCharIndex);
    }
}

static void ExitOpening(void) {}

const GameState STATE_OPENING_CUTSCENE = {
    .enter = EnterOpening,
    .update = UpdateOpening,
    .render = RenderOpening,
    .exit = ExitOpening
};
