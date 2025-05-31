// endingChoice.c
#include "endingChoice.h"
#include "raylib.h"
#include "stateController.h" // 這裡需要引入 stateController.h 來獲取 ENDING_CHOICE 這個指標
#include "story.h"
#include "dialogues.h"
#include <stdio.h>
#include <string.h>

// 內部狀態變數
static bool choiceMade = false;
static bool chooseToLeaveResult = false; // true: 選擇離開 (True End), false: 選擇留下 (Good End)

// 選擇框位置和尺寸
#define CHOICE_BOX_WIDTH 400
#define CHOICE_BOX_HEIGHT 150
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define BUTTON_PADDING 20

// 對話內容
static DialogueLine *endingLines = NULL;
static int totalLines = 0;
static int currentLineIndex = 0;
static int currentCharIndex = 0;

static float charTimer = 0.0f;
static const float charDelay = 0.03f; // 每個字顯示間隔（秒）

static bool isDialogueDone = false;

// 選擇按鈕
static Rectangle leaveButton;
static Rectangle stayButton;

static void EnterEndingChoice(void)
{
    choiceMade = false;
    // 計算選擇框和按鈕位置
    int boxX = GetScreenWidth() / 2 - CHOICE_BOX_WIDTH / 2;
    int boxY = GetScreenHeight() / 2 - CHOICE_BOX_HEIGHT / 2;

    leaveButton = (Rectangle){boxX + BUTTON_PADDING, boxY + CHOICE_BOX_HEIGHT - BUTTON_HEIGHT - BUTTON_PADDING, BUTTON_WIDTH, BUTTON_HEIGHT};
    stayButton = (Rectangle){boxX + CHOICE_BOX_WIDTH - BUTTON_WIDTH - BUTTON_PADDING, boxY + CHOICE_BOX_HEIGHT - BUTTON_HEIGHT - BUTTON_PADDING, BUTTON_WIDTH, BUTTON_HEIGHT};
}

static void UpdateEndingDialogue(void)
{
    if (isDialogueDone || !choiceMade)
        return;

    // 每幀累積時間，逐字顯示
    charTimer += GetFrameTime();
    if (charTimer >= charDelay)
    {
        charTimer = 0.0f;
        if (currentLineIndex < totalLines)
        {
            const char *text = endingLines[currentLineIndex].text;
            if (currentCharIndex < (int)strlen(text))
            {
                currentCharIndex++;
            }
        }
    }

    // 玩家點擊，切換下一句
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        const char *text = endingLines[currentLineIndex].text;

        if (currentCharIndex < (int)strlen(text))
        {
            // 若未顯示完就點，直接跳到顯示完
            currentCharIndex = strlen(text);
        }
        else
        {
            // 否則跳下一句
            currentLineIndex++;
            currentCharIndex = 0;
            charTimer = 0.0f;

            if (currentLineIndex >= totalLines)
            {
                isDialogueDone = true;
                GOTO(WIN); // 結局完成後切狀態
            }
        }
    }
}

static void UpdateEndingChoice(void)
{
    if (choiceMade)
    {
        UpdateEndingDialogue();
        return; // 選擇已做出，不再處理按鈕點擊
    }

    // 處理按鈕點擊
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, leaveButton))
        {
            choiceMade = true;
            endingLines = ending_True;
            totalLines = ending_True_Count;
            currentLineIndex = 0;
            currentCharIndex = 0;
            charTimer = 0.0f;
            isDialogueDone = false;
        }
        else if (CheckCollisionPointRec(mousePoint, stayButton))
        {
            choiceMade = true;
            endingLines = ending_Good;
            totalLines = ending_Good_Count;
            currentLineIndex = 0;
            currentCharIndex = 0;
            charTimer = 0.0f;
            isDialogueDone = false;
        }
    }
}

static void RenderEndingDialogue(void)
{
    if (!choiceMade || isDialogueDone || currentLineIndex >= totalLines)
        return;

    const char *text = endingLines[currentLineIndex].text;

    Rectangle bounds = {
        .x = 50,
        .y = GetScreenHeight() / 2 - 100,
        .width = GetScreenWidth() - 100,
        .height = 200};

    DrawWrappedTextWithLimit(text, bounds, 28, WHITE, currentCharIndex);
}

static void RenderEndingChoice(void)
{
    // 先強制繪製全黑背景（無論是否對話中）
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    // 再畫故事對話（會疊在上面）
    if (choiceMade)
    {
        RenderEndingDialogue();
        return;
    }

    // 如果尚未選擇，畫選項
    if (!choiceMade)
    {
        int boxX = GetScreenWidth() / 2 - CHOICE_BOX_WIDTH / 2;
        int boxY = GetScreenHeight() / 2 - CHOICE_BOX_HEIGHT / 2;

        // 選項對話框邊框
        DrawRectangleLinesEx((Rectangle){boxX, boxY, CHOICE_BOX_WIDTH, CHOICE_BOX_HEIGHT}, 2.0f, WHITE);
        DrawText("What will you do?",
                 boxX + 20,
                 boxY + 20,
                 24,
                 WHITE);

        // Leave 按鈕
        DrawRectangleRec(leaveButton, CheckCollisionPointRec(GetMousePosition(), leaveButton) ? GRAY : DARKBLUE);
        DrawRectangleLinesEx(leaveButton, 2.0f, WHITE);
        DrawText("Leave",
                 leaveButton.x + (leaveButton.width - MeasureText("Leave", 18)) / 2,
                 leaveButton.y + (leaveButton.height - 18) / 2, 18, WHITE);

        // Stay 按鈕
        DrawRectangleRec(stayButton, CheckCollisionPointRec(GetMousePosition(), stayButton) ? GRAY : DARKBLUE);
        DrawRectangleLinesEx(stayButton, 2.0f, WHITE);
        DrawText("Stay",
                 stayButton.x + (stayButton.width - MeasureText("Stay", 18)) / 2,
                 stayButton.y + (stayButton.height - 18) / 2, 18, WHITE);
    }
}

static void ExitEndingChoice(void)
{
    // 清理資源 (如果需要)
}

// 關鍵：在這裡定義 STATE_ENDING_CHOICE 實例
const GameState STATE_ENDING_CHOICE = {
    .enter = EnterEndingChoice,
    .update = UpdateEndingChoice,
    .render = RenderEndingChoice,
    .exit = ExitEndingChoice};

// 移除 IsEndingChoiceActive 和 SetEndingChoiceResult 函式，它們在外部不應直接調用
// bool IsEndingChoiceActive(void) {
//     return GetCurrentGameState() == ENDING_CHOICE;
// }

// void SetEndingChoiceResult(bool chooseToLeave) {
//     chooseToLeaveResult = chooseToLeave;
//     choiceMade = true;
//     if (chooseToLeave) {
//         StartDialogue(ending_True, ending_True_Count);
//     } else {
//         StartDialogue(ending_Good, ending_Good_Count);
//     }
// }