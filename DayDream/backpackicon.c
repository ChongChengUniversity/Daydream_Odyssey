// backpackicon.c
#include "backpackicon.h"
#include "raylib.h"
#include "config.h"

// 背包狀態和圖片
bool isBackpackOpen = false;
Texture2D backpackMenu;
Texture2D backpackScreen;
Texture2D exitButton;

// 背包按鈕和畫面位置
Rectangle backpackMenuRect;
Rectangle backpackScreenRect;
Rectangle exitButtonRect;

// 縮放比例
float menuScale = 0.4f; // 背包按鈕縮放比例
float screenScale = 1.2f; // 背包畫面縮放比例

void InitBackpackIcon(void) {
    // 載入背包圖片
    backpackMenu = LoadTexture("assets/backpack_menu.png");
    backpackScreen = LoadTexture("assets/backpack_screen.png");
    exitButton = LoadTexture("assets/exit.png");

    // 設定背包按鈕和畫面位置
    backpackMenuRect = (Rectangle){SCREEN_WIDTH - (backpackMenu.width * menuScale) - 10, SCREEN_HEIGHT - (backpackMenu.height * menuScale) - 10, backpackMenu.width * menuScale, backpackMenu.height * menuScale};

    float scaledScreenWidth = backpackScreen.width * screenScale;
    float scaledScreenHeight = backpackScreen.height * screenScale;

    backpackScreenRect = (Rectangle){(SCREEN_WIDTH - scaledScreenWidth) / 2, (SCREEN_HEIGHT - scaledScreenHeight) / 2, scaledScreenWidth, scaledScreenHeight};

    exitButtonRect = (Rectangle){backpackScreenRect.x + backpackScreenRect.width - (exitButton.width * screenScale) - 10, backpackScreenRect.y + 10, exitButton.width * screenScale, exitButton.height * screenScale};
}

void UpdateBackpackIcon(Vector2 mousePos) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (isBackpackOpen) {
            if (CheckCollisionPointRec(mousePos, exitButtonRect)) {
                isBackpackOpen = false; // 關閉背包
            }
        } else if (CheckCollisionPointRec(mousePos, backpackMenuRect)) {
            isBackpackOpen = true; // 開啟背包
        }
    }
}

void DrawBackpackIcon(void) {
    if (isBackpackOpen) {
        DrawTextureEx(backpackScreen, (Vector2){backpackScreenRect.x, backpackScreenRect.y}, 0.0f, screenScale, WHITE);
        DrawTextureEx(exitButton, (Vector2){exitButtonRect.x, exitButtonRect.y}, 0.0f, screenScale, WHITE);
    } else {
        DrawTextureEx(backpackMenu, (Vector2){backpackMenuRect.x, backpackMenuRect.y}, 0.0f, menuScale, WHITE);
    }
}

void ExitBackpackIcon(void) {
    UnloadTexture(backpackMenu);
    UnloadTexture(backpackScreen);
    UnloadTexture(exitButton);
}