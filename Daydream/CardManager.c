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
#include "ItemCard.h" 
#include <string.h> 

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

//賦予每個牌種類並打散
void InitCardTypes()
{
    int index = 0;
    cardTypes[index++] = TYPE_DOOR;
    for (int i = 0; i < 14; ++i)
        cardTypes[index++] = TYPE_ITEM;
    for (int i = 0; i < 3; ++i)
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

int indexdoorRow = -1;     
int indexdoorCol = -1; 

//記錄每張牌的種類位置&各自要執行的函式
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
                indexdoorRow = row;     //紀錄門的位置
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
            }
            card_index++;
        }
    }
}

// 表示格子位置
typedef struct {
    int row;
    int col;
} GridPos;

// 將實際座標轉換成 5x5 格子位置
GridPos GetCardGridPosition(Rectangle bounds) {
    GridPos pos;
    int start_x = BOARD_START_X;
    int start_y = BOARD_START_Y;
    pos.col = (bounds.x - start_x - TILE_GAP) / (TILE_SIZE + TILE_GAP);
    pos.row = (bounds.y - start_y - TILE_GAP) / (TILE_SIZE + TILE_GAP);
    return pos;
}

// 控制哪些格子允許被翻開
int abletoReveal[ROWS][COLS] = {0}; 

//每次掃描全部格子紀錄允許翻開的卡片
void AbleToReveal(){
    memset(abletoReveal, 0, sizeof(abletoReveal));  // 每次重設

    for (int i = 0; i < COLS * ROWS; ++i){
        if (cards[i] != NULL && cards[i]->isRevealed == 1){
            GridPos pos = GetCardGridPosition(cards[i]->bounds);

            if (pos.row > 0) abletoReveal[pos.row - 1][pos.col] = 1;
            if (pos.row < ROWS - 1) abletoReveal[pos.row + 1][pos.col] = 1;
            if (pos.col > 0) abletoReveal[pos.row][pos.col - 1] = 1;
            if (pos.col < COLS - 1) abletoReveal[pos.row][pos.col + 1] = 1;
        }
    }
}

//一開始自動翻開門並更新可翻開卡片
void RevealDoorCardAtStart(){
    for (int i = 0; i < COLS * ROWS; ++i){
        GridPos pos = GetCardGridPosition(cards[i]->bounds);
        if(indexdoorCol == pos.col && indexdoorRow == pos.row){
            cards[i]->onReveal(cards[i]);
            AbleToReveal();
            break;
        }
    }
}

//畫出所有卡片
void DrawAllCards()
{
    AbleToReveal();
    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        GridPos pos = GetCardGridPosition(cards[i]->bounds);

        if (cards[i])
        {
            if(abletoReveal[pos.row][pos.col]==1 && cards[i]->isRevealed!=1){
                DrawRectangleRec(cards[i]->bounds, BLUE);
            }
            else{
                cards[i]->draw(cards[i]);
            }
        }
    }
}

//滑鼠點到的卡片第一次狀態改為已翻開 第二次以上執行互動
void OnMouseClick(Vector2 mousePos)
{
    AbleToReveal();     //滑鼠點擊後先確定好允許翻開的格子
    for (int i = 0; i < TOTAL_CARDS; ++i)   
    {
        //如果這格被點到
        if (cards[i] && CheckCollisionPointRec(mousePos, cards[i]->bounds))
        {
            GridPos pos = GetCardGridPosition(cards[i]->bounds);

            //且是允許被翻開的格子
            if(abletoReveal[pos.row][pos.col]==1){
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

//死亡的怪物卡變為翻開狀態空卡
void ReplaceCardWithEmpty(int index) {
    float x = cards[index]->bounds.x;
    float y = cards[index]->bounds.y;
    free(cards[index]);  // 釋放原本的記憶體（EnemyCard）
    cards[index] = CreateEmptyCard(x, y, index);  // 換成空卡
    cards[index]->onReveal(cards[index]);
    cardTypes[index] = TYPE_EMPTY;  // 同步更新卡片類型
}

// 點擊過的道具卡變為翻開狀態空卡
void ReplaceItemCardWithEmpty(int index) {
    float x = cards[index]->bounds.x;
    float y = cards[index]->bounds.y;
    free(cards[index]);  // 釋放原本的記憶體（道具卡）

    // 替換為已翻開的空白卡
    cards[index] = CreateEmptyCard(x, y, index);
    cards[index]->onReveal(cards[index]);  // 自動將其設為已翻開
    cardTypes[index] = TYPE_EMPTY;  // 同步更新卡片類型
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