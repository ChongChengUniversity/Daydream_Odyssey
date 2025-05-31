// portalCard.c
#include "portalCard.h"
#include "config.h"
#include <stdlib.h>
#include "assetManager.h"
#include "stateController.h"
#include "endingChoice.h" // 如果需要觸發選擇
#include "story.h"
#include "dialogues.h"

static void ResetPortal(CardBase* self) {
    self->isRevealed = false;
}

static void DrawPortal(CardBase* self) {
    if (!self->isRevealed) {
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
        return;
    }

    DrawTextureEx(textures[TEXTURE_PORTAL], (Vector2) { self->bounds.x, self->bounds.y }, 0.0f,
        (float)TILE_SIZE / textures[TEXTURE_DOOR].width, WHITE);
}

static void OnRevealPortal(CardBase* self) {
    self->isRevealed = true;
}

static void OnInteractPortal(CardBase* self) {
    if (self->isRevealed)
    {
        GOTO(ENDING_CHOICE);
    }
}

CardBase* CreatePortalCard(float x, float y, int index, int row, int col)
{
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL;

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = false;
    card->reset = ResetPortal;
    card->draw = DrawPortal;
    card->onReveal = OnRevealPortal;
    card->onInteract = OnInteractPortal;
    card->indexInArray = index;
    card->row = row;
    card->col = col;
    card->type = TYPE_PORTAL;
    return card;
}