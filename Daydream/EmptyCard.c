// EmptyCard.c
#include "EmptyCard.h"
#include "config.h"
#include <stdlib.h>

//把牌一律改為未翻開狀態
static void ResetEmpty(CardBase* self) {
    self->isRevealed = false;
}

static void DrawEmpty(CardBase* self) {
    if (self->isRevealed)
        DrawRectangleRec(self->bounds, LIGHTGRAY); // ½�}�e�Ǧ�
    else
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
}

static void OnRevealEmpty(CardBase* self) {
    self->isRevealed = true;
    // �ťեd�S���S�O�ĪG
}

static void OnInteractEmpty(CardBase* self) {
    // ���򳣤���
}

CardBase* CreateEmptyCard(float x, float y, int index) {
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL; // �p�G malloc ���ѡA�����^�� NULL

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = false;
    card->reset = ResetEmpty;
    card->draw = DrawEmpty;
    card->onReveal = OnRevealEmpty;
    card->onInteract = OnInteractEmpty;
    card->indexInArray = index;
    return card;
}