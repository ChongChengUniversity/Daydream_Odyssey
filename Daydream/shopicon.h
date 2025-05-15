// shopicon.h
#pragma once        // 防止重複包含這個標頭檔
#include "raylib.h" // 引入 Raylib 函式庫，提供圖形、音效等 API

void InitShopIcon(void);   // 初始化商店圖示（計算位置與大小）
void DrawShopIcon(void);   // 繪製商店圖示（框與圖示）
void UpdateShopIcon(void); // 更新商店圖示邏輯（判斷滑鼠點擊）
void SetReturningFromShop(bool flag); // 設定是否從商店回來（給其他模組用來標記狀態）
bool IsReturningFromShop(void); // 查詢是否剛從商店回來（例如進入遊戲時決定是否初始化卡片）
