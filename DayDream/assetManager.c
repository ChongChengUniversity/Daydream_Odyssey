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
Texture2D SOLD_OUT;
Texture2D LOCK;
Texture2D OPEN;

Texture2D equipmentImages[EQUIP_TYPE_COUNT];  



// 當前季節（可供外部引用）
Season currentSeason = SEASON_SPRING;

// 四季前綴 物品圖片後綴
const char *seasonPrefix[SEASON_COUNT] = {"sp", "su", "au", "wi"};
const char *itemSuffix[ITEM_TYPE_COUNT] = {
    "_hp.png",             // ITEM_HP
    "_mp.png",             // ITEM_MP
    "_coin.png",           // ITEM_COIN
    "_t_scroll.png",       // SCROLL_TIME
    "_aoe_scroll.png",     // SCROLL_AOE
    "_sd_scroll.png",      // SCROLL_SHIELD ← ✅ 要注意這裡不是 "_shield_scroll.png"
    "_h_scroll.png",       // SCROLL_HEAL
    "_single_scroll.png"   // SCROLL_SINGLE
};


// 怪物圖片路徑
const char *enemyImagePaths[ENEMY_TYPE_COUNT] = {
    "assets/monsters/enemy.png",         // 普通怪
    "assets/monsters/buff_atk.png",      // 提升攻擊力
    "assets/monsters/buff_def.png",      // 提升防禦力
    "assets/monsters/boss.png"
};

ItemType GetRandomItemType()
{
    float r = (float)rand() / RAND_MAX;
    if (r < 0.20f)
        return ITEM_HP;       // 補血藥水 20%
    else if (r < 0.20f + 0.35f)
        return ITEM_COIN;     // 金幣 35%
    else if (r < 0.20f + 0.35f + 0.20f)
        return SCROLL_SINGLE; // 單體傷害卷軸 20%
    else if (r < 0.20f + 0.35f + 0.20f + 0.12f)
        return SCROLL_AOE;    // 群體傷害卷軸 12%
    else if (r < 0.20f + 0.35f + 0.20f + 0.12f + 0.08f)
        return SCROLL_HEAL;   // 補血卷軸 8%
    else
        return SCROLL_SHIELD; // 護盾卷軸 5%
}

void InitAssetManager() {
    // background image
    textures[TEXTURE_BG_SPRING] = LoadTexture("assets/scene/1.png");
    textures[TEXTURE_BG_SUMMER] = LoadTexture("assets/scene/2.png");
    textures[TEXTURE_BG_AUTUMN] = LoadTexture("assets/scene/3.png");
    textures[TEXTURE_BG_WINTER] = LoadTexture("assets/scene/4.png");

    // Door, Enemy, Key, character
    textures[TEXTURE_DOOR] = LoadTexture("assets/DOOR/door.png");
    textures[TEXTURE_KEY] = LoadTexture("assets/items/key.png");
    textures[TEXTURE_CHARACTER] = LoadTexture("assets/monsters/maincharacter.png");
    textures[TEXTURE_CHARACTER_HURT] = LoadTexture("assets/monsters/maincharacter_hurt.png");
    textures[TEXTURE_PORTAL] = LoadTexture("assets/portal.png");

    OPEN = LoadTexture("assets/DOOR/OPEN.png");
    // SHOP
    TEX_SHOP_ICON = LoadTexture("assets/shop/shop_icon.png");
    SOLD_OUT = LoadTexture("assets/shop/soldout.png");
    LOCK = LoadTexture("assets/shop/lock.png");

    
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

    // 裝備圖載入（9層 * 5件 = 45）
    int index = 0;
    for (int level = 1; level <= 9; ++level) {
        for (int slot = 1; slot <= 5; ++slot) {
            snprintf(path, sizeof(path), "assets/equipment/level%d/%d.png", level, slot);
            equipmentImages[index++] = LoadTexture(path);
        }
    }

    equipmentImages[45] = LoadTexture("assets/equipment/level10/1.png");
}


void ShutdownAssetManager() {
    for (int i = 0; i < MAX_TEXTURES; i++) {
        UnloadTexture(textures[i]);
    }

    for (int season = 0; season < SEASON_COUNT; season++) {
        for (int item = 0; item < ITEM_TYPE_COUNT; item++) {
            UnloadTexture(seasonalItems[season][item]);
        }
    }

    for (int i = 0; i < ENEMY_TYPE_COUNT; i++) {
        UnloadTexture(monsters[i]);
    }
    UnloadTexture(OPEN);
    UnloadTexture(TEX_SHOP_ICON);
    UnloadTexture(SOLD_OUT);
    UnloadTexture(LOCK);

    for (int i = 0; i < EQUIP_TYPE_COUNT; ++i) {
        UnloadTexture(equipmentImages[i]);
    }
}

// 裝備說明卡
Texture2D EQUIP_INFO_CARD;
Texture2D CLOSE_BUTTON_IMG;

void LoadEquipAssets(void) {
    EQUIP_INFO_CARD = LoadTexture("assets/infocard.png");
    CLOSE_BUTTON_IMG = LoadTexture("assets/closeinfo.png");
}

void UnloadEquipAssets(void) {
    UnloadTexture(EQUIP_INFO_CARD);
    UnloadTexture(CLOSE_BUTTON_IMG);
}