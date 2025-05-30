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
#define TEXTURE_PORTAL 7
#define TEXTURE_CHARACTER_HURT 8  
#define MAX_TEXTURES 9

#define ENEMY_TYPE_COUNT 4

#define EQUIP_TYPE_COUNT 46 


typedef enum {
    ITEM_HP,         // 0
    ITEM_MP,         // 1
    ITEM_COIN,       // 2
    SCROLL_TIME,     // 3
    SCROLL_AOE,      // 4
    SCROLL_SHIELD,   // 5
    SCROLL_HEAL,     // 6
    SCROLL_SINGLE,   // 7
    ITEM_TYPE_COUNT
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
extern Texture2D SOLD_OUT;
extern Texture2D LOCK;
extern Texture2D OPEN;
extern Texture2D equipmentImages[EQUIP_TYPE_COUNT];

void InitAssetManager();
void ShutdownAssetManager();
ItemType GetRandomItemType(void);

// 裝備說明卡
extern Texture2D EQUIP_INFO_CARD;
extern Texture2D CLOSE_BUTTON_IMG;
void LoadEquipAssets(void);
void UnloadEquipAssets(void);