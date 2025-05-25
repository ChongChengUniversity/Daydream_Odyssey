// scrollManager.c
#include "scrollManager.h"
#include <stdio.h>
#include "enemyManager.h"
#include "CardManager.h"
#include "CharacterStats.h"
#include "levelManager.h"
#include "itemUse.h"
#include "CardBase.h"

int GetSingleTargetMagicDamage(int magicPower, int floor, MonsterType type){
    float rawDamage;
    float multiplier = 1.0f;

    switch (type) {
        case MONSTER_NORMAL:
        case MONSTER_SAME_TYPE_BUFF:
            multiplier = 2.0f;
            break;
        case MONSTER_GLOBAL_BUFF:
            multiplier = 1.4f;
            break;
    }
    rawDamage = (magicPower + floor * 2) * multiplier;
    return (int)(rawDamage + 0.5f);
}

int GetAOEMagicDamage(int magicPower, int floor){
    float rawDamage;

    const float aoeMultiplier = 1.2f;
    rawDamage = (magicPower + floor * 2) * aoeMultiplier;

    return (int)(rawDamage + 0.5f);
}

void UseScrollEffect(ScrollType scroll, GridPos targetPos) {
    switch (scroll) {
        case SCROLL_TYPE_SINGLE: {
            printf("使用單體傷害卷軸\n");

            EnemyInfo* enemy = &enemyInfo[targetPos.row][targetPos.col];
            EnemyStats* targetStats = &enemy->stats;
            PlayerStats* player = GetPlayerStats();
            int currentFloor = GetCurrentLevel();
            int singleDamage = GetSingleTargetMagicDamage(player->magic, currentFloor, enemy->type);

            bool enemyDead = ApplyDamageToEnemy(targetStats, singleDamage);
            if (enemyDead) {
                int index = GetCardIndexByGridPos(targetPos.row, targetPos.col);
                ReplaceCardWithEmpty(index, true);
                printf("怪物已被擊敗\n");
            }
            AbleToReveal();
            UpdateVisibleBufferCounts();
            ApplyBuffsToVisibleEnemies();
            break;
        }

        case SCROLL_TYPE_AOE: {
            printf("使用群體傷害卷軸\n");

            PlayerStats* player = GetPlayerStats();
            int currentFloor = GetCurrentLevel();
            int aoeDamage = GetAOEMagicDamage(player->magic, currentFloor);

            for (int i = 0; i < TOTAL_CARDS; ++i) {
                if (cards[i]->type != TYPE_ENEMY) continue;

                int row = cards[i]->row;
                int col = cards[i]->col;
                EnemyInfo* enemyInfoPtr = &enemyInfo[row][col];
                EnemyStats* enemy = &enemyInfoPtr->stats;

                if (cards[i]->isRevealed || enemyInfo[row][col].isVisible) {
                    bool enemyDead = ApplyDamageToEnemy(enemy, aoeDamage);
                    if (enemyDead) {
                        ReplaceCardWithEmpty(cards[i]->indexInArray, true);
                        printf("怪物已被擊敗\n");
                    }
                    AbleToReveal();
                    UpdateVisibleBufferCounts();
                    ApplyBuffsToVisibleEnemies();
                }
            }
            break;
        }

        case SCROLL_TYPE_HEAL:
            printf("使用補血卷軸\n");
            // TODO: 回復玩家生命
            break;

        case SCROLL_TYPE_SHIELD:
            printf("使用護盾卷軸\n");
            // TODO: 增加防禦或護盾值
            break;

        case SCROLL_TYPE_TIME:
            printf("使用時間停止卷軸\n");
            // TODO: 暫停敵人行動 N 回合
            break;

        default:
            printf("錯誤：未知卷軸類型\n");
            break;
    }
}

