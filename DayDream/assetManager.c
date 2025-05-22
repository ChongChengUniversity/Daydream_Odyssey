// assetManager.c
#include "assetManager.h"
#include <stdio.h>
#include <stdlib.h>

// 通用圖片：背景、門等
Texture2D textures[MAX_TEXTURES];

// 四季對應的物品圖片
Texture2D seasonalItems[SEASON_COUNT][ITEM_TYPE_COUNT];

// 怪物圖片陣列（普通、Buff ATK、Buff DEF）
Texture2D monsters[ENEMY_TYPE_COUNT];

Texture2D TEX_SHOP_ICON;

// 當前季節（可供外部引用）
Season currentSeason = SEASON_SPRING;

// 四季前綴 物品圖片後綴
const char *seasonPrefix[SEASON_COUNT] = {"sp", "su", "au", "wi"};
const char *itemSuffix[ITEM_TYPE_COUNT] = {
    "_hp.png", "_coin.png",
    "_t_scroll.png", "_aoe_scroll.png", "_sd_scroll.png",
    "_h_scroll.png", "_single_scroll.png"};

// 怪物圖片路徑
const char *enemyImagePaths[ENEMY_TYPE_COUNT] = {
    "assets/monsters/enemy.png",         // 普通怪
    "assets/monsters/buff_atk.png",      // 提升攻擊力
    "assets/monsters/buff_def.png"       // 提升防禦力
};

ItemType GetRandomItemType()
{
    float r = (float)rand() / RAND_MAX;
    if (r < 0.20f)
        return ITEM_HP;       // 補血藥水 20%
    else if (r < 0.20f + 0.15f)
        return ITEM_COIN;     // 金幣 15%
    else if (r < 0.20f + 0.15f + 0.25f)
        return SCROLL_SINGLE; // 單體傷害卷軸 25%
    else if (r < 0.20f + 0.15f + 0.25f + 0.15f)
        return SCROLL_AOE;    // 群體傷害卷軸 15%
    else if (r < 0.20f + 0.15f + 0.25f + 0.15f + 0.15f)
        return SCROLL_HEAL;   // 補血卷軸 15%
    else
        return SCROLL_SHIELD; // 護盾卷軸 10%

    // float r = (float)rand() / RAND_MAX; // RAND_MAX defined in stdlib.h
    // if (r < 0.25f)
    //     return ITEM_HP; // 25% for hp
    // else if (r < 0.50f)
    //     return ITEM_MP; // 25%
    // else if (r < 0.60f)
    //     return ITEM_COIN; // 10%
    // else if (r < 0.68f)
    //     return SCROLL_TIME; // all the scrolls are 8% each
    // else if (r < 0.76f)
    //     return SCROLL_AOE;
    // else if (r < 0.84f)
    //     return SCROLL_SHIELD;
    // else if (r < 0.92f)
    //     return SCROLL_HEAL;
    // else
    //     return SCROLL_SINGLE;
}

void InitAssetManager() {
    // background image
    textures[TEXTURE_BG_SPRING] = LoadTexture("assets/scene/1.png");
    textures[TEXTURE_BG_SUMMER] = LoadTexture("assets/scene/2.png");
    textures[TEXTURE_BG_AUTUMN] = LoadTexture("assets/scene/3.png");
    textures[TEXTURE_BG_WINTER] = LoadTexture("assets/scene/4.png");

    // Door, Enemy, Key, character
    textures[TEXTURE_DOOR] = LoadTexture("assets/door.png");
    textures[TEXTURE_KEY] = LoadTexture("assets/items/key.png");
    textures[TEXTURE_CHARACTER] = LoadTexture("assets/monsters/enemy111.png");
    TEX_SHOP_ICON = LoadTexture("assets/shop.png");

    // 四季道具
    char path[128];
    for (int season = 0; season < SEASON_COUNT; season++) {
        for (int item = 0; item < ITEM_TYPE_COUNT; item++) {
            snprintf(path, sizeof(path), "assets/items/%s%s", seasonPrefix[season], itemSuffix[item]);
            seasonalItems[season][item] = LoadTexture(path);
        }
    }
    // 載入怪物圖片
    for (int i = 0; i < ENEMY_TYPE_COUNT; i++)
    {
        monsters[i] = LoadTexture(enemyImagePaths[i]);
    }
}

void ShutdownAssetManager()
{
    for (int i = 0; i < MAX_TEXTURES; i++)
    {
        UnloadTexture(textures[i]);
    }
    for (int season = 0; season < SEASON_COUNT; season++)
    {
        for (int item = 0; item < ITEM_TYPE_COUNT; item++)
        {
            UnloadTexture(seasonalItems[season][item]);
        }
    }
    for (int i = 0; i < ENEMY_TYPE_COUNT; i++)
    {
        UnloadTexture(monsters[i]);
    }
    UnloadTexture(TEX_SHOP_ICON);
}
