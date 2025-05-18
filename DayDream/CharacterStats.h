// CharacterStats.h
#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

#include <stdbool.h>

// 主角狀態
typedef struct {
    int maxHp;       // 最大血量
    int currentHp;   // 當前血量
    int atk;         // 攻擊力
    int def;         // 防禦力
} PlayerStats;

// 怪物狀態
typedef struct {
    int maxHp;
    int currentHp;
    int atk;
    int def;
    bool isBuffer; // 是否為提供增益的怪物
} EnemyStats;

// Player 相關操作
void InitPlayerStats();
bool ApplyDamageToEnemy(EnemyStats* enemy, int damageToEnemy);
void ApplyDamageToPlayer(PlayerStats* player, int damageToPlayer);
void ApplyEquipmentToPlayer(int bonusHp, int bonusAtk, int bonusDef);
void HealPlayer(int amount); // 補血功能
PlayerStats* GetPlayerStats();

// Enemy 生成
EnemyStats* CreateEnemyStats(int baseHp, int baseAtk, int baseDef, bool isBuffer);

#endif