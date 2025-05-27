// === state_shop.c===
// 包含所有必要的標頭檔，提供音效、遊戲設定、樓層控制、圖像繪製、商店操作等功能
#include "audioManager.h"
#include "config.h"
#include "levelManager.h"
#include "raylib.h"
#include "shopicon.h"
#include "stateController.h"
#include "equipmentSystem.h"
#include "itemSystem.h"
#include "assetManager.h"
#include "money.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shopSystem.h"

// 商店格子排版設定：3x3 共 9 格，每格尺寸與間距
#define SHOP_ITEM_SIZE 160
#define SHOP_GAP 36
#define LABEL_BUFFER 64 // 名稱與描述字元緩衝大小

extern Season currentSeason; // 外部變數：當前季節，用來選對應圖片

// 9 格商店商品格子
ShopItem shopGrid[SHOP_ROWS * SHOP_COLS];

// 當前滑鼠懸停與資訊顯示的格子編號
int hoverIndex = -1;
int infoIndex = -1;

// === 給第九層樓的卷軸隨機器（依照指定機率）===
static ItemType GetRandomScrollTypeForLevel9() {
    float r = (float)rand() / RAND_MAX;
    if (r < 0.45f) return SCROLL_SINGLE;        // 45%
    else if (r < 0.70f) return SCROLL_AOE;       // +25% = 70%
    else if (r < 0.85f) return SCROLL_HEAL;      // +15% = 85%
    else return SCROLL_SHIELD;                   // 剩下15%
}

// === 商店填入裝備與卷軸 ===
static void FillShopWithEquipmentsAndScrolls(int currentFloor) {
    int filled = 0;
    int base = (currentFloor - 1) * 5;

      // 清空商店格子狀態
      for (int i = 0; i < SHOP_ROWS * SHOP_COLS; ++i) {
        shopGrid[i].active = false;
        shopGrid[i].selected = false;
        shopGrid[i].isSoldOut = false;
        shopGrid[i].name[0] = '\0';
        shopGrid[i].description[0] = '\0';
        shopGrid[i].image = NULL;
    }

     // 放裝備
     for (int i = 0; i < GetTotalEquipments() && filled < SHOP_ROWS * SHOP_COLS; ++i) {
        EquipmentData* eq = GetEquipmentByIndex(i);
        if (!eq || i < base || i >= base + 5) continue;

        snprintf(shopGrid[filled].name, LABEL_BUFFER, "%s", eq->name);
        snprintf(shopGrid[filled].description, 128, "%s", eq->description);
        shopGrid[filled].price = eq->price;
        shopGrid[filled].active = !eq->isPurchased;
        shopGrid[filled].isSoldOut = eq->isPurchased;
        shopGrid[filled].image = eq->image;
        filled++;
    }
    // === 第九層樓：強制出現延長Boss CD卷軸 + 兩種不重複的隨機卷軸 ===
    if (currentFloor == 9) {
        // 1. 固定出現時間卷軸 SCROLL_TIME
        ItemData* fixed = GetItemByType(SCROLL_TIME);
        if (fixed && filled < SHOP_ROWS * SHOP_COLS) {
            snprintf(shopGrid[filled].name, LABEL_BUFFER, "%s", fixed->name);
            snprintf(shopGrid[filled].description, 128, "%s", fixed->description);
            shopGrid[filled].price = fixed->price;
            shopGrid[filled].active = !fixed->isPurchased;
            shopGrid[filled].isSoldOut = fixed->isPurchased;
            shopGrid[filled].image = &seasonalItems[currentSeason][SCROLL_TIME];
            filled++;
        }

        // 2. 隨機加入兩種不重複的卷軸
        ItemType selectedScrolls[2];  // 紀錄已經挑過的卷軸類型
        int scrollCount = 0;

        while (scrollCount < 2 && filled < SHOP_ROWS * SHOP_COLS) {
            ItemType scrollType = GetRandomScrollTypeForLevel9();

            // 檢查是否重複
            bool duplicate = false;
            for (int j = 0; j < scrollCount; ++j) {
                if (selectedScrolls[j] == scrollType) {
                    duplicate = true;
                    break;
                }
            }
            if (duplicate) continue;

            // 若沒重複，加入商店格子
            ItemData* item = GetItemByType(scrollType);
            if (item) {
                selectedScrolls[scrollCount++] = scrollType;

                snprintf(shopGrid[filled].name, LABEL_BUFFER, "%s", item->name);
                snprintf(shopGrid[filled].description, 128, "%s", item->description);
                shopGrid[filled].price = item->price;
                shopGrid[filled].active = !item->isPurchased;
                shopGrid[filled].isSoldOut = item->isPurchased;
                shopGrid[filled].image = &seasonalItems[currentSeason][scrollType];
                filled++;
            }
        }
    }

    // === 第3層以上：有機率出現 1 種卷軸（不重複處理，可重複）===
    else if (currentFloor >= 3) {
        float r = (float)rand() / RAND_MAX;
        ItemType scrollType;
        if (r < 0.40f) scrollType = SCROLL_SINGLE;
        else if (r < 0.65f) scrollType = SCROLL_AOE;
        else if (r < 0.80f) scrollType = SCROLL_TIME;
        else if (r < 0.90f) scrollType = SCROLL_HEAL;
        else scrollType = SCROLL_SHIELD;

        ItemData* item = GetItemByType(scrollType);
        if (item && filled < SHOP_ROWS * SHOP_COLS) {
            snprintf(shopGrid[filled].name, LABEL_BUFFER, "%s", item->name);
            snprintf(shopGrid[filled].description, 128, "%s", item->description);
            shopGrid[filled].price = item->price;
            shopGrid[filled].active = !item->isPurchased;
            shopGrid[filled].isSoldOut = item->isPurchased;
            shopGrid[filled].image = &seasonalItems[currentSeason][scrollType];
            filled++;
        }
    }
}


