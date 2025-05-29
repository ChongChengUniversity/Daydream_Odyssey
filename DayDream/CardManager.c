// CardManager.c
#include "CardManager.h"
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
#include "CharacterStats.h"
#include "enemyManager.h"
#include "levelManager.h"
#include "KeyCard.h"
#include "bossManager.h"
#include <stdio.h>


CardBase *cards[TOTAL_CARDS];

CardType cardTypes[TOTAL_CARDS];

// Control how each cards should appear, giving out index
void InitCardTypes()
{
    int index = 0;
    cardTypes[index++] = TYPE_DOOR; // only one
    for (int i = 0; i < 12; ++i)
        cardTypes[index++] = TYPE_ITEM;
    for (int i = 0; i < 6; ++i)
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

            //第十關boss位置(可更改)
            if (GetCurrentLevel() == 10 && row == 2 && col == 2) {
                cards[card_index] = CreateBossCard(x, y, card_index, row, col);
                card_index++;
                continue; // 避免重複插卡
            }
            
            switch (cardTypes[card_index])
            {
            case TYPE_DOOR:
                cards[card_index] = CreateDoorCard(x, y, card_index, row, col);
                indexdoorRow = row;  // 紀錄門的格子位置
                indexdoorCol = col;
                break;

            case TYPE_ITEM:
                cards[card_index] = CreateItemCard(x, y, card_index, row, col, GetRandomItemType());
                break;

            case TYPE_ENEMY:
                cards[card_index] = CreateEnemyCard(x, y, card_index, row, col);
                break;

            case TYPE_EMPTY:
                cards[card_index] = CreateEmptyCard(x, y, card_index, row, col);
                break;

            case TYPE_KEY:
                cards[card_index] = CreateKeyCard(x, y, card_index, row, col);
                printf("Key found at: Row %d, Col %d, Index %d\n", cards[card_index]->row, cards[card_index]->col, card_index);
                break;
            }
            
            card_index++;
        }
    }     
}

// 控制哪些格子允許被翻開
int abletoReveal[ROWS][COLS] = {0}; 

//該格是不可視已翻開還活著的怪物
bool IsRevealedInvisibleEnemy(int row, int col) {
    CardBase* card = GetCardAt(row, col);
    return card &&
           card->type == TYPE_ENEMY &&  // 確保還是怪物卡
           enemyInfo[row][col].isHidden &&
           card->isRevealed;
}

//檢查我們所在這格周圍四格是否有會封鎖周邊的不可視已翻開還活著的怪物
bool IsBlockedByEnemy(int row, int col) {
    if (row > 0 && IsRevealedInvisibleEnemy(row - 1, col)) return true;
    if (row < ROWS - 1 && IsRevealedInvisibleEnemy(row + 1, col)) return true;
    if (col > 0 && IsRevealedInvisibleEnemy(row, col - 1)) return true;
    if (col < COLS - 1 && IsRevealedInvisibleEnemy(row, col + 1)) return true;

    return false;
}

//每次掃描全部格子紀錄允許翻開的卡片
void AbleToReveal() {
    // 步驟 1：預設所有格子不可翻開
    memset(abletoReveal, 0, sizeof(abletoReveal));

    // 步驟 2：所有已翻開格子四周變成「可以嘗試翻開」
    for (int i = 0; i < TOTAL_CARDS; ++i) {
        CardBase* card = cards[i];
        if (!card || !card->isRevealed) continue;

        int row = card->row;
        int col = card->col;

        if (row > 0) abletoReveal[row - 1][col] = 1;
        if (row < ROWS - 1) abletoReveal[row + 1][col] = 1;
        if (col > 0) abletoReveal[row][col - 1] = 1;
        if (col < COLS - 1) abletoReveal[row][col + 1] = 1;
    }

    // 步驟 3：如果某格本來是允許，但它的上下左右有「封鎖怪」，則把它封掉
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (!abletoReveal[row][col]) continue;

            if (IsBlockedByEnemy(row, col)) {
                abletoReveal[row][col] = 0; // 取消允許翻開
            }
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

//判斷該格是否為怪物
bool IsEnemyCardAt(int row, int col) {
    CardBase* card = GetCardAt(row, col); 
    return card && card->type == TYPE_ENEMY;
}

// 畫出粗體字（加黑邊）
static void DrawBoldText(const char* text, int posX, int posY, int fontSize, Color color) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx != 0 || dy != 0) {
                DrawText(text, posX + dx, posY + dy, fontSize, BLACK); // 黑邊
            }
        }
    }
    DrawText(text, posX, posY, fontSize, color); // 主文字
}

