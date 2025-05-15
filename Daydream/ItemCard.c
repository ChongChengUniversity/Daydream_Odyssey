// ItemCard.c
#include "ItemCard.h"
#include "assetManager.h"  // 引入 assetManager.h 來使用 GetRandomItemType
#include "config.h"
#include <stdlib.h>

#include "inventory.h"  // 背包系統
#include "cardManager.h" // 換成空白格

typedef struct {
    CardBase base;
    ItemType type;
} ItemCard;

// 這裡不再定義 GetRandomItemType，而是引用 assetManager.h 中的函數

static void ResetItem(CardBase* self) {
    self->isRevealed = false;
}

static void DrawItem(CardBase* self) {
    ItemCard* card = (ItemCard*)self;
    if (self->isRevealed) {
        Texture2D tex = seasonalItems[currentSeason][card->type];
        DrawTextureEx(tex, (Vector2){ self->bounds.x, self->bounds.y }, 0.0f,
                      (float)TILE_SIZE / tex.width, WHITE);
    } else {
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
    }
}

static void OnRevealItem(CardBase* self) {
    self->isRevealed = true;
}

static void OnInteractItem(CardBase* self) {
    // 可以依據 item type 設計效果
    ItemCard* card = (ItemCard*)self;
    
    // 將道具加入背包
    AddItemToInventory(card->type);
    
    // 轉換成空白格（已翻開）
    ReplaceItemCardWithEmpty(self->indexInArray);
}

CardBase* CreateItemCard(float x, float y, int index, ItemType type) {
    ItemCard* card = malloc(sizeof(ItemCard));
    if (!card) return NULL;

    card->base.bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->base.isRevealed = false;
    card->base.reset = ResetItem;
    card->base.draw = DrawItem;
    card->base.onReveal = OnRevealItem;
    card->base.onInteract = OnInteractItem;
    card->type = type;
    card->base.indexInArray = index;

    return (CardBase*)card;
}
