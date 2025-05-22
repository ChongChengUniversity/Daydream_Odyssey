// ItemCard.c
#include "ItemCard.h"
#include "assetManager.h"  // 引入 assetManager.h 來使用 GetRandomItemType
#include "config.h"
#include <stdlib.h>
#include "CardBase.h"
#include "CardManager.h"
#include "inventory.h"
#include "CharacterStats.h"
#include "CardManager.h"
#include "money.h"
#include "CharacterStats.h"

typedef struct {
    CardBase base;
    ItemType type;
} ItemCard;

// 這裡不再定義 GetRandomItemType，而是引用 assetManager.h 中的函數

static void ResetItem(CardBase *self)
{
    self->isRevealed = false;
}

static void DrawItem(CardBase* self)
{
    ItemCard* card = (ItemCard*)self;
    if (self->isRevealed) 
    {
        if (card->type >= 0 && card->type < ITEM_TYPE_COUNT) {
            Texture2D tex = seasonalItems[currentSeason][card->type];
            DrawTextureEx(tex, (Vector2){ self->bounds.x, self->bounds.y }, 0.0f,
                      (float)TILE_SIZE / tex.width, WHITE);
        } else {
            DrawRectangle(self->bounds.x, self->bounds.y, TILE_SIZE, TILE_SIZE, RED);
            DrawText("ERR", self->bounds.x + 2, self->bounds.y + 2, 10, WHITE);
        }
    } 
    else {
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
    }
}

static void OnRevealItem(CardBase* self)
{
    self->isRevealed = true;
}

static void OnInteractItem(CardBase* self) {
    // different item type has different effects
    // switch case, finish the function, replace by empty cards

    ItemCard *card = (ItemCard *)self;
    if (card->type == ITEM_COIN) {
        AddCoins(10);
    } else if (card->type == ITEM_HP) {
        HealPlayerBySource(HEAL_FROM_POTION);
    } else {
        AddItemToInventory(card->type);
    }

    if (self->isRevealed)
    {   
        switch (card->type)
        {
        case ITEM_COIN:
            break;
        case SCROLL_AOE:
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
        // case SCROLL_TIME:
        //     // put into backpack
        //     break;
        default:
            break;
        }
        ReplaceCardWithEmpty(self->indexInArray, true);
    }
}

CardBase* CreateItemCard(float x, float y, int index, int row, int col, ItemType type)
{
    ItemCard* card = malloc(sizeof(ItemCard));
    if (!card) return NULL;

    card->base.bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->base.isRevealed = false;
    card->base.reset = ResetItem;
    card->base.draw = DrawItem;
    card->base.onReveal = OnRevealItem;
    card->base.onInteract = OnInteractItem;
    card->base.indexInArray = index;
    card->base.row = row;
    card->base.col = col;
    card->type = type;
    card->base.type = TYPE_ITEM;
    return (CardBase*)card;
}