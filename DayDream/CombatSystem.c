//CombatSystem.c
#include "CombatSystem.h"
#include "CharacterStats.h"
#include <stdio.h>

int CalculateDamage(int atk, int def){
    int damage;
    if(atk-def>0){
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
    //boss 攻擊機制另外算
    if (enemy->type != MONSTER_BOSS) {
        int damageToPlayer = CalculateDamage(enemy->atk, player->def);
        ApplyDamageToPlayer(player, damageToPlayer);
    }
    bool enemyDead = ApplyDamageToEnemy(enemy, damageToEnemy);
    return enemyDead;   //如果怪物死亡回傳ture
}