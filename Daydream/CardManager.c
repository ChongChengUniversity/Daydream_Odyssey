// CardManager.c
#include "CardBase.h"
#include "EnemyCard.h"
#include "ItemCard.h"
#include "DoorCard.h"
#include "EmptyCard.h"
#include "config.h"
#include "raylib.h"
#include "assetManager.h"
#include <stdlib.h>

#define TOTAL_CARDS (COLS * ROWS)

CardBase *cards[TOTAL_CARDS];

typedef enum
{
    TYPE_DOOR,
    TYPE_ITEM,
    TYPE_ENEMY,
    TYPE_EMPTY
} CardType;

CardType cardTypes[TOTAL_CARDS];

void InitCardTypes()
{
    int index = 0;
    cardTypes[index++] = TYPE_DOOR;
    for (int i = 0; i < 14; ++i)
        cardTypes[index++] = TYPE_ITEM;
    for (int i = 0; i < 1; ++i)
        cardTypes[index++] = TYPE_ENEMY;
    while (index < TOTAL_CARDS)
        cardTypes[index++] = TYPE_EMPTY;

    for (int i = TOTAL_CARDS - 1; i > 0; --i) // wdym?
    {
        int j = GetRandomValue(0, i);
        CardType temp = cardTypes[i];
        cardTypes[i] = cardTypes[j];
        cardTypes[j] = temp;
    }
}

void InitCards()
{
    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        cards[i] = NULL;
    }

    InitCardTypes();

    int card_index = 0;
    int start_x = BOARD_START_X;
    int start_y = BOARD_START_Y;

    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            float x = start_x + TILE_GAP + col * (TILE_SIZE + TILE_GAP);
            float y = start_y + TILE_GAP + row * (TILE_SIZE + TILE_GAP);

            switch (cardTypes[card_index])
            {
            case TYPE_DOOR:
                cards[card_index] = CreateDoorCard(x, y);
                break;
            case TYPE_ITEM:
                cards[card_index] = CreateItemCard(x, y, GetRandomItemType());
                break;
            case TYPE_ENEMY:
                cards[card_index] = CreateEnemyCard(x, y);
                break;
            case TYPE_EMPTY:
                cards[card_index] = CreateEmptyCard(x, y);
                break;
            }
            card_index++;
        }
    }
}

void DrawAllCards()
{
    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        if (cards[i])
        {
            cards[i]->draw(cards[i]);
        }
    }
}

void OnMouseClick(Vector2 mousePos)
{
    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        if (cards[i] && CheckCollisionPointRec(mousePos, cards[i]->bounds))
        {
            if (!cards[i]->isRevealed)
            {
                cards[i]->onReveal(cards[i]);
            }
            else
            {
                if (cards[i]->onInteract)
                {
                    cards[i]->onInteract(cards[i]);
                }
            }
            break;
        }
    }
}

void ResetAllCards()
{
    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        if (cards[i])
        {
            cards[i]->reset(cards[i]);
        }
    }
}