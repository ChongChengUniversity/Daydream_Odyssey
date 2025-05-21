//CombatSystem.c
#include "CombatSystem.h"
#include "CharacterStats.h"
#include <stdio.h>

int CalculateDamage(int atk, int def){
    int damage;
    if(atk - def>0){
        damage = atk - def;
        return damage;
    }
    else{
        return 1;
    }
}

//物攻
bool AttackEnemy(PlayerStats* player, EnemyStats* enemy) {
    int damageToEnemy = CalculateDamage(player->atk, enemy->def);
    int damageToPlayer = CalculateDamage(enemy->atk, player->def);

    ApplyDamageToPlayer(player, damageToPlayer);
    bool enemyDead = ApplyDamageToEnemy(enemy, damageToEnemy);
    return enemyDead;   //如果怪物死亡回傳ture
}

// 怪物群增益處理（例如 buff 所有怪物 atk+1）
//void ApplyEnemyBuffs(CharacterStats* allEnemies[], int enemyCount);
//void bossAttack(CharacterStats* enemy, CharacterStats* player);