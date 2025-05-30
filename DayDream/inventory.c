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

void DrawInventoryUI(Vector2 position, Rectangle screenRect) {
    int cols = 3; // 每列 3 格
    int rows = 3; // 總共 3 列
    float cellSize = 64.0f;
    float padding = 90.0f;

    float startX = screenRect.x + 170.0f;
    float startY = screenRect.y + 100.0f;

    for (int i = 0; i < inventoryCount; i++) {
        int col = i % cols;
        int row = i / cols;

        float yOffset = 0.0f;
        if (row == 1) yOffset = -20.0f;  // 第二列往上移 20 像素

        float x = startX + col * (cellSize + padding);
        float y = startY + row * (cellSize + padding) + yOffset;

        Vector2 mousePos = GetMousePosition();
        Rectangle itemRect = { x, y, cellSize, cellSize };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, itemRect)) {
            BeginItemUse(i);
            isBackpackOpen = false;
            SetCurrentBackpackPage(SCREEN_BACKPACK);
            return;
        }

        Texture2D itemTexture = seasonalItems[currentSeason][inventory[i].type];
        float itemWidth = itemTexture.width * itemScale;
        float itemHeight = itemTexture.height * itemScale;

        float itemX = x + (cellSize - itemWidth) / 2;
        float itemY = y + (cellSize - itemHeight) / 2;

        DrawTextureEx(itemTexture, (Vector2) { itemX, itemY }, 0.0f, itemScale, WHITE);

        // 顯示道具數量
        DrawText(TextFormat("x%d", inventory[i].quantity), x + cellSize - 20, y + cellSize - 20, 18, WHITE);
    }
}

// 道具互動
int GetClickedInventoryIndex(Vector2 mousePos, Rectangle screenRect) {
    int cols = 3;
    float cellSize = 64.0f;
    float padding = 90.0f;
    float startX = screenRect.x + 170.0f;
    float startY = screenRect.y + 100.0f;

    for (int i = 0; i < inventoryCount; i++) {
        int col = i % cols;
        int row = i / cols;

        float yOffset = 0.0f;
        if (row == 1) yOffset = -20.0f;

        float x = startX + col * (cellSize + padding);
        float y = startY + row * (cellSize + padding) + yOffset;
        Rectangle itemRect = { x, y, cellSize, cellSize };

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