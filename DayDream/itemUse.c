// itemUse.c
#include "itemUse.h"
#include "itemSystem.h"
#include "inventory.h"
#include "raylib.h"
#include "CharacterStats.h"
#include "enemyManager.h"
#include "CardManager.h"
#include <stdio.h>


static ItemUseState itemState = ITEM_STATE_NONE;
static int selectedItemIndex = -1;

static Rectangle quitButtonRect = { SCREEN_WIDTH - 130, SCREEN_HEIGHT - 60, 100, 40 };
static Texture2D quitTexture;

void InitItemUseSystem(void) {
    quitTexture = LoadTexture("assets/quit.png");
}

void UnloadItemUseSystem(void) {
    UnloadTexture(quitTexture);
}

void BeginItemUse(int itemIndex) {
    itemState = ITEM_STATE_WAIT_GRID;
    selectedItemIndex = itemIndex;
}

ItemUseState GetItemUseState(void) {
    return itemState;
}

void UpdateItemUse(Vector2 mousePos) {
    if (itemState != ITEM_STATE_WAIT_GRID) return;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        if (CheckCollisionPointRec(mousePos, quitButtonRect)) {
            itemState = ITEM_STATE_NONE;
            return;
        }

        // 點地圖格子：呼叫卡片互動（可擴充邏輯）
        GridPos pos = GetClickedGrid(mousePos);
        if (pos.row == -1 || pos.col == -1) return;

        ItemType type = inventory[selectedItemIndex].type;
        CardBase* card = GetCardAt(pos.row, pos.col);

        bool valid = false;

        // 判斷是否為合法格子
        if (type == SCROLL_AOE || type == SCROLL_HEAL || type == SCROLL_SHIELD || type == SCROLL_TIME) {
            valid = true; // 可任意點擊
        } else if (type == SCROLL_SINGLE) {
            if (card && card->type == TYPE_ENEMY) { // 會有怪物卡還沒被翻開之前就可以點擊使用道具的問題!!!
                valid = true;
            }
        }

        if (!valid) return;

        // 執行對應道具的效果?

        // 完成使用，減道具數量並結束狀態
        inventory[selectedItemIndex].quantity--;
        if (inventory[selectedItemIndex].quantity <= 0) {
            RemoveInventoryItem(selectedItemIndex);
        }

            itemState = ITEM_STATE_NONE;
    }
}


void DrawItemUseUI(void) {
    if (itemState == ITEM_STATE_WAIT_GRID) {
        DrawText("Click a tile to use the item or Quit", 200, SCREEN_HEIGHT - 750, 30, RED);
        // 顯示道具名稱
        if (selectedItemIndex >= 0 && selectedItemIndex < inventoryCount) 
        {
            ItemType type = inventory[selectedItemIndex].type;
            ItemData* item = GetItemByType(type);
            if (item) {
                int fontSize = 20;
                char line[256];
                snprintf(line, sizeof(line), "%s: %s", item->name, item->description);
                int lineWidth = MeasureText(line, fontSize);
                int lineX = (GetScreenWidth() - lineWidth) / 2;
                DrawText(line, lineX, 90, fontSize, BLACK);
            }
        }
        DrawTextureEx(quitTexture, (Vector2){ quitButtonRect.x, quitButtonRect.y }, 0.0f, 0.5f, WHITE);
    }
}