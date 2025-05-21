// DoorCard.c
#include "DoorCard.h"
#include "config.h"
#include <stdlib.h>
#include "stateController.h"
#include "assetManager.h"
#include "levelManager.h" // ���F�P�_�O�_�̫�@��
// #include "CardBase.h"

static void ResetDoor(CardBase *self)
{
    self->isRevealed = false;
}

static void DrawDoor(CardBase *self)
{
    DrawTextureEx(textures[TEXTURE_DOOR], (Vector2){self->bounds.x, self->bounds.y}, 0.0f,
                (float)TILE_SIZE / textures[TEXTURE_DOOR].width, WHITE);
}

static void OnRevealDoor(CardBase *self)
{
    self->isRevealed = true;
}

static void OnInteractDoor(CardBase *self)
{

    if (self->isRevealed)
    {
        if (IsFinalLevel() && HasKey())
        {
            GOTO(WIN);
        }
        else if (HasKey())
        {
            NextLevel();
            GOTO(PLAYING);
        }
    }
}

CardBase* CreateDoorCard(float x, float y, int index, int row, int col)
{
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL;

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = false;
    card->reset = ResetDoor;
    card->draw = DrawDoor;
    card->onReveal = OnRevealDoor;
    card->onInteract = OnInteractDoor;
    card->indexInArray = index;
    card->row = row;
    card->col = col;
    card->type = TYPE_DOOR;
    return card;
}
