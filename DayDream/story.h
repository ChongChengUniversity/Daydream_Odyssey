// story.h
#ifndef STORY_H
#define STORY_H

#include "raylib.h"
#include <stdbool.h>

// 定義對話狀態
typedef enum {
    DIALOGUE_STATE_NONE,        // 沒有對話在進行
    DIALOGUE_STATE_ACTIVE,      // 對話正在顯示
    DIALOGUE_STATE_WAIT_CLICK   // 等待玩家點擊進入下一行
} DialogueState;

// 對話單行結構
typedef struct {
    const char* speaker; // 說話者 (可以是 NULL 或空字串)
    const char* text;    // 對話內容
} DialogueLine;

// 劇情系統的初始化
void InitStorySystem(void);

// 開始一段新的對話
void StartDialogue(DialogueLine* dialogueSet, int lineCount);

// 更新劇情邏輯 (處理滑鼠點擊、文字逐字顯示)
void UpdateStory(void);

// 渲染劇情介面 (對話框、文字)
void RenderStory(void);

// 檢查對話是否正在進行
bool IsDialogueActive(void);

// 取得當前對話狀態
DialogueState GetDialogueState(void);

// 宣告 keyDialogueTriggered 為全域變數
extern bool keyDialogueTriggered[10];

void SetBadEndDialogueFlag(bool active);
bool IsBadEndDialogueFlagActive(void);
extern void DrawWrappedTextWithLimit(const char* text, Rectangle bounds, 
int fontSize, Color color, int maxDisplayCharIndex);

#endif // STORY_H