// story.c
#include "story.h"
#include "raylib.h"
#include <string.h> // for strlen, strncpy
#include <stdio.h>  // for snprintf (if needed for debugging)
#include "dialogues.h"
#include "stateController.h"

// 對話系統內部狀態變數
static DialogueLine *currentDialogueSet = NULL;
static int totalDialogueLines = 0;
static int currentLineIndex = 0;
static int currentCharIndex = 0; // 用於逐字顯示 (總共顯示的字元數)
static float charDisplayTimer = 0.0f;
static float charDisplayDelay = 0.03f;  // 每個字元顯示的延遲 (秒)
static bool badEndDialogueFlag = false; // 在 story.c 內部定義

static DialogueState dialogueState = DIALOGUE_STATE_NONE;

// 對話框尺寸和位置
#define DIALOGUE_BOX_HEIGHT 180
#define DIALOGUE_BOX_PADDING 20
#define SPEAKER_TEXT_OFFSET_Y 10
#define DIALOGUE_TEXT_OFFSET_Y 40

// 新增的常數，用於文字換行
#define DIALOGUE_TEXT_MAX_WIDTH (GetScreenWidth() - DIALOGUE_BOX_PADDING * 2 - 40) // 預留左右邊距
#define LINE_SPACING 5                                                             // 額外的行距

// --- 輔助函式：帶有自動換行和逐字顯示限制的文字繪製 ---
// text: 完整文字內容
// bounds: 繪製區域的矩形 (x, y, width, height)
// fontSize: 字體大小
// color: 文字顏色
// maxDisplayCharIndex: 總共允許顯示的字元數 (用於逐字顯示效果)
void DrawWrappedTextWithLimit(const char *text, Rectangle bounds, int fontSize, Color color, int maxDisplayCharIndex)
{
    if (!text || strlen(text) == 0 || maxDisplayCharIndex <= 0)
        return;

    float currentY = bounds.y;
    const char *remainingText = text;
    int totalCharsProcessed = 0; // 記錄從 text 開頭已處理的總字元數

    while (*remainingText != '\0' && totalCharsProcessed < maxDisplayCharIndex)
    {
        char lineBuffer[1024]; // 用於儲存單行文字的緩衝區
        int lineLength = 0;
        const char *lineStart = remainingText;
        const char *lastSpace = NULL; // 記錄上一個空格的位置，用於斷詞
        bool forcedBreak = false;     // 是否遇到強制換行符 '\n'

        int charCount = 0; // 當前行已考慮的字元數
        while (remainingText[charCount] != '\0')
        {
            // 檢查是否為強制換行符
            if (remainingText[charCount] == '\n')
            {
                forcedBreak = true;
                lineLength = charCount; // 該行長度到換行符前
                break;                  // 強制換行
            }

            // 測試加入下一個字元後是否會超出最大寬度
            char tempBuffer[1024];
            // 複製到 tempBuffer 進行測試，不包括當前 charCount 所在的字元，
            // 而是 charCount+1 個字元（即包含當前考慮的字元）
            strncpy(tempBuffer, lineStart, charCount + 1);
            tempBuffer[charCount + 1] = '\0'; // 確保字串終止

            if (MeasureText(tempBuffer, fontSize) > bounds.width)
            {
                // 如果加入此字元會超出寬度
                if (lastSpace != NULL && lastSpace > lineStart)
                {
                    // 如果有可供斷詞的空格，則在此處斷行
                    lineLength = lastSpace - lineStart; // 該行長度到最後一個空格前
                    remainingText = lastSpace + 1;      // 下一行從空格後開始
                }
                else
                {
                    // 沒有空格可斷詞（例如單詞很長），則強制在此字元處斷行
                    lineLength = charCount;                // 該行長度到超出寬度的字元前
                    remainingText = lineStart + charCount; // 下一行從該字元開始
                }
                break; // 確定當前行內容
            }

            if (remainingText[charCount] == ' ')
            {
                lastSpace = &remainingText[charCount]; // 記錄當前空格位置
            }
            charCount++;
        }

        // 如果循環結束，表示剩餘文本全部適合當前行
        if (!forcedBreak && remainingText[charCount] == '\0')
        {
            lineLength = charCount;
            remainingText += charCount; // 文本已讀取完畢
        }

        // 將確定好的行內容複製到 lineBuffer
        strncpy(lineBuffer, lineStart, lineLength);
        lineBuffer[lineLength] = '\0';

        // 應用逐字顯示限制
        int actualCharsToDraw = lineLength; // 當前行實際能繪製的字元數
        // 如果已處理的總字元數加上當前行長度超過了 maxDisplayCharIndex，
        // 則調整當前行實際繪製的字元數
        if (totalCharsProcessed + lineLength > maxDisplayCharIndex)
        {
            actualCharsToDraw = maxDisplayCharIndex - totalCharsProcessed;
            if (actualCharsToDraw < 0)
                actualCharsToDraw = 0; // 防止負數
        }

        // 繪製文本
        if (actualCharsToDraw > 0)
        {
            DrawText(TextSubtext(lineBuffer, 0, actualCharsToDraw), bounds.x, currentY, fontSize, color);
        }
        totalCharsProcessed += lineLength; // 更新已處理的總字元數

        currentY += fontSize + LINE_SPACING; // 移動到下一行的Y座標

        // 跳過強制換行符
        if (forcedBreak)
        {
            remainingText++;
        }
        // 跳過下一行開頭的任何空格
        while (*remainingText == ' ')
        {
            remainingText++;
        }
    }
}

