// characterStats.h
#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

#include <stdbool.h>
#include "EnemyStats.h"

typedef struct {
    int maxHp;
    int currentHp;
    int atk;
    int def;
} PlayerStats;

void InitPlayerStats();
bool ApplyDamageToEnemy(EnemyStats* enemy, int damage);
void ApplyDamageToPlayer(PlayerStats* player, int damageToPlayer);
void ApplyEquipmentToPlayer(int bonusHp, int bonusAtk, int bonusDef);
void HealPlayer(int amount);
PlayerStats* GetPlayerStats();
void GetBaseStatsByTypeAndFloor(MonsterType type, int floor, EnemyStats* outStats);

#endif // CHARACTER_STATS_H
