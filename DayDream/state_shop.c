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
#include "shopSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 商店格子排版設定：3x3 共 9 格，每格尺寸與間距
#define SHOP_ITEM_SIZE 160
#define SHOP_GAP 36


extern Season currentSeason; // 外部變數：當前季節，用來選對應圖片
extern double infoStartTime;

// 9 格商店商品格子
ShopItem shopGrid[SHOP_ROWS * SHOP_COLS];


// 當前滑鼠懸停與資訊顯示的格子編號
int hoverIndex = -1;
int infoIndex = -1;


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
        shopGrid[filled].type = -1;
        if (eq->locked)
            shopGrid[filled].locked = true;
        filled++;
    }

    FillScrollsForFloor(currentFloor, &filled);
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
        if (shopGrid[i].active) {
            // 圖片正常，才畫圖
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
        
        if (shopGrid[i].locked) {
            DrawTexture(LOCK, shopGrid[i].bounds.x, shopGrid[i].bounds.y, (Color){255, 255, 255, 200});  // 半透明覆蓋
        }
    }

    // 商品資訊框（滑鼠右鍵顯示）
    if (infoIndex >= 0) {
        if (GetTime() - infoStartTime > 3.0) {
            infoIndex = -1;  
        } else {
            char infoText[256];
            snprintf(infoText, sizeof(infoText), "%s\n%s", shopGrid[infoIndex].name, shopGrid[infoIndex].description);
            RenderItemInfo(infoIndex, itemBounds, infoText);
        }
    }
    
    RenderPurchaseConfirmation();
    RenderUnlockConfirmation();
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








