// shopSystem.c
#include "shopSystem.h"
#include "equipmentSystem.h"
#include "itemSystem.h"       // ✅ 引入道具系統
#include "money.h"
#include "assetManager.h"
#include "raylib.h"
#include "config.h"
#include "state_shop.h"
#include "audioManager.h"
#include <stdio.h>
#include <string.h>

extern Texture2D SOLD_OUT;
extern ShopItem shopGrid[]; // 提供商店格子資料給購買邏輯

// 商品資訊
double infoStartTime = 0;


// === 購買視窗狀態 ===
static bool confirmVisible = false;
static int confirmIndex = -1;
static double confirmStartTime = 0; 

// === 上鎖視窗狀態 ===
static bool unlockConfirmVisible = false;
static int unlockIndex = -1;
static double unlockStartTime = 0;

// === 顯示簡單訊息框（暫停式） ===
// 簡易訊息框
static void ShowMessageBoxBlocking(const char* message, Color color) {
    const int w = 280, h = 80;
    Rectangle box = {
        SCREEN_WIDTH / 2 - w / 2,
        SCREEN_HEIGHT / 2 - h / 2 + 100,
        w, h
    };

    double start = GetTime();
    while (GetTime() - start < 0.4) {
        BeginDrawing();
        DrawRectangleRec(box, (Color){30, 30, 30, 230});
        DrawRectangleLinesEx(box, 2, color);
        int textW = MeasureText(message, 20);
        DrawText(message, box.x + (w - textW) / 2, box.y + 28, 20, color);
        EndDrawing();
    }
}

void UpdateShopInteraction(Rectangle* itemBounds, int itemCount, int* hoverIndex, int* infoIndex, const bool* isActive) {
    Vector2 mouse = GetMousePosition();
    *hoverIndex = -1;

    for (int i = 0; i < itemCount; ++i) {
        if (!isActive[i]) continue;

        if (CheckCollisionPointRec(mouse, itemBounds[i])) {
            *hoverIndex = i;

            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                *infoIndex = i; // 顯示道具資訊
                infoStartTime = GetTime();  
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && *hoverIndex == -1) {
        *infoIndex = -1; // 點空白區域關閉資訊框
    }

    if (!confirmVisible && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && *hoverIndex >= 0 && isActive[*hoverIndex]) {
        ShopItem* item = &shopGrid[*hoverIndex];
    
        if (item->locked) {
            // 鎖住的商品 -> 顯示解鎖視窗
            TryOpenUnlockDialog(*hoverIndex);  
            return;
        }
    
        if (!item->isSoldOut) {
            // 可購買的商品才顯示購買視窗
            confirmIndex = *hoverIndex;
            confirmVisible = true;
            confirmStartTime = 0;
        }
    }
    
}

void RenderItemHover(int hoverIndex, Rectangle* itemBounds, int itemCount) {
    if (hoverIndex >= 0 && hoverIndex < itemCount) {
        DrawRectangleRec(itemBounds[hoverIndex], (Color){220, 180, 100, 100});
    }
}

void RenderItemInfo(int infoIndex, Rectangle* itemBounds, const char* infoText) {
    if (infoIndex < 0) return;

    int infoWidth = 240;
    int infoHeight = 80;
    int padding = 10;

    Rectangle box = {
        itemBounds[infoIndex].x + (itemBounds[infoIndex].width / 2) - (infoWidth / 2),
        itemBounds[infoIndex].y - infoHeight - 10,
        infoWidth,
        infoHeight
    };

    DrawRectangleRec(box, (Color){50, 50, 50, 230});
    DrawRectangleLinesEx(box, 2, GOLD);
    DrawText(infoText, box.x + padding, box.y + padding, 18, RAYWHITE);
}

void RenderPurchaseConfirmation() {
    if (!confirmVisible || confirmIndex < 0) return;

    if (confirmStartTime == 0) confirmStartTime = GetTime();
    if (GetTime() - confirmStartTime > 3.0) {
        confirmVisible = false;
        confirmStartTime = 0;
        return;
    }

    ShopItem* item = &shopGrid[confirmIndex];

    const int w = 320, h = 160;
    Rectangle box = {
        SCREEN_WIDTH / 2 - w / 2,
        SCREEN_HEIGHT / 2 - h / 2,
        w, h
    };

    Vector2 mouse = GetMousePosition();
    DrawRectangleRec(box, (Color){40, 40, 40, 250});
    DrawRectangleLinesEx(box, 2, GOLD);

    DrawText("Confirm Purchase?", box.x + 20, box.y + 20, 24, RAYWHITE);
    DrawText(item->name, box.x + 20, box.y + 60, 20, LIGHTGRAY);

    char priceText[64];
    snprintf(priceText, sizeof(priceText), "Price: %d coins", item->price);
    DrawText(priceText, box.x + 20, box.y + 90, 20, GOLD);

    DrawText("[Y] Yes", box.x + 40, box.y + 120, 20, GREEN);
    DrawText("[N] No", box.x + 180, box.y + 120, 20, RED);

    if (IsKeyPressed(KEY_Y)) {
        bool success = TryPurchaseAtIndex(confirmIndex);
        confirmVisible = false;
        confirmStartTime = 0;
        ShowMessageBoxBlocking(success ? "Purchase Successful!" : "Not enough coins!", success ? GREEN : RED);
    }
    if (IsKeyPressed(KEY_N)) {
        confirmVisible = false;
        confirmStartTime = 0;
    } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // 若點到不是確認視窗的範圍，也不是商品格，才關閉
        bool clickOutsideBox = !CheckCollisionPointRec(mouse, box);
    
        // 確認沒點到任何商品格子
        bool clickOutsideAllItems = true;
        for (int i = 0; i < SHOP_ROWS * SHOP_COLS; i++) {
            if (CheckCollisionPointRec(mouse, shopGrid[i].bounds)) {
                clickOutsideAllItems = false;
                break;
            }
        }
    
        if (clickOutsideBox && clickOutsideAllItems) {
            confirmVisible = false;
            confirmStartTime = 0;
        }
    }
    
}

