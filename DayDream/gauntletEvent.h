// gauntletEvent.h
#ifndef GAUNTLET_EVENT_H
#define GAUNTLET_EVENT_H

#include <stdbool.h>

// 在其他地方也要能讀取的變數（extern 宣告）
extern bool infinityGauntletAvailable;
extern float infinityGauntletScale;

// UI 顯示與按下手套圖示時的行為
void DrawInfinityGauntletIcon(void);

// // 每次 update 時呼叫，檢查是否要觸發手套事件（敵人打完 → 開始劇情 → 給手套）
// void CheckLevelProgress(void);

void GivePlayerInfinityGauntlet(void);

#endif // GAUNTLET_EVENT_H
