// levelManager.h
#pragma once

#include<stdbool.h>

/// 初始化關卡狀態（例如重新開始遊戲）
void InitLevelManager();

/// 進入下一關（如果還有下一關）
void NextLevel();

/// 取得目前的關卡（1~4）
int GetCurrentLevel();

/// 取得總關卡數
int GetTotalLevels();

bool IsFinalLevel();
