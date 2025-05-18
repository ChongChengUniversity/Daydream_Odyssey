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
   
// bool AttackEnemy(PlayerStats* player, EnemyStats* enemy) {
//     int damageToEnemy = CalculateDamage(player->atk, enemy->def);
//     int damageToPlayer = CalculateDamage(enemy->atk, player->def);

//     // 輸出主角血量、怪物血量
//     printf("Before attack: Player HP: %d, Enemy HP: %d\n", player->currentHp, enemy->currentHp);

//     ApplyDamageToPlayer(player, damageToPlayer);  // 更新主角血量
//     bool enemyDead = ApplyDamageToEnemy(enemy, damageToEnemy);  // 更新怪物血量

//     // 輸出攻擊後的數值
//     printf("After attack: Player HP: %d, Enemy HP: %d\n", player->currentHp, enemy->currentHp);

//     return enemyDead;  // 如果怪物死亡回傳 true
// }


// 怪物群增益處理（例如 buff 所有怪物 atk+1）
//void ApplyEnemyBuffs(CharacterStats* allEnemies[], int enemyCount);
//void bossAttack(CharacterStats* enemy, CharacterStats* player);