// levelManager.h
#pragma once
#include<stdbool.h>

void InitLevelManager();
void NextLevel();
int GetCurrentLevel();
int GetTotalLevels();
bool IsFinalLevel();

void AcquireKey();
bool HasKey();
