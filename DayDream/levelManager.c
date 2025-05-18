// levelManager.c
#include "levelManager.h"
#include "assetManager.h"

static int currentLevel = 1;
static const int totalLevels = 10;
bool hasKey = false;

void AcquireKey() {
    hasKey = true;
}

bool HasKey() {
    return hasKey;
}

void InitLevelManager() {
    currentSeason = SEASON_SPRING;
    currentLevel = 1;
    hasKey = false;
}

void NextLevel() {
    if (currentLevel < totalLevels)
    {
        if (currentLevel % 3 == 0 && currentSeason <= SEASON_WINTER) // currentLevel++ first, so won't exist a situation that first level's currentSeason = 0(spring)
        {
            currentSeason++;
        }
        currentLevel++;
        hasKey = false; // reset hasKey in every level
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
