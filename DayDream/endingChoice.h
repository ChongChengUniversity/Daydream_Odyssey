// endingChoice.h
#ifndef ENDING_CHOICE_H
#define ENDING_CHOICE_H

#include "raylib.h"
#include <stdbool.h>
#include "stateController.h"

// 宣告 GameState 結構，讓 main 可以引用
typedef struct GameState GameState;

// 宣告 GameState 結構的實際定義，它將在 endingChoice.c 中定義
extern const GameState STATE_ENDING_CHOICE;

// 檢查是否正在進行結局選擇
//bool IsEndingChoiceActive(void);

// 設置選擇結果並觸發對話
//void SetEndingChoiceResult(bool chooseToLeave);

#endif // ENDING_CHOICE_H