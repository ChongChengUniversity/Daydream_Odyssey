// scrollManager.h
#pragma once
#include "raylib.h"
#include "EnemyStats.h"

typedef enum {
    SCROLL_SINGLE,
    SCROLL_AOE,
    SCROLL_HEAL,
    SCROLL_SHIELD,
    SCROLL_TIME,
    SCROLL_TYPE_COUNT  // ✨作為總數，不會重複定義，維護方便
} ScrollType;

typedef enum {
    MAGIC_SINGLE,
    MAGIC_AOE
} MagicAttackType;

int GetSingleTargetMagicDamage(int magicPower, int floor, MonsterType type);
int GetAOEMagicDamage(int magicPower, int floor);

void UseScrollEffect(ScrollType scroll);