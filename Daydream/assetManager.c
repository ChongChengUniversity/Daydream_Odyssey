// assetManager.c
#include "assetManager.h"
#include <stdio.h>
#include <stdlib.h>

Texture2D textures[MAX_TEXTURES];   //Texture2D是存寬度高度等照片資料的結構體
Texture2D seasonalItems[SEASON_COUNT][ITEM_TYPE_COUNT];
Season currentSeason = SEASON_SPRING; // defined here
Texture2D TEX_SHOP_ICON;              // 商店圖

const char *seasonPrefix[SEASON_COUNT] = {"sp", "su", "au", "wi"};
const char *itemSuffix[ITEM_TYPE_COUNT] = {
    "_hp.png", "_mp.png", "_coin.png",
    "_t_scroll.png", "_aoe_scroll.png", "_shield_scroll.png",
    "_heal_scroll.png", "_single_scroll.png"};

//隨機決定格子中的物品種類
ItemType GetRandomItemType()
{
    float r = (float)rand() / RAND_MAX; // RAND_MAX defined in stdlib.h
    if (r < 0.20f)
        return ITEM_HP;
    else if (r < 0.40f)
        return ITEM_MP;
    else if (r < 0.55f)
        return ITEM_COIN;
    else if (r < 0.60f)
        return SCROLL_TIME;
    else if (r < 0.65f)
        return SCROLL_AOE;
    else if (r < 0.70f)
        return SCROLL_SHIELD;
    else if (r < 0.75f)
        return SCROLL_HEAL;
    else if (r < 0.80f)
        return SCROLL_SINGLE;
    else
        return BOSS;
}

//將所需圖片地址分類存入陣列方便後續使用
void InitAssetManager()
{
    for (int i = 0; i < BACKGROUND_COUNT; ++i)
    {
        char path[64];
        snprintf(path, sizeof(path), "assets/scene/%d.png", i + 1); // load season scene
        textures[TEXTURE_BG_START + i] = LoadTexture(path);
    }

    //分前後綴組成圖片地址 前綴季節種類後綴物品種類
    char path[128];
    for (int season = 0; season < SEASON_COUNT; season++)
    {
        for (int item = 0; item < ITEM_TYPE_COUNT; item++)
        {
            snprintf(path, sizeof(path), "assets/items/%s%s",
                     seasonPrefix[season], itemSuffix[item]);
            seasonalItems[season][item] = LoadTexture(path);
        }
    }

    textures[TEXTURE_DOOR] = LoadTexture("assets/door.png");
    textures[TEXTURE_ENEMY] = LoadTexture("assets/monsters/enemy.png");
    TEX_SHOP_ICON = LoadTexture("assets/shop.png");
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
    // 卸載商店圖像
    UnloadTexture(TEX_SHOP_ICON);
}
