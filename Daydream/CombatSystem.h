// CombatSystem.h
#include <stdbool.h>
#include "CharacterStats.h"

int CalculateDamage(int atk, int def);
bool AttackEnemy(PlayerStats* player, EnemyStats* enemy);