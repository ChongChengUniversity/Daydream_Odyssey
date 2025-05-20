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
#include "inventory.h"
#include "money.h"

void EnterPlaying(void)
{
    if (!IsReturningFromShop())
    {
        InitCards();
        RevealDoorCardAtStart();
    }

    // if return from shop, no need to reset the map(originally used for level change)
    InitShopIcon();
    SetReturningFromShop(false); // reset shop's state
    InitBackpackIcon(); // load backpack icon
}

void UpdatePlaying(void)
{
    //if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // can run properly??
    //{
        Vector2 mousePos = GetMousePosition();
        //OnMouseClick(mousePos);
    //}

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
}

void RenderPlaying(void)
{
    ClearBackground(RAYWHITE);

    DrawTexture(textures[currentSeason], 0, 0, WHITE);
    DrawAllCards();
    DrawPlayerUI();
    DrawShopIcon(); // on right top of the screen
    DrawBackpackIcon();

    if (IsBackpackOpen()) {
         DrawInventoryUI((Vector2){0, 0}, GetBackpackScreenRect()); 
    }

    DrawMoneyUI();

    // draw current level on middle top
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "Level %d", GetCurrentLevel());
    int textWidth = MeasureText(buffer, 24);
    DrawText(buffer, (GetScreenWidth() - textWidth) / 2, 10, 24, WHITE);
}

void ExitPlaying(void)
{
    ExitBackpackIcon();
}

const GameState STATE_PLAYING = {
    .enter = EnterPlaying,
    .update = UpdatePlaying,
    .render = RenderPlaying,
    .exit = ExitPlaying};