void RenderUnlockConfirmation() {
    if (!unlockConfirmVisible || unlockIndex < 0) return;

    // ✅ 初始化時間
    if (unlockStartTime == 0) unlockStartTime = GetTime();

    // ✅ 自動關閉視窗（超過3秒）
    if (GetTime() - unlockStartTime > 3.0) {
        unlockConfirmVisible = false;
        unlockIndex = -1;
        unlockStartTime = 0;
        return;
    }

    ShopItem* item = &shopGrid[unlockIndex];

    // 找出該裝備對象
    EquipmentData* eq = NULL;
    for (int i = 0; i < GetTotalEquipments(); ++i) {
        EquipmentData* temp = GetEquipmentByIndex(i);
        if (temp && strcmp(temp->name, item->name) == 0) {
            eq = temp;
            break;
        }
    }

    const int w = 320, h = 160;
    Rectangle box = {
        SCREEN_WIDTH / 2 - w / 2,
        SCREEN_HEIGHT / 2 - h / 2,
        w, h
    };

    Vector2 mouse = GetMousePosition();

    // ✅ 點擊外部視窗則關閉（包含非商品格）
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        bool clickOutsideBox = !CheckCollisionPointRec(mouse, box);
        bool clickOutsideAllItems = true;

        for (int i = 0; i < SHOP_ROWS * SHOP_COLS; i++) {
            if (CheckCollisionPointRec(mouse, shopGrid[i].bounds)) {
                clickOutsideAllItems = false;
                break;
            }
        }

        if (clickOutsideBox && clickOutsideAllItems) {
            unlockConfirmVisible = false;
            unlockIndex = -1;
            unlockStartTime = 0;
            return;
        }
    }

    // === 視窗繪製 ===
    DrawRectangleRec(box, (Color){50, 30, 30, 250});
    DrawRectangleLinesEx(box, 2, GOLD);
    DrawText("Unlock this slot?", box.x + 20, box.y + 20, 24, WHITE);

    char priceText[64];
    snprintf(priceText, sizeof(priceText), "Unlock cost: 1 coins");
    DrawText(priceText, box.x + 20, box.y + 60, 20, GOLD);

    DrawText("[Y] Yes", box.x + 40, box.y + 110, 20, GREEN);
    DrawText("[N] No", box.x + 180, box.y + 110, 20, RED);

    // === 處理輸入 ===
    if (IsKeyPressed(KEY_Y)) {
        if (GetPlayerCoins() >= 1) {
            SubtractCoins(1);
            GamePlaySound(SOUND_FIVE);
            ShowMessageBoxBlocking("Unlocked!", GREEN);

            if (eq->slot == SLOT_ACCESSORY) 
                UnlockAllAccessorySlots();  
            if (eq->slot == SLOT_FOOT) 
                UnlockAllBootSlots();        

            item->locked = false;
            eq->locked = false;
        } else {
            GamePlaySound(SOUND_FOUR);
            ShowMessageBoxBlocking("Not enough coins!", RED);
        }

        unlockConfirmVisible = false;
        unlockIndex = -1;
        unlockStartTime = 0;
    }

    if (IsKeyPressed(KEY_N)) {
        unlockConfirmVisible = false;
        unlockIndex = -1;
        unlockStartTime = 0;
    }
}

bool TryPurchaseAtIndex(int index) {
    ShopItem* item = &shopGrid[index];

    // === 嘗試購買裝備 ===
    if ((int)item->type == -1) {  // 裝備的 type = -1，代表這是裝備
        for (int i = 0; i < GetTotalEquipments(); ++i) {
            EquipmentData* eq = GetEquipmentByIndex(i);
            if (eq && strcmp(eq->name, item->name) == 0) {

                if (GetPlayerCoins() >= eq->price) {
                    SubtractCoins(eq->price);
                    eq->isPurchased = 1;
                    item->isSoldOut = true;
                    item->active = false;
                    ShowMessageBoxBlocking("Purchase Successful!", GREEN);
                    GamePlaySound(SOUND_FIVE);
                    return true;
                } else {
                    ShowMessageBoxBlocking("Not enough coins!", RED);
                    GamePlaySound(SOUND_FOUR);
                    return false;
                }
            }
        }
    }

    // === 嘗試購買道具 ===
    if (item->type >= 0 && item->type < ITEM_TYPE_COUNT) {
        ItemData* it = GetItemByType(item->type);

        if (GetPlayerCoins() >= it->price) {
            SubtractCoins(it->price);
            it->isPurchased = 1;
            item->active = false;
            item->isSoldOut = true;
            ShowMessageBoxBlocking("Purchase Successful!", GREEN);
            GamePlaySound(SOUND_FIVE);
            return true;
        } else {
            ShowMessageBoxBlocking("Not enough coins!", RED);
            GamePlaySound(SOUND_FOUR);
            return false;
        }
    }

    // 防呆結尾
    ShowMessageBoxBlocking("Item not found!", RED);
    return false;
}


void TryOpenUnlockDialog(int index) {
    unlockIndex = index;
    unlockConfirmVisible = true;
    unlockStartTime = GetTime(); 
}



