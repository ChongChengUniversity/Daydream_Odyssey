// shopSystem.h
#pragma once
#include "raylib.h"
#include "assetManager.h"
#include <stdbool.h>

#define SHOP_ROWS 3
#define SHOP_COLS 3
#define LABEL_BUFFER 64 // 名稱與描述字元緩衝大小


typedef struct {
    char name[LABEL_BUFFER];
    char description[128];
    int price;
    Rectangle bounds;
    Texture2D* image;

    bool active;         // 控制是否可互動（例如點擊）
    bool selected;
    bool isSoldOut;      //  新增這個欄位表示是否已售出
    bool locked;         // 是否上鎖

    ItemType type; 
} ShopItem;


// === 商店互動與資訊框 ===
void UpdateShopInteraction(Rectangle* itemBounds, int itemCount, int* hoverIndex, int* infoIndex, const bool* isActive);
void RenderItemHover(int hoverIndex, Rectangle* itemBounds, int itemCount);
void RenderItemInfo(int infoIndex, Rectangle* itemBounds, const char* infoText);

// === 購買系統 ===
void RenderPurchaseConfirmation(void);
void RenderPurchaseMessage(void);
bool TryPurchaseAtIndex(int index);
void RenderUnlockConfirmation(void);
void TryOpenUnlockDialog(int index);
void FillScrollsForFloor(int floor, int* filled);

ItemType GetRandomScrollTypeForLevel9();