// === 進入商店階段時呼叫，初始化商店內容與格子座標 ===
static void EnterShop() {

    // 商店整體寬高計算
    int totalWidth = SHOP_COLS * SHOP_ITEM_SIZE + (SHOP_COLS - 1) * SHOP_GAP;
    int totalHeight = SHOP_ROWS * SHOP_ITEM_SIZE + (SHOP_ROWS - 1) * SHOP_GAP;
    int startX = SCREEN_WIDTH / 2 - totalWidth / 2;
    int startY = SCREEN_HEIGHT / 2 - totalHeight / 2 + 40;

    // 每個格子座標設定
    for (int i = 0; i < SHOP_ROWS * SHOP_COLS; ++i) {
        int row = i / SHOP_COLS;
        int col = i % SHOP_COLS;
        shopGrid[i].bounds = (Rectangle){
            startX + col * (SHOP_ITEM_SIZE + SHOP_GAP),
            startY + row * (SHOP_ITEM_SIZE + SHOP_GAP),
            SHOP_ITEM_SIZE, SHOP_ITEM_SIZE
        };
    }

    FillShopWithEquipmentsAndScrolls(GetCurrentLevel());
}

// === 每幀更新商店狀態：按鍵偵測與滑鼠互動 ===
static void UpdateShop() {
    if (IsKeyPressed(KEY_ENTER)) {
        SetReturningFromShop(true);
        GOTO(PLAYING);
    }

    Rectangle itemBounds[SHOP_ROWS * SHOP_COLS];
    bool activeArray[SHOP_ROWS * SHOP_COLS];
    for (int i = 0; i < SHOP_ROWS * SHOP_COLS; ++i) {
        itemBounds[i] = shopGrid[i].bounds;
        activeArray[i] = shopGrid[i].active;
    }

    UpdateShopInteraction(itemBounds, SHOP_ROWS * SHOP_COLS, &hoverIndex, &infoIndex, activeArray);
}

// === 繪製整個商店畫面（商品格子、圖片、名稱、價格、資訊等）===
static void RenderShop() {
    ClearBackground((Color){77, 51, 25, 255});
    DrawRectangle(0, 0, SCREEN_WIDTH, 80, (Color){193, 117, 56, 255});
    DrawText("SHOP", SCREEN_WIDTH / 2 - MeasureText("SHOP", 48) / 2, 20, 48, YELLOW);

    char coinText[64];
    snprintf(coinText, sizeof(coinText), "COIN: %d", GetPlayerCoins());
    DrawText(coinText, SCREEN_WIDTH - 200, 30, 24, GOLD);

    Rectangle itemBounds[SHOP_ROWS * SHOP_COLS];
    for (int i = 0; i < SHOP_ROWS * SHOP_COLS; ++i) itemBounds[i] = shopGrid[i].bounds;
    RenderItemHover(hoverIndex, itemBounds, SHOP_ROWS * SHOP_COLS);

    for (int i = 0; i < SHOP_ROWS * SHOP_COLS; ++i) {
        DrawRectangleRounded(shopGrid[i].bounds, 0.1f, 12, (Color){236, 204, 158, 255});
        DrawRectangleRoundedLines(shopGrid[i].bounds, 0.1f, 12, BROWN);

        // 若有圖就畫圖
        if (shopGrid[i].active && shopGrid[i].image && shopGrid[i].image->id > 0) {
            DrawTexturePro(
                *shopGrid[i].image,
                (Rectangle){0, 0, shopGrid[i].image->width, shopGrid[i].image->height},
                (Rectangle){shopGrid[i].bounds.x, shopGrid[i].bounds.y, shopGrid[i].bounds.width, shopGrid[i].bounds.height},
                (Vector2){0, 0}, 0.0f, WHITE
            );
        }

        // 商品名稱
        int nameW = MeasureText(shopGrid[i].name, 16);
        DrawText(shopGrid[i].name,
                 shopGrid[i].bounds.x + SHOP_ITEM_SIZE / 2 - nameW / 2,
                 shopGrid[i].bounds.y + SHOP_ITEM_SIZE - 30,
                 16, WHITE);

        // 價格
        if (shopGrid[i].active) {
            char priceStr[32];
            snprintf(priceStr, sizeof(priceStr), "$%d", shopGrid[i].price);
            int priceWidth = MeasureText(priceStr, 14);
            DrawText(priceStr,
                     shopGrid[i].bounds.x + SHOP_ITEM_SIZE / 2 - priceWidth / 2,
                     shopGrid[i].bounds.y + SHOP_ITEM_SIZE - 15,
                     14, WHITE);
        }

        if (shopGrid[i].isSoldOut) {
            DrawTexture(SOLD_OUT, shopGrid[i].bounds.x, shopGrid[i].bounds.y, (Color){255, 255, 255, 180});  // 半透明覆蓋
        }
        
    }

    // 商品資訊框（滑鼠右鍵顯示）
    if (infoIndex >= 0) {
        char infoText[256];
        snprintf(infoText, sizeof(infoText), "%s\n%s", shopGrid[infoIndex].name, shopGrid[infoIndex].description);
        RenderItemInfo(infoIndex, itemBounds, infoText);
    }
    RenderPurchaseConfirmation();
    DrawText("[ENTER] Return to Game", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT - 50, 20, LIGHTGRAY);
}

// === 離開商店階段，目前不需處理 ===
static void ExitShop() {}

// === 商店狀態結構：提供給 stateController 切換使用 ===
const GameState STATE_SHOP = {
    .enter = EnterShop,
    .update = UpdateShop,
    .render = RenderShop,
    .exit = ExitShop
};









