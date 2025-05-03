// levelManager.c
#include "levelManager.h"
#include "assetManager.h"

static int currentLevel = 1;
static const int totalLevels = 10;

void InitLevelManager() {
    currentSeason = SEASON_SPRING;
    currentLevel = 1;
}

void NextLevel() {
    if (currentLevel < totalLevels)
    {
        currentLevel++;

        if (currentLevel % 3 == 0 && currentSeason < SEASON_WINTER) // currentLevel++ first, so won't exist a situation that first level's currentSeason = 0(spring)
        {
            currentSeason++;
        }
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
