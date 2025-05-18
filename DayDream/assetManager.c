// assetManager.c
#include "assetManager.h"
#include <stdio.h>
#include <stdlib.h>

Texture2D textures[MAX_TEXTURES];
Texture2D seasonalItems[SEASON_COUNT][ITEM_TYPE_COUNT];
Season currentSeason = SEASON_SPRING; // defined here
Texture2D TEX_SHOP_ICON;

const char *seasonPrefix[SEASON_COUNT] = {"sp", "su", "au", "wi"};
const char *itemSuffix[ITEM_TYPE_COUNT] = {
    "_hp.png", "_mp.png", "_coin.png",
    "_t_scroll.png", "_aoe_scroll.png", "_sd_scroll.png",
    "_h_scroll.png", "_single_scroll.png"};

ItemType GetRandomItemType()
{
    float r = (float)rand() / RAND_MAX; // RAND_MAX defined in stdlib.h
    if (r < 0.25f)
        return ITEM_HP; // 25% for hp
    else if (r < 0.50f)
        return ITEM_MP; // 25%
    else if (r < 0.60f)
        return ITEM_COIN; // 10%
    else if (r < 0.68f)
        return SCROLL_TIME; // all the scrolls are 8% each
    else if (r < 0.76f)
        return SCROLL_AOE;
    else if (r < 0.84f)
        return SCROLL_SHIELD;
    else if (r < 0.92f)
        return SCROLL_HEAL;
    else
        return SCROLL_SINGLE;
}

void InitAssetManager() {
    // background image
    textures[TEXTURE_BG_SPRING] = LoadTexture("assets/scene/1.png");
    textures[TEXTURE_BG_SUMMER] = LoadTexture("assets/scene/2.png");
    textures[TEXTURE_BG_AUTUMN] = LoadTexture("assets/scene/3.png");
    textures[TEXTURE_BG_WINTER] = LoadTexture("assets/scene/4.png");

    // Door, Enemy, Key
    textures[TEXTURE_DOOR] = LoadTexture("assets/door.png");
    textures[TEXTURE_ENEMY] = LoadTexture("assets/monsters/enemy.png");
    textures[TEXTURE_KEY] = LoadTexture("assets/items/key.png");
    TEX_SHOP_ICON = LoadTexture("assets/shop.png");

    // 四季道具
    char path[128];
    for (int season = 0; season < SEASON_COUNT; season++) {
        for (int item = 0; item < ITEM_TYPE_COUNT; item++) {
            snprintf(path, sizeof(path), "assets/items/%s%s", seasonPrefix[season], itemSuffix[item]);
            seasonalItems[season][item] = LoadTexture(path);
        }
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
    UnloadTexture(TEX_SHOP_ICON);
}
