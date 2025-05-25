// scrollManager.h
#pragma once
#include "raylib.h"
#include "EnemyStats.h"
#include "CardBase.h"

// 用前綴 SCROLL_TYPE_ 避免和 assetManager 的 SCROLL_ 衝突
typedef enum {
    SCROLL_TYPE_SINGLE,
    SCROLL_TYPE_AOE,
    SCROLL_TYPE_HEAL,
    SCROLL_TYPE_SHIELD,
    SCROLL_TYPE_TIME,
    SCROLL_TYPE_COUNT
} ScrollType;

typedef enum {
    MAGIC_SINGLE,
    MAGIC_AOE
} MagicAttackType;

int GetSingleTargetMagicDamage(int magicPower, int floor, MonsterType type);
int GetAOEMagicDamage(int magicPower, int floor);

void UseScrollEffect(ScrollType scroll, GridPos targetPos);