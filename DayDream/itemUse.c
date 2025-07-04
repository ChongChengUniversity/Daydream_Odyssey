// itemUse.c
#include "itemUse.h"
#include "itemSystem.h"
#include "inventory.h"
#include "raylib.h"
#include "CharacterStats.h"
#include "enemyManager.h"
#include "CardManager.h"
#include <stdio.h>
#include "scrollManager.h"
#include "CardManager.h"
#include "EnemyStats.h"

static ItemUseState itemState = ITEM_STATE_NONE;
static int selectedItemIndex = -1;

static Rectangle quitButtonRect = { SCREEN_WIDTH - 130, SCREEN_HEIGHT - 60, 100, 40 };
static Texture2D quitTexture;

static int targetRow = -1;
static int targetCol = -1;

char message[256] = "";
int messageTimer = 0;

char bossMessage[256] = "";
bool bossMessageVisible = false;

#define MESSAGE_DURATION 90  // 顯示多久幀數 (2秒，如果60FPS)

void SetMessage(const char* text) {
    snprintf(message, sizeof(message), "%s", text);
    messageTimer = MESSAGE_DURATION;
}

ScrollType GetScrollTypeFromItemType(ItemType type) {
    switch (type) {
        case SCROLL_SINGLE: return SCROLL_TYPE_SINGLE;
        case SCROLL_AOE:    return SCROLL_TYPE_AOE;
        case SCROLL_HEAL:   return SCROLL_TYPE_HEAL;
        case SCROLL_SHIELD: return SCROLL_TYPE_SHIELD;
        case SCROLL_TIME:   return SCROLL_TYPE_TIME;
        default: return SCROLL_TYPE_COUNT; // 不合法
    }
}

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
    int messageTimer = 0;
    if (itemState != ITEM_STATE_WAIT_GRID) return;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        if (CheckCollisionPointRec(mousePos, quitButtonRect)) {
            itemState = ITEM_STATE_NONE;
            return;
        }

        // 點地圖格子：呼叫卡片互動（可擴充邏輯）
        GridPos pos = GetClickedGrid(mousePos);
        int row = pos.row, col = pos.col;
        if (pos.row == -1 || pos.col == -1) return;

        ItemType type = inventory[selectedItemIndex].type;
        CardBase* card = GetCardAt(pos.row, pos.col);

        bool valid = false;

        //讀取怪物資訊
        bool isEnemy = IsEnemyCardAt(row, col);
        bool isVisible = false;
        EnemyInfo* enemy = NULL;

        enemy = &enemyInfo[row][col]; 
        isVisible = enemy->isVisible;

        // 判斷是否為合法格子
        if (type == SCROLL_AOE || type == SCROLL_HEAL || type == SCROLL_SHIELD || type == SCROLL_TIME) {
            valid = true; // 可任意點擊
        } 
        else if (type == SCROLL_SINGLE && card && isEnemy) {
            if (isVisible || card->isRevealed) {
                valid = true;
                //使用單體攻擊卷軸時紀錄施放的座標
                targetRow = row;
                targetCol = col;
            }
        }

        if (!valid) return;

        // 執行對應道具的效果?
        bool success = UseScrollEffect(GetScrollTypeFromItemType(type), pos);
    if (success) {
        inventory[selectedItemIndex].quantity--;
        if (inventory[selectedItemIndex].quantity <= 0) {
            RemoveInventoryItem(selectedItemIndex);
        }
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
        // 加上 hover 效果
        Vector2 mouse = GetMousePosition();
        Color quitButtonTint = CheckCollisionPointRec(mouse, quitButtonRect) ? (Color){255, 255, 255, 200} : WHITE;
        DrawTextureEx(quitTexture, (Vector2){ quitButtonRect.x, quitButtonRect.y }, 0.0f, 0.5f, quitButtonTint);
    }

    if (messageTimer > 0) {
        int fontSize = 32;  // 稍微大一點比較好看
        int textWidth = MeasureText(message, fontSize);
        int textHeight = fontSize;  // Raylib的字體高度就是字體大小
        
        // 中心座標
        int posX = (SCREEN_WIDTH - textWidth) / 2;
        int posY = (SCREEN_HEIGHT - textHeight) / 2;

        // 先畫個黑色半透明背景
        DrawRectangle(posX - 20, posY - 10, textWidth + 40, textHeight + 20, (Color){0, 0, 0, 180});

        // 再畫訊息字
        DrawText(message, posX, posY, fontSize, RED);

        messageTimer--;
    }
}   