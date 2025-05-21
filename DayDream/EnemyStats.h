// EnemyStats.h
#ifndef ENEMY_STATS_H
#define ENEMY_STATS_H

#include <stdbool.h>

typedef enum {
    MONSTER_NORMAL,
    MONSTER_SAME_TYPE_BUFF,
    MONSTER_GLOBAL_BUFF,
    // MONSTER_BOSS
} MonsterType;

typedef struct EnemyStats {
    int maxHp;
    int currentHp;
    int atk;
    int baseAtk;
    int bonusAtk;

    int def;
    int baseDef;
    int bonusDef;

    bool isBuffer;
    MonsterType type;
} EnemyStats;

#endif // ENEMY_STATS_H
