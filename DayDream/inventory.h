// inventory.h
#pragma once
#include "assetManager.h"
#include "raylib.h"

// 背包最大容量
#define INVENTORY_CAPACITY 16

// 背包中的物品結構
typedef struct {
    ItemType type;
    int quantity;
} InventoryItem;

// 背包資料
extern InventoryItem inventory[INVENTORY_CAPACITY];
extern int inventoryCount;

// 初始化背包
void InitInventory();
// 增加物品到背包
void AddItemToInventory(ItemType type);
// 從背包移除物品

// 繪製背包 UI
void DrawInventoryUI(Vector2 position, Rectangle screenRect);
