// backpackicon.c
#include "backpackicon.h"
#include "raylib.h"
#include "config.h"
#include "inventory.h"
#include "CharacterStats.h"

// 狀態變數、背包欄和裝備欄圖片資源
bool isBackpackOpen = false;
Texture2D backpackMenu;
Texture2D backpackScreen;
Texture2D exitButton;
Texture2D equipmentScreen;
Texture2D nextButton;
Texture2D backButton;

// 按鈕和畫面位置
Rectangle backpackMenuRect;
Rectangle backpackScreenRect;
Rectangle exitButtonRect;
Rectangle nextButtonRect;
Rectangle backButtonRect;
// 不用equipmentScreenRect?

static BackpackPage currentPage = SCREEN_BACKPACK;

// 縮放比例
float menuScale = 0.4f; // 背包按鈕縮放比例
float screenScale = 1.2f; // 背包畫面縮放比例
float buttonScale = 0.5f; // 上下頁按鈕縮放比例

// 檢查背包開啟狀態（供其他模組檢查）
bool IsBackpackOpen() {
    return isBackpackOpen;
}

// 獲取背包畫面區域（Rectangle）
Rectangle GetBackpackScreenRect(void) {
    return backpackScreenRect;
}

BackpackPage GetCurrentBackpackPage(void) {
    return currentPage;
}

void SetCurrentBackpackPage(BackpackPage page) {
    currentPage = page;
}

void InitBackpackIcon(void) {
    // 載入圖片
    backpackMenu = LoadTexture("assets/backpack_menu.png");
    backpackScreen = LoadTexture("assets/backpack_screen.png");
    equipmentScreen = LoadTexture("assets/equipment_screen.png");
    exitButton = LoadTexture("assets/exit.png");
    backButton = LoadTexture("assets/back.png");
    nextButton = LoadTexture("assets/next.png");

    // 設定背包按鈕和畫面位置
    backpackMenuRect = (Rectangle){
        SCREEN_WIDTH - (backpackMenu.width * menuScale) - 10,
        SCREEN_HEIGHT - (backpackMenu.height * menuScale) - 10,
        backpackMenu.width * menuScale,
        backpackMenu.height * menuScale};

    float scaledScreenWidth = backpackScreen.width * screenScale;
    float scaledScreenHeight = backpackScreen.height * screenScale;

    backpackScreenRect = (Rectangle){(SCREEN_WIDTH - scaledScreenWidth) / 2, (SCREEN_HEIGHT - scaledScreenHeight) / 2, scaledScreenWidth, scaledScreenHeight};

    exitButtonRect = (Rectangle){
        backpackScreenRect.x + backpackScreenRect.width - (exitButton.width * screenScale) - 10,
        backpackScreenRect.y + 10,
        exitButton.width * screenScale,
        exitButton.height * screenScale};

    nextButtonRect = (Rectangle){
        backpackScreenRect.x + backpackScreenRect.width - (nextButton.width * buttonScale) - 60,
        backpackScreenRect.y + backpackScreenRect.height - (nextButton.height * buttonScale) - 5,
        nextButton.width * buttonScale,
        nextButton.height * buttonScale};

    backButtonRect = (Rectangle){
        backpackScreenRect.x + 60,
        backpackScreenRect.y + backpackScreenRect.height - (backButton.height * buttonScale) - 5,
        backButton.width * buttonScale,
        backButton.height * buttonScale};
}

void UpdateBackpackIcon(Vector2 mousePos) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (isBackpackOpen) {
            if (CheckCollisionPointRec(mousePos, exitButtonRect)) {
                isBackpackOpen = false;
                currentPage = SCREEN_BACKPACK;
                return;
            }
            if (currentPage == SCREEN_BACKPACK && CheckCollisionPointRec(mousePos, nextButtonRect)) {
                currentPage = SCREEN_EQUIPMENT;
                return;
            }
            if (currentPage == SCREEN_EQUIPMENT && CheckCollisionPointRec(mousePos, backButtonRect)) {
                currentPage = SCREEN_BACKPACK;
                return;
            }
        } else {
            if (CheckCollisionPointRec(mousePos, backpackMenuRect)) {
                isBackpackOpen = true;
            }
        }
    }
}

