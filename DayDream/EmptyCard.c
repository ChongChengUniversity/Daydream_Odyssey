// EmptyCard.c
#include "EmptyCard.h"
#include "config.h"
#include <stdlib.h>

static void ResetEmpty(CardBase* self) {
    self->isRevealed = false;
}

static void DrawEmpty(CardBase* self) {
    if (self->isRevealed)
        DrawRectangleRec(self->bounds, BLANK);
    else
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
}

static void OnRevealEmpty(CardBase* self) {
    self->isRevealed = true;
}

static void OnInteractEmpty(CardBase* self) {
    // no interaction for empty cards
}

CardBase* CreateEmptyCard(float x, float y, int index, int row, int col)
{
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL;

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = false;
    card->reset = ResetEmpty;
    card->draw = DrawEmpty;
    card->onReveal = OnRevealEmpty;
    card->onInteract = OnInteractEmpty;
    card->indexInArray = index;
    card->row = row;
    card->col = col;
    card->type = TYPE_EMPTY;
    return card;
}