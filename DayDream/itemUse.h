// itemUse.h
#pragma once
#include "raylib.h"

// 狀態列舉：是否正在等待使用道具
typedef enum {
    ITEM_STATE_NONE,
    ITEM_STATE_WAIT_GRID
} ItemUseState;

// 初始化與釋放資源
void InitItemUseSystem(void);
void UnloadItemUseSystem(void);

// 進入道具使用模式
void BeginItemUse(int itemIndex);

// 處理點擊地圖或Quit按鈕
void UpdateItemUse(Vector2 mousePos);

// 提示、Quit按鈕
void DrawItemUseUI(void);

// 外部讀取目前狀態
ItemUseState GetItemUseState(void);

void SetMessage(const char* text);   // 🔥 對外開放函數
extern int messageTimer;
extern char message[256];