// KeyCard.c
#include "KeyCard.h"
#include "config.h"
#include <stdlib.h>
#include "stateController.h"
#include "assetManager.h"
#include "levelManager.h"
#include "CardManager.h"

static void ResetKey(CardBase *self)
{
    self->isRevealed = false;
}

static void DrawKey(CardBase *self)
{
    if (!self->isRevealed) {
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
        return;
    }

    DrawTextureEx(textures[TEXTURE_KEY], (Vector2){self->bounds.x, self->bounds.y}, 0.0f,
        (float)TILE_SIZE / textures[TEXTURE_DOOR].width, WHITE);
}

static void OnRevealKey(CardBase *self)
{
    self->isRevealed = true;
}

static void OnInteractKey(CardBase *self)
{
    if (self->isRevealed)
    {
        AcquireKey(); // hasKey = true
        ReplaceCardWithEmpty(self->indexInArray, true);
    }
}

CardBase *CreateKeyCard(float x, float y, int index, int row, int col)
{ 
    CardBase *card = malloc(sizeof(CardBase));
    if (!card)return NULL;

    card->bounds = (Rectangle){x, y, TILE_SIZE, TILE_SIZE};
    card->isRevealed = false;
    card->reset = ResetKey;
    card->draw = DrawKey;
    card->onReveal = OnRevealKey;
    card->onInteract = OnInteractKey;
    card->indexInArray = index;
    card->row = row;
    card->col = col;
    return card;
}