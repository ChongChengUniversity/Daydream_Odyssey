#include <raylib.h>
#include <string.h>
#include "assetManager.h"
#include "itemSystem.h"

static ItemData items[ITEM_TYPE_COUNT];

void InitAllItems(void) {
    items[ITEM_HP] = (ItemData){
        .name = "HP Potion",
        .description = "Recover 50 HP",
        .price = 100,
        .hpRestore = 50,
        .isPurchased = 0,
    };

    items[ITEM_COIN] = (ItemData){
        .name = "Coin",
        .description = "Just a coin (not usable)",
        .price = 0,
        .isPurchased = 0,
    };

    items[SCROLL_TIME] = (ItemData){
        .name = "Time Scroll",
        .description = "Delay Boss CD by 5s",
        .price = 100,
        .time = 5,
        .isPurchased = 0,
    };

    items[SCROLL_AOE] = (ItemData){
        .name = "AOE Scroll",
        .description = "AOE +10 atk",
        .price = 100,
        .atkBoost = 10,
        .isPurchased = 0,
    };

    items[SCROLL_SHIELD] = (ItemData){
        .name = "Shield Scroll",
        .description = "Gain 10 shield",
        .price = 100,
        .shield = 10,
        .isPurchased = 0,
    };

    items[SCROLL_HEAL] = (ItemData){
        .name = "Heal Scroll",
        .description = "Recover 50 HP",
        .price = 100,
        .hpRestore = 50,
        .isPurchased = 0,
    };

    items[SCROLL_SINGLE] = (ItemData){
        .name = "Single Scroll",
        .description = "Single attack +10",
        .price = 100,
        .atkBoost = 10,
        .isPurchased = 0,
    };
}

ItemData* GetItemByType(ItemType type) {
    if (type >= 0 && type < ITEM_TYPE_COUNT) {
        return &items[type];
    }
    return NULL;
}

ItemData* GetItemByIndex(int index) {
    if (index >= 0 && index < ITEM_TYPE_COUNT) {
        return &items[index];
    }
    return NULL;
}


int GetTotalItems(void) {
    return ITEM_TYPE_COUNT;
}