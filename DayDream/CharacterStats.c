//CharacterStats.c
#include "CharacterStats.h"
#include "levelManager.h" // 需要樓層倍率
#include <stdlib.h>
#include "stateController.h"
#include <stdio.h>
#include "equipmentSystem.h" // 取得裝備資料

static PlayerStats player;

//數值假定之後再考慮平衡
void InitPlayerStats() {
    // 初始化 base 數值
    player.basemaxHp = 1000;
    player.bonusMaxHp = 0;
    player.maxHp = player.basemaxHp;
    player.currentHp = 1000; // 測試用(之後可改成初始化為maxHP，如: player.currentHp = player.maxHp;)

    player.baseAtk = 10;
    player.bonusAtk = 0;
    player.atk = player.baseAtk; // 初始總 atk

    player.baseDef = 5;
    player.bonusDef = 0;
    player.def = player.baseDef; // 初始總 def

    player.baseMagic = 5; // 初始魔力數值可再調
    player.bonusMagic = 0;
    player.magic = player.baseMagic;

    player.currentBuff = BUFF_NONE;
    player.isHit = 0;
    player.hitTimer = 0;
}

PlayerStats* GetPlayerStats() {
    return &player;
}

/*
void ApplyEquipmentToPlayer(int bonusHp, int bonusAtk, int bonusDef) {
    player.maxHp += bonusHp;
    player.atk += bonusAtk;
    player.def += bonusDef;
}
*/

// 加上裝備後重新計算能力值
void RecalculatePlayerStats() {
    PlayerStats* player = GetPlayerStats();

    // 先重設為基礎值
    player->bonusAtk = 0;
    player->bonusDef = 0;
    player->bonusMaxHp = 0;
    player->bonusMagic = 0;

    // 掃描裝備欄，每一件裝備加成對應的欄位
    for (int i = 0; i < EQUIP_SLOT_COUNT; i++) {
        EquipmentData* eq = GetEquippedInSlot(i);
        if (eq) {
            player->bonusAtk += eq->atkPhysical;
            player->bonusDef += eq->defValue;
            player->bonusMaxHp += eq->maxHP;
            player->bonusMagic += eq->atkMagical;
        }
    }

    // 計算最終數值
    player->atk = player->baseAtk + player->bonusAtk;
    player->def = player->baseDef + player->bonusDef;
    player->maxHp = player->basemaxHp + player->bonusMaxHp;
    player->magic = player->baseMagic + player->bonusMagic;

    // 防止 currentHp 超過 maxHp
    if (player->currentHp > player->maxHp) {
        player->currentHp = player->maxHp;
    }
}

bool ApplyDamageToEnemy(EnemyStats* enemy, int damageToEnemy){
    if (enemy == NULL) return false;

    enemy->currentHp -= damageToEnemy;
    printf("對怪物造成 %d 傷害，剩餘 HP: %d\n", damageToEnemy, enemy->currentHp);

    if (enemy->currentHp <= 0) {
        enemy->currentHp = 0;  // 防止負數，死亡設為 0
        return true;
    }

    return false;
}

void ApplyDamageToPlayer(PlayerStats* player, int damageToPlayer){
    if(player->currentHp - damageToPlayer > 0){
        player->currentHp = player->currentHp - damageToPlayer;

        // 新增：觸發受攻擊效果
        player->isHit = true;
        player->hitTimer = 30;  // 顯示 0.5 秒 (30 幀)
    }
    else{
        GOTO(LOSE);
    }
}

void UpdatePlayer(PlayerStats* player) {
    if (player->isHit) {
        player->hitTimer--;
        if (player->hitTimer <= 0) {
            player->isHit = false;
        }
    }
}

void HealPlayer(int amount) {
    player.currentHp += amount;
    if (player.currentHp > player.maxHp) {
        player.currentHp = player.maxHp;
    }
}

void HealPlayerBySource(HealSource source) {
    int healAmount = 0;

    switch (source) {
        case HEAL_FROM_POTION:
            healAmount = 15 + 2 * GetCurrentLevel();
            printf("你喝下補血藥水，恢復了 %d 點 HP！\n", healAmount);
            break;

        case HEAL_FROM_SCROLL:
            // 預留邏輯，先不實作
            break;
    }

    HealPlayer(healAmount);
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



