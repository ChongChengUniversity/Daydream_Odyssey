// state_playing.c
#include "stateController.h"
#include "CardManager.h"
#include "raylib.h"

#include "assetManager.h"
#include "levelManager.h"
#include "playerUI.h"
#include "shopicon.h" // 商店圖示模組：包含圖示顯示、互動邏輯與狀態旗標（是否從商店回來）

#include "backpackicon.h"
#include "inventory.h"
#include "money.h" // 金幣系統


// 進入「遊玩中」狀態時執行的初始化函式
void EnterPlaying(void) {
  // 如果不是從商店回來，就初始化遊戲卡片地圖與起始門
  if (!IsReturningFromShop()) {
    InitCards();
    RevealDoorCardAtStart();
  }

  // 若是從商店返回，就不重設地圖，保留遊戲進度
  InitShopIcon();
  SetReturningFromShop(false); // 重設狀態

  InitBackpackIcon(); // 初始化背包圖示
}

void UpdatePlaying(void) {
    Vector2 mousePos = GetMousePosition();
    // 1. 如果背包開啟，僅處理背包互動
    if (IsBackpackOpen()) {
        UpdateBackpackIcon(mousePos);
        return; // 阻止其他互動
    }

    // 2. 如果商店開啟，僅處理商店互動
    if (IsReturningFromShop()) {
        UpdateShopIcon();
        return; // 阻止其他互動
    }

    // 3. 如果背包和商店都未開啟，處理地圖互動
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        OnMouseClick(mousePos); // 只有這裡處理地圖卡片點擊
    }

    // 4. 背包和商店的圖示仍然可以互動
    UpdateBackpackIcon(mousePos);
    UpdateShopIcon();
}

void RenderPlaying(void) {
    ClearBackground(RAYWHITE);

    DrawTexture(textures[GetCurrentLevel() - 1], 0, 0, WHITE);

    DrawAllCards();
    DrawPlayerUI();
    DrawShopIcon(); // 畫出右上角商店圖示（可以點擊）

    DrawBackpackIcon(); // 繪製背包圖示

  // 如果背包開啟，繪製背包內容
    if (IsBackpackOpen()) {
         DrawInventoryUI((Vector2){0, 0}, GetBackpackScreenRect()); 
    }

    DrawMoneyUI(); // 金幣 UI
}

void ExitPlaying(void) {
    ExitBackpackIcon();
}

const GameState STATE_PLAYING = {
    .enter = EnterPlaying,
    .update = UpdatePlaying,
    .render = RenderPlaying,
    .exit = ExitPlaying
};
