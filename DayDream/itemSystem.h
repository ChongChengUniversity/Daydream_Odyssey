// itemSystem.h
#pragma once

#include <raylib.h>         // ✅ 放最上面
#include "assetManager.h"   // ✅ 若有用到季節或圖片陣列

#define INVENTORY_SIZE 20
#define EQUIP_SIZE 10

typedef struct {
    const char* name;       // 道具名稱
    const char* description;// 道具說明
    int price;              // 價格
    int hpRestore;          // 回復 HP 數值
    int atkBoost;           // 攻擊加成
    int time;               // 時間加成 
    int shield;             // 護盾值
    int isOwned;            // 是否已擁有（0 = 沒有, 1 = 擁有）
    int isPurchased;          // 是否已購買
    int isUsed;             // 是否已使用（0 = 未使用, 1 = 已使用）
} ItemData;

void InitAllItems(void);
ItemData* GetItemByType(ItemType type);
ItemData* GetItemByIndex(int index);  // ✅ 補上這一行

int GetTotalItems(void);

