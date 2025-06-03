// ItemCard.c
#include "ItemCard.h"
#include "config.h"
#include "assetManager.h"
#include <stdlib.h>

static void ResetItem(CardBase* self) {
    self->isRevealed = false;
}

static void DrawItem(CardBase* self) {
    if (self->isRevealed)
        DrawTextureEx(textures[TEXTURE_ITEM], (Vector2) { self->bounds.x, self->bounds.y }, 0.0f,
            (float)TILE_SIZE / textures[TEXTURE_ITEM].width, WHITE);
    else
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
}

static void OnRevealItem(CardBase* self) {
    self->isRevealed = true;
    // �o��i�H�[�G�[���޿�
}

static void OnInteractItem(CardBase* self) {
    // �ĤH�Q���ĤG���A�i�H�]�p������Bĵ�i����
}

CardBase* CreateItemCard(float x, float y) {
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL; // �p�G malloc ���ѡA�����^�� NULL

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = false;
    card->reset = ResetItem;
    card->draw = DrawItem;
    card->onReveal = OnRevealItem;
    card->onInteract = OnInteractItem;
    return card;
}