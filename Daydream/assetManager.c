// assetManager.c
#include "assetManager.h"
#include <stdio.h>
#include <stdlib.h>

Texture2D textures[MAX_TEXTURES];
Texture2D seasonalItems[SEASON_COUNT][ITEM_TYPE_COUNT];
Season currentSeason = SEASON_SPRING; // defined here

const char *seasonPrefix[SEASON_COUNT] = {"sp", "su", "au", "wi"};
const char *itemSuffix[ITEM_TYPE_COUNT] = {
    "_hp.png", "_mp.png", "_coin.png",
    "_t_scroll.png", "_aoe_scroll.png", "_shield_scroll.png",
    "_heal_scroll.png", "_single_scroll.png"};

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

void InitAssetManager()
{
    for (int i = 0; i < BACKGROUND_COUNT; ++i)
    {
        char path[64];
        snprintf(path, sizeof(path), "assets/scene/%d.png", i + 1); // load season scene
        textures[TEXTURE_BG_START + i] = LoadTexture(path);
    }

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
}
