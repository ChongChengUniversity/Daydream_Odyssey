// backpackicon.h
#ifndef BACKPACKICON_H
#define BACKPACKICON_H

#include "raylib.h"

// 背包圖示功能函數
void InitBackpackIcon(void);
void UpdateBackpackIcon(Vector2 mousePos);
void DrawBackpackIcon(void);
void ExitBackpackIcon(void);

// 背包狀態函數（用於檢查是否開啟）
bool IsBackpackOpen(void);

// 獲取背包畫面區域（Rectangle）
Rectangle GetBackpackScreenRect(void);

// 當前畫面狀態：背包 or 裝備欄
typedef enum {
    SCREEN_BACKPACK,
    SCREEN_EQUIPMENT
} BackpackPage;

// 當前畫面狀態存取用
BackpackPage GetCurrentBackpackPage(void);
void SetCurrentBackpackPage(BackpackPage page);

// 背包狀態變數
extern bool isBackpackOpen;

#endif
