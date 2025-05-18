// ItemCard.c
#include "ItemCard.h"
#include "config.h"
#include "assetManager.h"
#include <stdlib.h>
#include "CardManager.h"
#include "CharacterStats.h"
#include "inventory.h"
#include "CardManager.h"

typedef struct
{
    CardBase base;
    ItemType type;
} ItemCard;

static void ResetItem(CardBase *self)
{
    self->isRevealed = false;
}

static void DrawItem(CardBase *self)
{
    ItemCard *card = (ItemCard *)self;
    if (self->isRevealed)
    {
        Texture2D tex = seasonalItems[currentSeason][card->type];
        DrawTextureEx(tex, (Vector2){self->bounds.x, self->bounds.y}, 0.0f,
                      (float)TILE_SIZE / tex.width, WHITE);
    }
    else
    {
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
    }
}

static void OnRevealItem(CardBase *self)
{
    self->isRevealed = true;
}

static void OnInteractItem(CardBase *self)
{
    // different item type has different effects
    // switch case, finish the function, replace by empty cards

    ItemCard *card = (ItemCard *)self;
    AddItemToInventory(card->type); // add items into backpack(**not every item!)

    if (self->isRevealed)
    {   
        switch (card->type)
        {
        case ITEM_HP: // apply when collected
            ApplyEquipmentToPlayer(5, 0, 0);
            break;
        case ITEM_MP:
            break;
        case ITEM_COIN:
            break;
        case SCROLL_AOE:
            // ApplyDamageToEnemy(all_enemy, 5);
            break;
        case SCROLL_HEAL:
            // put into backpack
            break;
        case SCROLL_SHIELD:
            // put into backpack
            break;
        case SCROLL_SINGLE:
            // put into backpack
            break;
        case SCROLL_TIME:
            // put into backpack
            break;
        default:
            break;
        }

        ReplaceCardWithEmpty(self->indexInArray);
    }
}

CardBase *CreateItemCard(float x, float y, int index, ItemType type)
{
    ItemCard *card = malloc(sizeof(ItemCard));
    if (!card)
        return NULL;

    card->base.bounds = (Rectangle){x, y, TILE_SIZE, TILE_SIZE};
    card->base.isRevealed = false;
    card->base.reset = ResetItem;
    card->base.draw = DrawItem;
    card->base.onReveal = OnRevealItem;
    card->base.onInteract = OnInteractItem;
    card->type = type;
    card->base.indexInArray = index;

    return (CardBase *)card;
}