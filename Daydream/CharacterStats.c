//CharacterStats.c
#include "CharacterStats.h"
#include "levelManager.h" // 需要樓層倍率
#include <stdlib.h>
#include "stateController.h"

static PlayerStats player;

//數值假定之後再考慮平衡
void InitPlayerStats() {
    player.maxHp = 10;
    player.currentHp = 10;
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

// EnemyStats CreateEnemyStats(int baseHp, int baseAtk, int baseDef, bool isBuffer) {
//     float multiplier = GetEnemyStatMultiplier();

//     EnemyStats enemy = {
//         .maxHp = (int)(baseHp * multiplier),
//         .currentHp = (int)(baseHp * multiplier),
//         .atk = (int)(baseAtk * multiplier),
//         .def = (int)(baseDef * multiplier),
//         .isBuffer = isBuffer
//     };
//     return enemy;
// }

EnemyStats* CreateEnemyStats(int baseHp, int baseAtk, int baseDef, bool isBuffer) {
    EnemyStats* enemy = malloc(sizeof(EnemyStats));  // 分配記憶體

    enemy->maxHp = baseHp;
    enemy->currentHp = baseHp;
    enemy->atk = baseAtk;
    enemy->def = baseDef;
    enemy->isBuffer = isBuffer;

    return enemy;
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
