//bossManager.h
#include "raylib.h"
#include "CardBase.h"

// 假設 BOSS 固定在地圖中央
#define BOSS_ROW 2
#define BOSS_COL 2

void InitBossState();
void KillBoss();
bool IsBossAlive();
int GetBossCD();
void UpdateBossAction();
CardBase* CreateBossCard(float x, float y, int index, int row, int col);
void DrawBoss(CardBase* self);
void OnInteractBoss(CardBase* self);