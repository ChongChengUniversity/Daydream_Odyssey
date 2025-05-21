//enemyManager.c
#include "enemyManager.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"
#include "EmptyCard.h"
#include "cardManager.h" 
#include "CardBase.h"
#include "levelManager.h"
#include "CharacterStats.h"

// 客製化每層怪物設定
FloorEnemyConfig floorConfigs[10];

// 初始化每層怪物設定
void InitFloorEnemyConfigs() {
    for (int i = 0; i < 10; ++i) {
        FloorEnemyConfig *cfg = &floorConfigs[i];
        cfg->visibleMin = 1;
        cfg->visibleMax = 2;
        cfg->hiddenMin = 2;
        cfg->hiddenMax = 4;

        if (i < 2) {
            cfg->allowSameTypeBuff = false;
            cfg->allowGlobalBuff = false;
        } else if (i < 6) {
            cfg->allowSameTypeBuff = true;
            cfg->maxSameTypeBuffEnemies = 2;
            cfg->allowGlobalBuff = true;
            cfg->maxGlobalBuffEnemies = 1;
        } else {
            cfg->allowSameTypeBuff = true;
            cfg->maxSameTypeBuffEnemies = 3;
            cfg->allowGlobalBuff = true;
            cfg->maxGlobalBuffEnemies = 1;
        }
    }
}

int gSameTypeBuffCount = 0;
int gGlobalBuffCount = 0;

//紀錄buff怪個別數量
void UpdateVisibleBufferCounts() {
    gSameTypeBuffCount = 0;
    gGlobalBuffCount = 0;

    for (int i = 0; i < TOTAL_CARDS; ++i) {
        if (cards[i]->type != TYPE_ENEMY) continue;

        GridPos pos = GetCardGridPosition(cards[i]->bounds);
        EnemyInfo* info = &enemyInfo[pos.row][pos.col];

        if (!cards[i]->isRevealed && !info->isVisible) continue;

        if (info->type == MONSTER_SAME_TYPE_BUFF) {
            gSameTypeBuffCount++;
        } else if (info->type == MONSTER_GLOBAL_BUFF) {
            gGlobalBuffCount++;
        }
    }
}

//實踐buff效果
void ApplyBuffsToVisibleEnemies() {
    for (int i = 0; i < TOTAL_CARDS; ++i) {
        if (cards[i]->type != TYPE_ENEMY) continue;

        GridPos pos = GetCardGridPosition(cards[i]->bounds);
        EnemyInfo* info = &enemyInfo[pos.row][pos.col];

        if (!info->isVisible && !cards[i]->isRevealed) continue;

        // 攻擊 buff：只有對 S_T_BUFF 類型的怪有效
        if (gSameTypeBuffCount >= 2 && info->type == MONSTER_SAME_TYPE_BUFF) {
            info->stats.bonusAtk = gSameTypeBuffCount * BUFF_ATK_PER_SAME_TYPE;
        } else {
            info->stats.bonusAtk = 0;
        }

        // 防禦 buff
        if (gGlobalBuffCount > 0) {
            info->stats.bonusDef = gGlobalBuffCount * BUFF_DEF_PER_GLOBAL;
        } else {
            info->stats.bonusDef = 0;
        }

        // 最終值統一更新
        info->stats.atk = info->stats.baseAtk + info->stats.bonusAtk;
        info->stats.def = info->stats.baseDef + info->stats.bonusDef;
    }
}

// 隨機選擇怪物類型
MonsterType GetRandomMonsterType(int floor, int sameTypeBuffCount, int globalBuffCount) {
    FloorEnemyConfig cfg = floorConfigs[floor];

    MonsterType candidates[3];
    int weights[3]; // 對應三種的權重
    int count = 0;

    // 永遠可以有普通怪
    candidates[count] = MONSTER_NORMAL;
    weights[count++] = 40;

    if (cfg.allowSameTypeBuff && sameTypeBuffCount < cfg.maxSameTypeBuffEnemies) {
        candidates[count] = MONSTER_SAME_TYPE_BUFF;
        weights[count++] = 30;
    }

    if (cfg.allowGlobalBuff && globalBuffCount < cfg.maxGlobalBuffEnemies) {
        candidates[count] = MONSTER_GLOBAL_BUFF;
        weights[count++] = 30;
    }

    // 計算加總後抽籤
    int totalWeight = 0;
    for (int i = 0; i < count; ++i) {
        totalWeight += weights[i];
    }

    int r = rand() % totalWeight;
    int acc = 0;

    for (int i = 0; i < count; ++i) {
        acc += weights[i];
        if (r < acc) {
            return candidates[i];
        }
    }

    return MONSTER_NORMAL; // 理論上不會到這裡
}
// MonsterType GetRandomMonsterType(int floor, int sameTypeBuffCount, int globalBuffCount) {
//     FloorEnemyConfig cfg = floorConfigs[floor];

//     bool allowSame = cfg.allowSameTypeBuff && (sameTypeBuffCount < cfg.maxSameTypeBuffEnemies);
//     bool allowGlobal = cfg.allowGlobalBuff && (globalBuffCount < cfg.maxGlobalBuffEnemies);

