// state_playing.c
#include "stateController.h"
#include "CardManager.h"
#include "raylib.h"

#include "assetManager.h"
#include "levelManager.h"
#include "playerUI.h"
#include "shopicon.h" // 商店圖示模組：包含圖示顯示、互動邏輯與狀態旗標（是否從商店回來）

#include "backpackicon.h"


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
    UpdateBackpackIcon(mousePos);

    UpdateShopIcon(); // 處理商店點擊互動
}

void RenderPlaying(void) {
    ClearBackground(RAYWHITE);

    DrawTexture(textures[GetCurrentLevel() - 1], 0, 0, WHITE);

    DrawAllCards();
    DrawPlayerUI();
    DrawShopIcon(); // 畫出右上角商店圖示（可以點擊）

    DrawBackpackIcon(); // 繪製背包圖示
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