void InitStorySystem(void)
{
    currentDialogueSet = NULL;
    totalDialogueLines = 0;
    currentLineIndex = 0;
    currentCharIndex = 0;
    charDisplayTimer = 0.0f;
    dialogueState = DIALOGUE_STATE_NONE;
    badEndDialogueFlag = false; // 初始化時重置
}

void StartDialogue(DialogueLine *dialogueSet, int lineCount)
{
    if (dialogueSet == NULL || lineCount <= 0)
    {
        TraceLog(LOG_WARNING, "STORY: Attempted to start dialogue with invalid set or count.");
        return;
    }
    currentDialogueSet = dialogueSet;
    totalDialogueLines = lineCount;
    currentLineIndex = 0;
    currentCharIndex = 0;
    charDisplayTimer = 0.0f;
    dialogueState = DIALOGUE_STATE_ACTIVE;
}

void UpdateStory(void)
{
    if (dialogueState == DIALOGUE_STATE_NONE)
        return;

    if (dialogueState == DIALOGUE_STATE_ACTIVE)
    {
        charDisplayTimer += GetFrameTime();
        if (charDisplayTimer >= charDisplayDelay)
        {
            currentCharIndex++;
            charDisplayTimer = 0.0f;
            // 當逐字顯示達到當前對話行的總字元數時，切換到等待點擊狀態
            if (currentCharIndex > strlen(currentDialogueSet[currentLineIndex].text))
            {
                currentCharIndex = strlen(currentDialogueSet[currentLineIndex].text); // 確保不越界
                dialogueState = DIALOGUE_STATE_WAIT_CLICK;
            }
        }
    }

    if (dialogueState == DIALOGUE_STATE_WAIT_CLICK)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER))
        {
            currentLineIndex++;
            if (currentLineIndex >= totalDialogueLines)
            {
                // 對話結束
                dialogueState = DIALOGUE_STATE_NONE;
                currentDialogueSet = NULL; // 清除對話集指針
                // 在這裡加入 Bad End 判斷與自動跳轉
                if (IsBadEndDialogueFlagActive())
                {
                    SetBadEndDialogueFlag(false); // 重置旗標
                    GOTO(LOSE);                   // 自動跳轉到失敗畫面
                }
            }
            else
            {
                // 進入下一行
                currentCharIndex = 0; // 重置下一行的逐字顯示計數
                dialogueState = DIALOGUE_STATE_ACTIVE;
            }
        }
    }
}

void RenderStory(void)
{
    if (dialogueState == DIALOGUE_STATE_NONE)
        return;

    int boxX = DIALOGUE_BOX_PADDING;
    int boxY = GetScreenHeight() - DIALOGUE_BOX_HEIGHT - DIALOGUE_BOX_PADDING;
    int boxWidth = GetScreenWidth() - DIALOGUE_BOX_PADDING * 2;

    DrawRectangle(boxX, boxY, boxWidth, DIALOGUE_BOX_HEIGHT, Fade(BLACK, 0.7f));
    DrawRectangleLinesEx((Rectangle){boxX, boxY, boxWidth, DIALOGUE_BOX_HEIGHT}, 2.0f, WHITE);

    if (currentDialogueSet != NULL && currentLineIndex < totalDialogueLines)
    {
        // 顯示說話者
        if (currentDialogueSet[currentLineIndex].speaker != NULL &&
            strlen(currentDialogueSet[currentLineIndex].speaker) > 0)
        {
            DrawText(currentDialogueSet[currentLineIndex].speaker,
                     boxX + 20, boxY + SPEAKER_TEXT_OFFSET_Y, 20, YELLOW);
        }

        // 設定文本繪製區域
        Rectangle textDrawBounds = {
            boxX + 20,                                                                  // X 偏移
            boxY + DIALOGUE_TEXT_OFFSET_Y,                                              // Y 偏移
            DIALOGUE_TEXT_MAX_WIDTH,                                                    // 最大寬度
            DIALOGUE_BOX_HEIGHT - (DIALOGUE_TEXT_OFFSET_Y - SPEAKER_TEXT_OFFSET_Y) - 10 // 可用高度
        };

        // 呼叫輔助函式來繪製帶有換行和逐字顯示的文本
        DrawWrappedTextWithLimit(currentDialogueSet[currentLineIndex].text,
                                 textDrawBounds,
                                 25, // 字體大小
                                 WHITE,
                                 currentCharIndex); // 傳入當前已顯示的字元數

        // 如果是等待點擊狀態，顯示提示
        if (dialogueState == DIALOGUE_STATE_WAIT_CLICK)
        {
            DrawText("Click to continue...",
                     boxX + boxWidth - MeasureText("Click to continue...", 20) - 20,
                     boxY + DIALOGUE_BOX_HEIGHT - 30, 20, LIGHTGRAY);
        }
    }
}

DialogueState GetDialogueState(void)
{
    return dialogueState;
}

bool IsDialogueActive(void)
{
    return dialogueState != DIALOGUE_STATE_NONE;
}

void SetBadEndDialogueFlag(bool active)
{
    badEndDialogueFlag = active;
}

bool IsBadEndDialogueFlagActive(void)
{
    return badEndDialogueFlag;
}