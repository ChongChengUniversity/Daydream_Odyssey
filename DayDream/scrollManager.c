// scrollManager.c
#include "scrollManager.h"
#include <stdio.h>
#include "enemyManager.h"
#include "CardManager.h"
#include "CharacterStats.h"
#include "levelManager.h"
#include "itemUse.h"
#include "CardBase.h"
#include "money.h"
#define MESSAGE_DURATION 90

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

bool UseScrollEffect(ScrollType scroll, GridPos targetPos) {
    switch (scroll) {
        case SCROLL_TYPE_SINGLE: {
            printf("Use single target damage scroll\n");

            EnemyInfo* enemy = &enemyInfo[targetPos.row][targetPos.col];
            EnemyStats* targetStats = &enemy->stats;
            PlayerStats* player = GetPlayerStats();
            int currentFloor = GetCurrentLevel();
            int singleDamage = GetSingleTargetMagicDamage(player->magic, currentFloor, enemy->type);

            bool enemyDead = ApplyDamageToEnemy(targetStats, singleDamage);
            if (enemyDead) {
                int index = GetCardIndexByGridPos(targetPos.row, targetPos.col);
                ReplaceCardWithEmpty(index, true);
                printf("Enemy defeated\n");
            }
            AbleToReveal();
            UpdateVisibleBufferCounts();
            ApplyBuffsToVisibleEnemies();
            return true;
        }

        case SCROLL_TYPE_AOE: {
            printf("Use AOE damage scroll\n");

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
                        printf("Enemy defeated\n");
                    }
                    AbleToReveal();
                    UpdateVisibleBufferCounts();
                    ApplyBuffsToVisibleEnemies();
                }
            }
            return true;
        }

        case SCROLL_TYPE_HEAL:
            PlayerStats* player = GetPlayerStats();
            printf("[Scroll] Healing scroll used\n");
            int healAmount = 50; // Heal 50 HP
            player->currentHp += healAmount;
            if (player->currentHp > player->maxHp) {
                player->currentHp = player->maxHp;
            }
            return true;

        case SCROLL_TYPE_SHIELD: {
            printf("Use shield scroll\n");
            PlayerStats* player = GetPlayerStats();
            if (player->bonusDef >= 10) {
                printf("Shield already active\n");
                SetMessage("Shield already active");
                return false;  //  失敗，已經有護盾了
            }else{
                player->bonusDef = 10; // 加護盾
                printf("Shield applied successfully\n");
                return true;  //  成功
            }
        }

        case SCROLL_TYPE_TIME:
            printf("Use time-stop scroll\n");
            return true;

        default:
            printf("Error: Unknown scroll type\n");
            return false;
    }
}


