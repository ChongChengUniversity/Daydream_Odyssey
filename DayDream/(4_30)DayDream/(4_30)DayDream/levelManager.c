// levelManager.c
#include "levelManager.h"

static int currentLevel = 1;
static const int totalLevels = 4;

void InitLevelManager() {
    currentLevel = 1;
}

void NextLevel() {
    if (currentLevel < totalLevels) {
        currentLevel++;
    }
}

int GetCurrentLevel() {
    return currentLevel;
}

int GetTotalLevels() {
    return totalLevels;
}

bool IsFinalLevel() {
    return currentLevel == totalLevels;
}