//     while (1) {
//         int r = rand() % 100;

//         if (r < 40) {
//             return MONSTER_NORMAL;
//         } else if (r < 75) {
//             if (allowSame) return MONSTER_SAME_TYPE_BUFF;
//         } else {
//             if (allowGlobal) return MONSTER_GLOBAL_BUFF;
//         }

//         // 若抽到不合法類型（已達上限），就重新抽
//         if (!allowSame && !allowGlobal) {
//             return MONSTER_NORMAL;
//         }
//     }
// }

EnemyInfo enemyInfo[ROWS][COLS];

// 初始化全部enemyInfo
void ResetEnemyInfo() {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            enemyInfo[row][col].isVisible = false;
            enemyInfo[row][col].isHidden = false;
            enemyInfo[row][col].type = -1;

            enemyInfo[row][col].stats.maxHp = 0;
            enemyInfo[row][col].stats.currentHp = 0;
            enemyInfo[row][col].stats.atk = 0;
            enemyInfo[row][col].stats.baseAtk = 0;
            enemyInfo[row][col].stats.bonusAtk = 0;
            enemyInfo[row][col].stats.def = 0;
            enemyInfo[row][col].stats.baseDef = 0;
            enemyInfo[row][col].stats.bonusDef = 0;
            enemyInfo[row][col].stats.isBuffer = false;
            enemyInfo[row][col].stats.type = -1;
        }
    }
}

// 洗牌用函式
void Shuffle(int *array, int count) {
    for (int i = count - 1; i > 0; --i) {
        int j = GetRandomValue(0, i);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// 根據卡片中的怪物決定哪些怪顯示
void UpdateEnemyVisibility() {
    ResetEnemyInfo();

    int currentFloor = GetCurrentLevel() - 1;

    // 根據目前層數讀取本層怪物設定
    FloorEnemyConfig config = floorConfigs[currentFloor];

    // 決定可視與不可視怪物數
    int visibleEnemies = GetRandomValue(config.visibleMin, config.visibleMax);
    int hiddenEnemies = GetRandomValue(config.hiddenMin, config.hiddenMax);

    // 紀錄所有 TYPE_ENEMY 的卡片 index
    int enemyIndices[TOTAL_CARDS];
    int enemyCount = 0;

    for (int i = 0; i < TOTAL_CARDS; ++i) {
        if (cards[i]->type == TYPE_ENEMY) {
            enemyIndices[enemyCount++] = i;
        }
    }

    // 避免超出實際怪物數量
    if (visibleEnemies > enemyCount) {
        visibleEnemies = enemyCount;
    }

    Shuffle(enemyIndices, enemyCount);

    // 設定可視怪物
    int sameTypeBuffCount = 0;
    int globalBuffCount = 0;

    for (int i = 0; i < visibleEnemies; ++i) {
        int index = enemyIndices[i];
        MonsterType monsterType = GetRandomMonsterType(currentFloor, sameTypeBuffCount, globalBuffCount);
        if (monsterType == MONSTER_SAME_TYPE_BUFF) {
            sameTypeBuffCount++;
        } else if (monsterType == MONSTER_GLOBAL_BUFF) {
            globalBuffCount++;
        }

        GridPos pos = GetCardGridPosition(cards[index]->bounds);
        EnemyInfo* enemy = &enemyInfo[pos.row][pos.col];

        enemy->isVisible = true;
        enemy->type = monsterType;
        GetBaseStatsByTypeAndFloor(monsterType, currentFloor, &enemy->stats);
    }

    // 設定不可視怪物
    for (int i = visibleEnemies; i < visibleEnemies + hiddenEnemies && i < enemyCount; ++i) {
        int index = enemyIndices[i];
        MonsterType monsterType = GetRandomMonsterType(currentFloor, sameTypeBuffCount, globalBuffCount);
        if (monsterType == MONSTER_SAME_TYPE_BUFF) {
            sameTypeBuffCount++;
        } else if (monsterType == MONSTER_GLOBAL_BUFF) {
            globalBuffCount++;
        }

        GridPos pos = GetCardGridPosition(cards[index]->bounds);
        EnemyInfo* enemy = &enemyInfo[pos.row][pos.col];

        enemy->isHidden = true;
        enemy->type = monsterType;
        GetBaseStatsByTypeAndFloor(monsterType, currentFloor, &enemy->stats);
    }

    // 剩餘的怪物卡轉為空卡
    for (int i = visibleEnemies + hiddenEnemies; i < enemyCount; ++i) {
        int index = enemyIndices[i];
        //不會翻開新轉成的空卡
        ReplaceCardWithEmpty(index, false);
    }
    AbleToReveal();
    UpdateVisibleBufferCounts();
    ApplyBuffsToVisibleEnemies();
}

// 初始化地圖與怪物資訊
void InitFloor() {
    InitFloorEnemyConfigs();
    UpdateEnemyVisibility();
}

// 查詢是否為可視怪物
bool IsEnemyVisibleAt(int row, int col) {
    return enemyInfo[row][col].isVisible;
}
