// enemyManager.h
#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "EnemyStats.h"
#include <stdbool.h>
#include "config.h"

#define BUFF_ATK_PER_SAME_TYPE 2  // 每多一隻 S_T_BUFF 怪，加 2 攻擊力
#define BUFF_DEF_PER_GLOBAL 1     // 每多一隻 G_BUFF 怪，加 1 防禦力

extern int gSameTypeBuffCount;
extern int gGlobalBuffCount;

typedef struct {
    MonsterType type;
    bool isVisible;
    bool isHidden;
    EnemyStats stats;
} EnemyInfo;

extern EnemyInfo enemyInfo[ROWS][COLS];

typedef struct {
    int visibleMin;
    int visibleMax;
    int hiddenMin;
    int hiddenMax;
    int maxSameTypeBuffEnemies;
    int maxGlobalBuffEnemies;
    bool allowSameTypeBuff;
    bool allowGlobalBuff;
} FloorEnemyConfig;

extern FloorEnemyConfig floorConfigs[10];

void InitFloorEnemyConfigs();
void InitFloor();
void UpdateEnemyVisibility();
bool IsEnemyVisibleAt(int row, int col);

void UpdateVisibleBufferCounts();
void ApplyBuffsToVisibleEnemies(); 

#endif // ENEMY_MANAGER_H
