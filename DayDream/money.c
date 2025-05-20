// money.c
#include "money.h"
#include "raylib.h"
#include "config.h"

static int playerCoins = 0;
static Texture2D moneyUITexture;
static float moneyUIScale = 0.2f; // 縮放比例

// 初始化金幣系統
void InitMoneySystem() {
    moneyUITexture = LoadTexture("assets/MoneyUI.png"); 
}

// 結束金幣系統（釋放資源）
void ShutdownMoneySystem() {
    UnloadTexture(moneyUITexture);
}

// 增加金幣
void AddCoins(int amount) {
    playerCoins += amount;
}

// 減少金幣（花費）
void SubtractCoins(int amount) {
    if (playerCoins >= amount) {
        playerCoins -= amount;
    }
}

// 取得當前金幣數量
int GetPlayerCoins() {
    return playerCoins;
}

// 繪製金幣 UI（左上角）
void DrawMoneyUI() {
    // 縮放後的 MoneyUI 尺寸
    float scaledWidth = moneyUITexture.width * moneyUIScale;
    float scaledHeight = moneyUITexture.height * moneyUIScale;
    
    // 設定 UI 的位置（左上角）
    Vector2 uiPos = {10, 10};
    DrawTextureEx(moneyUITexture, uiPos, 0.0f, moneyUIScale, WHITE);
    
    // 顯示金幣數量
    DrawText(TextFormat("%d", playerCoins), uiPos.x + 95, uiPos.y + 15, 30, WHITE);
}