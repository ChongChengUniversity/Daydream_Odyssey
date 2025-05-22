// assetManager.h
#pragma once
#include "raylib.h"

#define TEXTURE_BG_SPRING 0
#define TEXTURE_BG_SUMMER 1
#define TEXTURE_BG_AUTUMN 2
#define TEXTURE_BG_WINTER 3

#define TEXTURE_DOOR 4
#define TEXTURE_CHARACTER 5
#define TEXTURE_KEY 6
#define MAX_TEXTURES 7

#define ENEMY_TYPE_COUNT 3

typedef enum {
    ITEM_HP,
    ITEM_COIN,
    SCROLL_TIME,
    SCROLL_AOE,
    SCROLL_SHIELD,
    SCROLL_HEAL,
    SCROLL_SINGLE,
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
extern Texture2D monsters[ENEMY_TYPE_COUNT];
extern Texture2D TEX_SHOP_ICON;

void InitAssetManager();
void ShutdownAssetManager();
ItemType GetRandomItemType(void);
