//bossManager.h
#include "raylib.h"
#include "CardBase.h"

void InitBossState();
void KillBoss();
bool IsBossAlive();
int GetBossCD();
void UpdateBossAction();
CardBase* CreateBossCard(float x, float y, int index, int row, int col);
void DrawBoss(CardBase* self);
void OnInteractBoss(CardBase* self);