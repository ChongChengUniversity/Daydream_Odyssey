// CardManager.c
#include "CardBase.h"
#include "EnemyCard.h"
#include "ItemCard.h"
#include "DoorCard.h"
#include "EmptyCard.h"
#include "KeyCard.h"
#include "config.h"
#include "raylib.h"
#include "assetManager.h"
#include <stdlib.h>
#include <string.h>

#define TOTAL_CARDS (COLS * ROWS)

CardBase *cards[TOTAL_CARDS];

typedef enum
{
    TYPE_DOOR,
    TYPE_ITEM,
    TYPE_ENEMY,
    TYPE_EMPTY,
    TYPE_KEY
} CardType;

CardType cardTypes[TOTAL_CARDS];

// Control how each cards should appear, giving out index
void InitCardTypes()
{
    int index = 0;
    cardTypes[index++] = TYPE_DOOR; // only one
    for (int i = 0; i < 14; ++i)
        cardTypes[index++] = TYPE_ITEM;
    for (int i = 0; i < 3; ++i)
        cardTypes[index++] = TYPE_ENEMY;
    cardTypes[index++] = TYPE_KEY; // only one
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

// for function AbleToReveal()
static int indexdoorRow = -1;
static int indexdoorCol = -1;

// create cards
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
                cards[card_index] = CreateDoorCard(x, y, card_index);
                indexdoorRow = row; // pos of the door
                indexdoorCol = col;
                break;
            case TYPE_ITEM:
                cards[card_index] = CreateItemCard(x, y, card_index, GetRandomItemType());
                break;
            case TYPE_ENEMY:
                cards[card_index] = CreateEnemyCard(x, y, card_index);
                break;
            case TYPE_EMPTY:
                cards[card_index] = CreateEmptyCard(x, y, card_index);
                break;
            case TYPE_KEY:
                cards[card_index] = CreateKeyCard(x, y, card_index);
                break;
            }
            card_index++;
        }
    }
}

// 表示格子位置

typedef struct
{
    int row;
    int col;
} GridPos;

// turn to 5*5 blocks
GridPos GetCardGridPosition(Rectangle bounds)
{
    GridPos pos;

    int start_x = BOARD_START_X;

    int start_y = BOARD_START_Y;

    pos.col = (bounds.x - start_x - TILE_GAP) / (TILE_SIZE + TILE_GAP);

    pos.row = (bounds.y - start_y - TILE_GAP) / (TILE_SIZE + TILE_GAP);

    return pos;
}

// control how many blocks should be revealed
int abletoReveal[ROWS][COLS] = {0};

// scan all the blocks everytime
void AbleToReveal()
{
    memset(abletoReveal, 0, sizeof(abletoReveal)); // reset every time

    for (int i = 0; i < COLS * ROWS; ++i)
    {
        if (cards[i] != NULL && cards[i]->isRevealed == 1)
        {

            GridPos pos = GetCardGridPosition(cards[i]->bounds);

            if (pos.row > 0)
                abletoReveal[pos.row - 1][pos.col] = 1;

            if (pos.row < ROWS - 1)
                abletoReveal[pos.row + 1][pos.col] = 1;

            if (pos.col > 0)
                abletoReveal[pos.row][pos.col - 1] = 1;

            if (pos.col < COLS - 1)
                abletoReveal[pos.row][pos.col + 1] = 1;
        }
    }
}

void RevealDoorCardAtStart()
{
    for (int i = 0; i < COLS * ROWS; ++i)
    {
        GridPos pos = GetCardGridPosition(cards[i]->bounds);

        if (indexdoorCol == pos.col && indexdoorRow == pos.row)
        {

            cards[i]->onReveal(cards[i]);

            AbleToReveal();

            break;
        }
    }
}

void DrawAllCards()
{
    AbleToReveal();
    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        GridPos pos = GetCardGridPosition(cards[i]->bounds);

        if (cards[i])
        {
            if (abletoReveal[pos.row][pos.col] == 1 && cards[i]->isRevealed != 1)
            {
                DrawRectangleRec(cards[i]->bounds, BLUE);
            }
            else
            {
                cards[i]->draw(cards[i]);
            }
        }
    }
}

// 1. click once: reveal card; 2. click twice: interactions
void OnMouseClick(Vector2 mousePos)
{
    AbleToReveal();

    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        // if click
        if (cards[i] && CheckCollisionPointRec(mousePos, cards[i]->bounds))
        {
            GridPos pos = GetCardGridPosition(cards[i]->bounds);

            if (abletoReveal[pos.row][pos.col] == 1)
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
}

// 1. if enemy died, turn into empty cards; 2. if get key or items turn into empty cards
void ReplaceCardWithEmpty(int index)
{
    float x = cards[index]->bounds.x;

    float y = cards[index]->bounds.y;

    free(cards[index]); // free the EnemyCard

    cards[index] = CreateEmptyCard(x, y, index); // replace by empty card

    cards[index]->onReveal(cards[index]);

    cardTypes[index] = TYPE_EMPTY; // change its type
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