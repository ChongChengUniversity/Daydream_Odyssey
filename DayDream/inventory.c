// inventory.c
#include "inventory.h"
#include <string.h>
#include "itemUse.h"
#include "backpackicon.h"

// 背包資料
InventoryItem inventory[INVENTORY_CAPACITY];
int inventoryCount = 0;

// 道具圖片縮放比例
float itemScale = 0.1f; 

// 初始化背包
void InitInventory() {
    memset(inventory, 0, sizeof(inventory));
    inventoryCount = 0;
}

// 增加物品到背包
void AddItemToInventory(ItemType type) {
    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].type == type) {
            inventory[i].quantity++;
            return;
        }
    }

    if (inventoryCount < INVENTORY_CAPACITY) {
        inventory[inventoryCount].type = type;
        inventory[inventoryCount].quantity = 1;
        inventoryCount++;
    }
}

// 從背包移除物品
void RemoveInventoryItem(int index) {
    if (index < 0 || index >= inventoryCount) return;

    for (int i = index; i < inventoryCount - 1; i++) {
        inventory[i] = inventory[i + 1];
    }
    inventoryCount--;
}

// 繪製背包 UI
void DrawInventoryUI(Vector2 position, Rectangle screenRect) {
    int cols = 4; // 每列 4 格
    int rows = 4; // 總共 4 列
    float cellSize = 64.0f; // 每個格子的大小（正方形）
    float padding = 45.0f;   // 格子之間的間距

    // 計算背包區域的起始位置（左上）
    float startX = screenRect.x + 90.0f;
    float startY = screenRect.y + 90.0f;

    for (int i = 0; i < inventoryCount; i++) {
        int col = i % cols;
        int row = i / cols;

        // 計算每個道具格子的位置（準確對齊）
        float x = startX + col * (cellSize + padding);
        float y = startY + row * (cellSize + padding);

        Vector2 mousePos = GetMousePosition(); // 取得滑鼠座標

        Rectangle itemRect = {x, y, cellSize, cellSize};

        // 點擊偵測）
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, itemRect)) {
            BeginItemUse(i); // 觸發使用道具流程
            isBackpackOpen = false; // 關閉背包
            SetCurrentBackpackPage(SCREEN_BACKPACK); // 重設為背包頁
            return; // 點到就不再畫其他道具
        }

        // 繪製道具圖片
        Texture2D itemTexture = seasonalItems[currentSeason][inventory[i].type];
        float itemWidth = itemTexture.width * itemScale;
        float itemHeight = itemTexture.height * itemScale;

        float itemX = x + (cellSize - itemWidth) / 2;
        float itemY = y + (cellSize - itemHeight) / 2;

        DrawTextureEx(itemTexture, (Vector2){itemX, itemY}, 0.0f, itemScale, WHITE);

        // 顯示數量
        DrawText(TextFormat("x%d", inventory[i].quantity), x + cellSize - 20, y + cellSize - 20, 18, WHITE);
    }
}

// 道具互動
int GetClickedInventoryIndex(Vector2 mousePos, Rectangle screenRect) {
    int cols = 4;
    float cellSize = 64.0f;
    float padding = 45.0f;
    float startX = screenRect.x + 90.0f;
    float startY = screenRect.y + 90.0f;

    for (int i = 0; i < inventoryCount; i++) {
        int col = i % cols;
        int row = i / cols;
        float x = startX + col * (cellSize + padding);
        float y = startY + row * (cellSize + padding);
        Rectangle itemRect = {x, y, cellSize, cellSize};
        if (CheckCollisionPointRec(mousePos, itemRect)) {
            return i;
        }
    }
    return -1;
}

void ResetInventory(void) {
    inventoryCount = 0;
    for (int i = 0; i < INVENTORY_CAPACITY; i++) {
        inventory[i].type = 0;
        inventory[i].quantity = 0;
    }
}