// 裝備欄位繪製
static void DrawEquipmentSlots(Rectangle screenRect) {
    float cellSize = 81;
    Vector2 slotPositions[5] = {
        {screenRect.x + 135,  screenRect.y + 122},   // Head（左上）
        {screenRect.x + 355, screenRect.y + 122},   // Hand（右上）
        {screenRect.x + 245, screenRect.y + 210},  // Body（中）
        {screenRect.x + 135,  screenRect.y + 300},  // Leg（左下）
        {screenRect.x + 355, screenRect.y + 300}   // Accessory（右下）
    };
    const char *slotLabels[5] = {"Head", "Hand", "Body", "Leg", "Accessory"};

    for (int i = 0; i < 5; i++) {
        // DrawRectangleLines(slotPositions[i].x, slotPositions[i].y, cellSize, cellSize, GRAY);
        DrawText(slotLabels[i], slotPositions[i].x, slotPositions[i].y - 20, 20, LIGHTGRAY);
    }
}

// 主角能力值顯示
static void DrawPlayerStats(Rectangle screenRect) {
    PlayerStats* stats = GetPlayerStats();

    Vector2 statPositions[4] = {
        {screenRect.x + 100,  screenRect.y + 410},  // ATK
        {screenRect.x + 315, screenRect.y + 410},  // MATK
        {screenRect.x + 100,  screenRect.y + 475},  // DEF
        {screenRect.x + 315, screenRect.y + 475}   // MAX HP
    };

    const char* labels[4] = {"ATK", "MATK", "DEF", "MAX HP"};
    int values[4] = {
        stats->atk,
        stats->magic,
        stats->def,
        stats->maxHp
    };

    for (int i = 0; i < 4; i++) {
        DrawText(TextFormat("%s: %d", labels[i], values[i]), statPositions[i].x, statPositions[i].y, 25, DARKBROWN);
    }
}

void DrawBackpackIcon(void) {
    if (!isBackpackOpen) {
        // 背包關閉狀態，只畫圖示按鈕
        DrawTextureEx(backpackMenu, (Vector2){backpackMenuRect.x, backpackMenuRect.y}, 0.0f, menuScale, WHITE);
        return;
    }

    if (currentPage == SCREEN_BACKPACK) {
        // 背包畫面、道具與 next 按鈕
        DrawTextureEx(backpackScreen, (Vector2){backpackScreenRect.x, backpackScreenRect.y}, 0.0f, screenScale, WHITE);
        DrawInventoryUI((Vector2){backpackScreenRect.x + 20, backpackScreenRect.y + 50}, backpackScreenRect);
        DrawTextureEx(nextButton, (Vector2){nextButtonRect.x, nextButtonRect.y}, 0.0f, 0.5f, WHITE);
    } else {
        // 裝備畫面、slot與 back 按鈕
        DrawTextureEx(equipmentScreen, (Vector2){backpackScreenRect.x, backpackScreenRect.y}, 0.0f, screenScale, WHITE);
        DrawEquipmentSlots(backpackScreenRect);
        DrawPlayerStats(backpackScreenRect);
        DrawTextureEx(backButton, (Vector2){backButtonRect.x, backButtonRect.y}, 0.0f, 0.5f, WHITE);
    }

    DrawTextureEx(exitButton, (Vector2){exitButtonRect.x, exitButtonRect.y}, 0.0f, screenScale, WHITE);
}

void ExitBackpackIcon(void) {
    UnloadTexture(backpackMenu);
    UnloadTexture(backpackScreen);
    UnloadTexture(equipmentScreen);
    UnloadTexture(exitButton);
    UnloadTexture(nextButton);
    UnloadTexture(backButton);
}
