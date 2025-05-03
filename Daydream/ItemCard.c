// ItemCard.c
#include "ItemCard.h"
#include "config.h"
#include "assetManager.h"
#include <stdlib.h>

typedef struct {
    CardBase base;
    ItemType type;
} ItemCard;

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
}

CardBase* CreateItemCard(float x, float y, ItemType type) {
    ItemCard* card = malloc(sizeof(ItemCard));
    if (!card) return NULL;

    card->base.bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->base.isRevealed = false;
    card->base.reset = ResetItem;
    card->base.draw = DrawItem;
    card->base.onReveal = OnRevealItem;
    card->base.onInteract = OnInteractItem;
    card->type = type;

    return (CardBase*)card;
}