void DrawAllCards() {
    for (int i = 0; i < TOTAL_CARDS; ++i) {
        if (!cards[i]) continue;

        int row = cards[i]->row;
        int col = cards[i]->col;
        bool canReveal = abletoReveal[row][col];
        bool isEnemy = IsEnemyCardAt(row, col);
        bool isVisible = false;
        EnemyInfo* enemy = NULL;

        int type = -1; // 預設-1代表沒有怪物類型
        if (isEnemy) {
            enemy = &enemyInfo[row][col];
            type = enemy->type;
            isVisible = enemy->isVisible;

            // // 防呆：怪物類型範圍檢查
            // if (type < 0 || type >= 3) {
            //     printf("Warning: Invalid monster type %d at (%d,%d)\n", type, row, col);
            //     type = -1;  // 設為無效，避免畫錯圖
            // }
        }

        if (cards[i]->isRevealed) {
            cards[i]->draw(cards[i]);
        }
        else if (isEnemy && isVisible) {
            if (enemy && type >= 0) {
                Rectangle bounds = cards[i]->bounds;

                // ✅ 根據 bonusAtk / bonusDef 加底色
                bool hasAtkBuff = enemy->stats.bonusAtk > 0;
                bool hasDefBuff = enemy->stats.bonusDef > 0;

                if (hasAtkBuff && hasDefBuff) {
                    DrawRectangleRec(bounds, (Color){230, 200, 255, 255}); // 淺紫
                } else if (hasAtkBuff) {
                    DrawRectangleRec(bounds, (Color){255, 200, 200, 255}); // 淺紅
                } else if (hasDefBuff) {
                    DrawRectangleRec(bounds, (Color){200, 200, 255, 255}); // 淺藍
                }

                // ✅ 畫怪物圖片（蓋在底色上）
                DrawTextureEx(monsters[type],
                            (Vector2){bounds.x, bounds.y},
                            0.0f,
                            (float)TILE_SIZE / monsters[type].width,
                            WHITE);

                // ✅ 畫數值
                if (CheckCollisionPointRec(GetMousePosition(), cards[i]->bounds)){
                    int fontSize = 16;
                    DrawBoldText(TextFormat("%d", enemy->stats.atk), bounds.x + 2, bounds.y + 2, fontSize, YELLOW); // 攻擊
                    DrawBoldText(TextFormat("%d", enemy->stats.currentHp), bounds.x + 2, bounds.y + bounds.height - fontSize - 2, fontSize, RED); // 血量
                    DrawBoldText(TextFormat("%d", enemy->stats.def), bounds.x + bounds.width - fontSize - 2, bounds.y + bounds.height - fontSize - 2, fontSize, YELLOW); // 防禦
                }
            }
            // else {
            //     // 畫一個紅框提醒，表示怪物類型錯誤
            //     DrawRectangleLinesEx(cards[i]->bounds, 2.0f, PINK);
            // }
            // DrawRectangleLinesEx(cards[i]->bounds, 2.0f, GREEN);
        }
        else if (canReveal) {
            DrawRectangleRec(cards[i]->bounds, BLUE);
        }
        else {
            cards[i]->draw(cards[i]);
        }

        if (IsBlockedByEnemy(row, col) && !cards[i]->isRevealed && !isVisible) {
            DrawRectangleLinesEx(cards[i]->bounds, 2.0f, RED);
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
        if (cards[i] && CheckCollisionPointRec(mousePos, cards[i]->bounds)) {
            int row = cards[i]->row, col = cards[i]->col;
            bool isEnemy = IsEnemyCardAt(row, col);
            bool isVisible = false;

            if (isEnemy) {
                isVisible = enemyInfo[row][col].isVisible;
            }

            if (abletoReveal[row][col] == 1) {
                // 合法可以互動的格子
                if (isEnemy && isVisible) {
                    // 可視敵人 → 可攻擊
                    if (cards[i]->onInteract) {
                        cards[i]->onInteract(cards[i]);
                    }
                }
                else if (!cards[i]->isRevealed) {
                    // 一般未翻開卡 → 翻開
                    if (cards[i]->onReveal) {
                        cards[i]->onReveal(cards[i]);
                    }
                }
                else {
                    // 其他可互動卡片
                    if (cards[i]->onInteract) {
                        cards[i]->onInteract(cards[i]);
                    }
                }
            }
            else {
                // 不在允許翻開區域，但是「已翻開」或是「不可視怪物」的特例仍允許互動
                if (cards[i]->isRevealed && cards[i]->onInteract ||
                    IsBlockedByEnemy(row, col) && isVisible) {
                    cards[i]->onInteract(cards[i]);
                }
            }

            // 更新 buff 狀態
            UpdateVisibleBufferCounts();
            ApplyBuffsToVisibleEnemies();
        }

    }
}

//死亡的怪物卡變為翻開狀態空卡(不能在這邊就主動把空卡打開)
void ReplaceCardWithEmpty(int index, bool shouldReveal) {
    float x = cards[index]->bounds.x;
    float y = cards[index]->bounds.y;
    int row = cards[index]->row;
    int col = cards[index]->col;

    SafeDestroyCard(&cards[index]);
    cards[index] = CreateEmptyCard(x, y, index, row, col);  // 換成空卡

    if (shouldReveal) {
        cards[index]->onReveal(cards[index]);  // 只有需要時才觸發翻開
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

void DestroyCard(CardBase* card) {
    if (!card) return;

    switch (card->type) {
        case TYPE_ENEMY:
            if (card->data != NULL) {
                free(card->data);
                card->data = NULL;
            }
            break;
        default:
            break;
    }

    free(card);
}

// 修改呼叫端範例
void SafeDestroyCard(CardBase** pCard) {
    if (pCard == NULL || *pCard == NULL) return;
    DestroyCard(*pCard);
    *pCard = NULL;  // 釋放後將指標設 NULL，避免野指標
}

GridPos GetClickedGrid(Vector2 mousePos) {
    for (int i = 0; i < TOTAL_CARDS; i++) {
        if (cards[i] && CheckCollisionPointRec(mousePos, cards[i]->bounds)) {
            return (GridPos){ cards[i]->row, cards[i]->col };
        }
    }
    return (GridPos){ -1, -1 }; // 沒有點到任何卡片
}