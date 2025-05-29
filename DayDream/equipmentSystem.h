// equipmentSystem.h
#pragma once

#define MAX_EQUIPMENTS 46
#define EQUIP_SLOT_COUNT 5
#include "assetManager.h"  // 提供 Season 定義與 currentSeason

typedef enum {
    SLOT_HEAD,
    SLOT_BODY,
    SLOT_HAND,
    SLOT_FOOT,
    SLOT_ACCESSORY
} EquipSlot;

typedef struct {
    const char* name;         // 裝備名稱
    const char* description;  // 裝備說明
    int price;                // 裝備價格
    EquipSlot slot;           // 所屬裝備欄位
    int atkPhysical;          // 物理攻擊加成
    int atkMagical;           // 魔法攻擊加成
    int defValue;             // 防禦加成
    int maxHP;                // 最大 HP 上限加成
    int isEquipped;           // 是否裝備中
    int isPurchased;          // 是否已購買
    int locked;               //是否上鎖
    Season season;            // 所屬季節
    Texture2D* image;
} EquipmentData;

// 裝備初始化與管理函式
// 初始化所有裝備資料，清空裝備欄位、重建預設 20 件裝備（包含不同季節與部位）
void InitAllEquipments(void);

// 根據裝備索引（0 ~ MAX_EQUIPMENTS - 1）取得對應的裝備資料指標
EquipmentData* GetEquipmentByIndex(int index);

// 回傳目前系統中已初始化的裝備總數（通常最多為 20）
int GetTotalEquipments(void);

// 取得某個裝備欄位（如頭部、手部）目前裝備中的裝備資料
EquipmentData* GetEquippedInSlot(EquipSlot slot);

// 裝備指定 index 的裝備資料（會自動卸下該欄位原有裝備）
void EquipItem(int index);

// 卸下指定裝備欄位上的裝備（例如 SLOT_HEAD），若無裝備則無操作
void UnequipSlot(EquipSlot slot);

// 根據指定的季節與裝備欄位，自動尋找該季節適合的裝備
EquipmentData* GetEquipmentForSeason(Season season, EquipSlot slot);

void UnlockAllAccessorySlots(void);

void UnlockAllBootSlots(void);

// 顯示已購買的裝備圖示
void DrawEquippedItems(Rectangle screenRect);

// 清空所有裝備欄
void UnequipAllSlots(void);