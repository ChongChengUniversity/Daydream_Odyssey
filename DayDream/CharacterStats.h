// characterStats.h
#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

#include <stdbool.h>
#include "EnemyStats.h"

typedef enum {
    BUFF_NONE,
    BUFF_SHIELD
} BuffType;

typedef struct {
    int atk;
    int baseAtk;
    int bonusAtk;

    int def;
    int baseDef;
    int bonusDef;

    int maxHp;
    int basemaxHp;
    int bonusMaxHp;
    int currentHp;

    int magic;  // 魔力
    int baseMagic;   // 基礎魔力值
    int bonusMagic;  // 裝備提供的魔力加成

    BuffType currentBuff;
    bool isHit;         // 是否剛被打中
    int hitTimer;       // 受攻擊顯示計時器（單位：幀）
} PlayerStats;

typedef enum {
    HEAL_FROM_POTION,
    HEAL_FROM_SCROLL
} HealSource;

void InitPlayerStats();
bool ApplyDamageToEnemy(EnemyStats* enemy, int damage);
void ApplyDamageToPlayer(PlayerStats* player, int damageToPlayer);
void UpdatePlayer(PlayerStats* player);

//void ApplyEquipmentToPlayer(int bonusHp, int bonusAtk, int bonusDef);
// 上面的function改成底下這個(加上裝備後重新計算能力值)
void RecalculatePlayerStats();
void HealPlayerBySource(HealSource source);

PlayerStats* GetPlayerStats();
void GetBaseStatsByTypeAndFloor(MonsterType type, int floor, EnemyStats* outStats);

#endif // CHARACTER_STATS_H
