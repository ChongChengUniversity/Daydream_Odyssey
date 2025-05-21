// EnemyCard.c
#include "EnemyCard.h"
#include "config.h"
#include <stdlib.h>
#include "stateController.h"
#include "assetManager.h"
#include "CombatSystem.h"
#include "CharacterStats.h"
#include "cardManager.h"
#include <stdio.h>
#include "CardBase.h"
#include "enemyManager.h"

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

// 重置卡片（例如重設關卡時）
static void ResetEnemy(CardBase* self) {
    self->isRevealed = false;
}

void DrawEnemy(CardBase* self) {
    if (self->isRevealed) {
        EnemyInfo* enemyInfoPtr = &enemyInfo[self->row][self->col];
        EnemyStats* enemy = &enemyInfoPtr->stats;

        // // 防呆檢查：怪物類型是否有效
        // if (enemy->type < 0 || enemy->type >= ENEMY_TYPE_COUNT) {
        //     printf("Invalid enemy type: %d\n", enemy->type);
        //     return;
        // }

        Rectangle bounds = self->bounds; // ✅ 提早定義 bounds，底色跟文字都會用

        // ✅ 根據 bonusAtk / bonusDef 加底色
        bool hasAtkBuff = enemy->bonusAtk > 0;
        bool hasDefBuff = enemy->bonusDef > 0;

        if (hasAtkBuff && hasDefBuff) {
            DrawRectangleRec(bounds, (Color){230, 200, 255, 255}); // 淺紫
        } else if (hasAtkBuff) {
            DrawRectangleRec(bounds, (Color){255, 200, 200, 255}); // 淺紅
        } else if (hasDefBuff) {
            DrawRectangleRec(bounds, (Color){200, 200, 255, 255}); // 淺藍
        }

        // 使用 monsters 陣列依照類型選圖
        DrawTextureEx(monsters[enemy->type], 
            (Vector2){ self->bounds.x, self->bounds.y },
            0.0f,
            (float)TILE_SIZE / monsters[enemy->type].width,
            WHITE);

        int fontSize = 16;
        // 左上角：攻擊力（黃色）
        DrawBoldText(TextFormat("%d", enemy->atk), bounds.x + 2, bounds.y + 2, fontSize, YELLOW);
        // 左下角：血量（紅色）
        DrawBoldText(TextFormat("%d", enemy->currentHp), bounds.x + 2, bounds.y + bounds.height - fontSize - 2, fontSize, RED);
        // 右下角：防禦力（黃色）
        DrawBoldText(TextFormat("%d", enemy->def),bounds.x + bounds.width - fontSize - 2,bounds.y + bounds.height - fontSize - 2,fontSize, YELLOW);
    } else {
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE); // 未翻開時只畫邊框
    }
}


// 當翻開卡片時
static void OnRevealEnemy(CardBase* self) {
    self->isRevealed = true;
}

// 當與卡片互動時（點擊怪物）
static void OnInteractEnemy(CardBase* self) {
    PlayerStats* player = GetPlayerStats();
    EnemyInfo* enemyInfoPtr = &enemyInfo[self->row][self->col];
    EnemyStats* enemy = &enemyInfoPtr->stats;

    bool enemyDead = AttackEnemy(player, enemy);
    if (enemyDead) {
        //會翻開新轉成的空卡
        ReplaceCardWithEmpty(self->indexInArray, true);
        AbleToReveal();
        UpdateVisibleBufferCounts();
        ApplyBuffsToVisibleEnemies();
    }
}

CardBase* CreateEnemyCard(float x, float y, int index, int row, int col)
{
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL;

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = false;
    card->reset = ResetEnemy;
    card->draw = DrawEnemy;
    card->onReveal = OnRevealEnemy;
    card->onInteract = OnInteractEnemy;
    card->indexInArray = index;
    card->row = row;
    card->col = col;

    // 預設敵人資料（真正用 enemyInfo[row][col] 儲存）
    card->data = NULL;
    card->type = TYPE_ENEMY;
    return card;
}