// assetManager.h
#pragma once
#include "raylib.h"

#define BACKGROUND_COUNT 3
#define CARD_IMAGE_COUNT 3
#define TEXTURE_BG_START 0
#define TEXTURE_CARD_START (TEXTURE_BG_START + BACKGROUND_COUNT)

#define TEXTURE_DOOR (TEXTURE_CARD_START + 0)
#define TEXTURE_ENEMY (TEXTURE_CARD_START + 1)

#define MAX_TEXTURES (BACKGROUND_COUNT + CARD_IMAGE_COUNT)

typedef enum {
    ITEM_HP,
    ITEM_MP,
    ITEM_COIN,
    SCROLL_TIME,
    SCROLL_AOE,
    SCROLL_SHIELD,
    SCROLL_HEAL,
    SCROLL_SINGLE,
    BOSS,
    ITEM_TYPE_COUNT,
} ItemType;

typedef enum {
    SEASON_SPRING, // 0
    SEASON_SUMMER, // 1
    SEASON_AUTUMN, // 2
    SEASON_WINTER, // 3
    SEASON_COUNT, // 4
} Season;

extern Season currentSeason;

extern Texture2D textures[MAX_TEXTURES];
extern Texture2D seasonalItems[SEASON_COUNT][ITEM_TYPE_COUNT];

void InitAssetManager();
void ShutdownAssetManager();
