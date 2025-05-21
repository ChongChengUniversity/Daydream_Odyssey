//CharacterStats.c
#include "CharacterStats.h"
#include "levelManager.h" // 需要樓層倍率
#include <stdlib.h>
#include "stateController.h"
#include <stdio.h>

static PlayerStats player;

//數值假定之後再考慮平衡
void InitPlayerStats() {
    player.maxHp = 200;
    player.currentHp = 200;
    player.atk = 10;
    player.def = 5;
}

void ApplyEquipmentToPlayer(int bonusHp, int bonusAtk, int bonusDef) {
    player.maxHp += bonusHp;
    player.atk += bonusAtk;
    player.def += bonusDef;
}

PlayerStats* GetPlayerStats() {
    return &player;
}

bool ApplyDamageToEnemy(EnemyStats* enemy, int damageToEnemy){
    if(enemy->currentHp - damageToEnemy > 0){
        enemy->currentHp = enemy->currentHp - damageToEnemy;
        return false;
    }
    else{
        return true; //怪物死亡
    }
}

void ApplyDamageToPlayer(PlayerStats* player, int damageToPlayer){
    if(player->currentHp - damageToPlayer > 0){
        player->currentHp = player->currentHp - damageToPlayer;
    }
    else{
        GOTO(LOSE);
    }
}

void HealPlayer(int amount) {
    player.currentHp += amount;
    if (player.currentHp > player.maxHp) {
        player.currentHp = player.maxHp;
    }
}

void GetBaseStatsByTypeAndFloor(MonsterType type, int floor, EnemyStats* outStats) {
    // 初始化屬性
    outStats->bonusAtk = 0;
    outStats->bonusDef = 0;
    outStats->isBuffer = false;
    outStats->type = type;

    switch (type) {
        case MONSTER_NORMAL:
            outStats->maxHp = 10 + floor * 2;
            outStats->baseAtk = 5 + floor;
            outStats->baseDef = 2 + floor / 2;
            break;
        case MONSTER_SAME_TYPE_BUFF:
            outStats->maxHp = 12 + floor * 2;
            outStats->baseAtk = 6 + floor;
            outStats->baseDef = 3 + floor / 2;
            outStats->isBuffer = true;
            break;
        case MONSTER_GLOBAL_BUFF:
            outStats->maxHp = 15 + floor * 2;
            outStats->baseAtk = 7 + floor;
            outStats->baseDef = 4 + floor / 2;
            outStats->isBuffer = true;
            break;
        default:
            // 預設值（安全備援）
            outStats->maxHp = 10;
            outStats->baseAtk = 5;
            outStats->baseDef = 2;
            break;
    }

    // 統一計算 atk / def
    outStats->atk = outStats->baseAtk + outStats->bonusAtk;
    outStats->def = outStats->baseDef + outStats->bonusDef;

    // 設定初始血量
    outStats->currentHp = outStats->maxHp;
}


