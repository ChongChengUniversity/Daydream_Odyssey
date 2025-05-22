// item.c
#include "itemSystem.h"
#include <string.h>

static ItemData items[MAX_ITEMS];
static int itemCount = 0;

// 數值需修改
void InitAllItems(void) {
    itemCount = 0;

    // 0 血瓶
    items[itemCount++] = (ItemData){
        .name = "HP Potion",
        .description = "Recover 50 HP",
        .price = 100,
        .hpRestore = 50,
        .atkBoost = 0,
        .shield = 0,
        .time = 0,
        .isOwned = 0,
        .isUsed = 0
    };

    // 1 護盾卷軸
    items[itemCount++] = (ItemData){
        .name = "Shield Scroll",
        .description = "Reduce damage by 10",
        .price = 100,
        .hpRestore = 0,
        .atkBoost = 0,
        .shield = 10,
        .time = 0,
        .isOwned = 0,
        .isUsed = 0
    };

    // 2 時間卷軸
    items[itemCount++] = (ItemData){
        .name = "Time Scroll",
        .description = "Delay Boss CD by 5s",
        .price = 100,
        .hpRestore = 0,
        .atkBoost = 0,
        .shield = 0,
        .time = 5,
        .isOwned = 0,
        .isUsed = 0
    };

    // 3 Single attack卷軸
    items[itemCount++] = (ItemData){
        .name = "Single attack Scroll",
        .description = "Increase single target attack by 10",
        .price = 100,
        .hpRestore = 0,
        .atkBoost = 10,
        .shield = 0,
        .time = 0,
        .isOwned = 0,
        .isUsed = 0
    };

     // 4 AOE卷軸
     items[itemCount++] = (ItemData){
        .name = "AOE Scroll",
        .description = "Increase group attack by 10",
        .price = 100,
        .hpRestore = 0,
        .atkBoost = 10,
        .shield = 0,
        .time = 0,
        .isOwned = 0,
        .isUsed = 0
    };

    // 4 AOE卷軸
    items[itemCount++] = (ItemData){
        .name = "AOE Scroll",
        .description = "Increase group attack by 10",
        .price = 100,
        .hpRestore = 0,
        .atkBoost = 10,
        .shield = 0,
        .time = 0,
        .isOwned = 0,
        .isUsed = 0
    };

    // 5 治療卷軸
    items[itemCount++] = (ItemData){
        .name = "Heal Scroll",
        .description = "Recover 50 HP",
        .price = 100,
        .hpRestore = 50,
        .atkBoost = 0,
        .shield = 0,
        .time = 0,
        .isOwned = 0,
        .isUsed = 0
    };

    // 可繼續加入更多項目
}

ItemData* GetItemByIndex(int index) {
    if (index < 0 || index >= itemCount) return NULL;
    return &items[index];
}

int GetTotalItems(void) {
    return itemCount;
}
