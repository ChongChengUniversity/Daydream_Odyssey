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
#include "CharacterStats.h"
#include "story.h"
#include "dialogues.h"

// 用於追蹤劇情是否已觸發的標誌
static bool openingDialogueTriggered = false;
static bool summerDialogueTriggered = false;
static bool autumnDialogueTriggered = false;
static bool winterDialogueTriggered = false;

// 每一關的鑰匙對話標誌 (現在是全域變數，在 story.h 中 extern)
// 這裡定義並初始化它
bool keyDialogueTriggered[10] = {false, false, false, false, false, false, false, false, false, false};

void EnterPlaying(void)
{
    // 進入Playing狀態時，觸發開場對話，只觸發一次
    if (!openingDialogueTriggered) {
        StartDialogue(openingDialogue, openingDialogueCount); // 使用 dialogues.h 中的對話
        openingDialogueTriggered = true;
    }

    if (!IsReturningFromShop())
    {
        InitCards();
        if (!(GetCurrentLevel() == 10)) RevealDoorCardAtStart();// ✅ 第十關不自動翻門
        InitFloor();    //載入怪物資訊
    }

    // 觸發季節對話
    if (GetCurrentLevel() == 4 && !summerDialogueTriggered) {
        StartDialogue(seasonChange_SummerStart, seasonChange_SummerStart_Count);
        summerDialogueTriggered = true;
    } else if (GetCurrentLevel() == 7 && !autumnDialogueTriggered) {
        StartDialogue(seasonChange_AutumnStart, seasonChange_AutumnStart_Count);
        autumnDialogueTriggered = true;
    } else if (GetCurrentLevel() == 10 && !winterDialogueTriggered) {
        StartDialogue(seasonChange_WinterStart, seasonChange_WinterStart_Count);
        winterDialogueTriggered = true;
    }

    // if return from shop, no need to reset the map(originally used for level change)
    InitShopIcon();
    SetReturningFromShop(false); // reset shop's state
    InitBackpackIcon(); // load backpack icon
    InitItemUseSystem();
}

void UpdatePlaying(void)
{
    // 如果正在對話中，則只更新劇情，不處理其他遊戲邏輯
    if (IsDialogueActive()) {
        UpdateStory();
        return;
    }

    Vector2 mousePos = GetMousePosition();

    UpdatePlayer(GetPlayerStats());

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
    DrawText(buffer, (GetScreenWidth() - textWidth) / 2, 10, 30, WHITE);
}

const GameState STATE_PLAYING = {
    .enter = EnterPlaying,
    .update = UpdatePlaying,
    .render = RenderPlaying,
    .exit = ExitPlaying};
