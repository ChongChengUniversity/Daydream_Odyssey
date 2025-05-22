// scrollManager.c
#include "scrollManager.h"
#include <stdio.h>
#include "enemyManager.h"
#include "CardManager.h"
#include "CharacterStats.h"
#include "levelManager.h"

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

void UseScrollEffect(ScrollType scroll)
{
    switch (scroll) {
        case SCROLL_SINGLE: {
            printf("使用單體傷害卷軸\n");

            //這邊要補一個讀取被選中攻擊的怪物資訊的函式
            // EnemyStats* target = GetTargetedEnemy(); // 🔹你需要實作這個函式

            // if (target == NULL) {
            //     printf("錯誤：找不到目標怪物\n");
            //     break;
            // }

            PlayerStats* player = GetPlayerStats();
            int currentFloor = GetCurrentLevel();

            // int singledamage = GetSingleTargetMagicDamage(player->magic, currentFloor, target->type);
            // bool enemyDead = ApplyDamageToEnemy(target, singledamage);

            // if (enemyDead) {
            //     // ReplaceCardWithEmpty(target->indexInArray, true);
            //     AbleToReveal();
            //     UpdateVisibleBufferCounts();
            //     ApplyBuffsToVisibleEnemies();

            //     printf("怪物已被擊敗\n");
            // }
            break;
        }

        case SCROLL_AOE: {
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
                        AbleToReveal();
                        UpdateVisibleBufferCounts();
                        ApplyBuffsToVisibleEnemies();

                        printf("怪物已被擊敗\n");
                    }
                }
            }
            break;
        }

        case SCROLL_HEAL: {
            printf("使用補血卷軸\n");
            // TODO: 回復玩家生命
            break;
        }

        case SCROLL_SHIELD: {
            printf("使用護盾卷軸\n");
            // TODO: 增加防禦或護盾值
            break;
        }

        case SCROLL_TIME: {
            printf("使用時間停止卷軸\n");
            // TODO: 暫停敵人行動 N 回合
            break;
        }

        default: {
            printf("錯誤：未知卷軸類型\n");
            break;
        }
    }
}
