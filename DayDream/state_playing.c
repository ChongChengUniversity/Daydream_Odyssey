// state_playing.c
#include "stateController.h"
#include "CardManager.h"
#include "raylib.h"
#include "levelManager.h"
#include "assetManager.h"
#include "playerUI.h"
#include <stdio.h>
#include "shopicon.h" // shop picture mode: including display, interact, and states
#include "backpackicon.h"
#include "enemyManager.h"
#include "inventory.h"
#include "money.h"

#include "itemUse.h"

void EnterPlaying(void)
{
    if (!IsReturningFromShop())
    {
        InitCards();
        RevealDoorCardAtStart();
        InitFloor();    //載入怪物資訊
    }

    // if return from shop, no need to reset the map(originally used for level change)
    InitShopIcon();
    SetReturningFromShop(false); // reset shop's state
    InitBackpackIcon(); // load backpack icon
    InitItemUseSystem();
}

void UpdatePlaying(void)
{
    Vector2 mousePos = GetMousePosition();

    if (GetItemUseState() != ITEM_STATE_NONE) {
        UpdateItemUse(mousePos);
        return;
    }

    if (IsBackpackOpen()) {
        UpdateBackpackIcon(mousePos);
        return; // 阻止其他互動
    }

    if (IsReturningFromShop()) {
        UpdateShopIcon();
        return; // 阻止其他互動
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        OnMouseClick(mousePos); // 只有這裡處理地圖卡片點擊
    }

    UpdateBackpackIcon(mousePos);
    UpdateShopIcon();
    AbleToReveal(); //這行可以讓畫面即時更新啊啊
}



void ExitPlaying(void)
{
    ExitBackpackIcon();
    UnloadItemUseSystem();
}
void RenderPlaying(void)
{
    ClearBackground(RAYWHITE);

    DrawTexture(textures[currentSeason], 0, 0, WHITE);
    DrawAllCards();
    DrawPlayerUI();

    if (GetItemUseState() == ITEM_STATE_NONE) {
        DrawBackpackIcon();
        DrawShopIcon();
    } else {
        DrawItemUseUI(); // 顯示 quit 按鈕
    }

    DrawMoneyUI();

    // draw current level on middle top
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "Level %d", GetCurrentLevel());
    int textWidth = MeasureText(buffer, 24);
    DrawText(buffer, (GetScreenWidth() - textWidth) / 2, 10, 24, WHITE);
}
const GameState STATE_PLAYING = {
    .enter = EnterPlaying,
    .update = UpdatePlaying,
    .render = RenderPlaying,
    .exit = ExitPlaying};
