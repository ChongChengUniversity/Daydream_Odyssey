// EmptyCard.c
#include "EmptyCard.h"
#include "config.h"
#include <stdlib.h>

static void ResetEmpty(CardBase* self) {
    self->isRevealed = false;
}

static void DrawEmpty(CardBase* self) {
    if (self->isRevealed)
        DrawRectangleRec(self->bounds, LIGHTGRAY); // 翻開畫灰色
    else
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
}

static void OnRevealEmpty(CardBase* self) {
    self->isRevealed = true;
    // 空白卡沒有特別效果
}

static void OnInteractEmpty(CardBase* self) {
    // 什麼都不做
}

CardBase* CreateEmptyCard(float x, float y) {
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL; // 如果 malloc 失敗，直接回傳 NULL

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = false;
    card->reset = ResetEmpty;
    card->draw = DrawEmpty;
    card->onReveal = OnRevealEmpty;
    card->onInteract = OnInteractEmpty;
    return card;
}