//equipmentSystem.c

#include "equipmentSystem.h"
#include <string.h> // 若未使用 strcpy 等功能可省略

// === 全域變數 ===

// 儲存所有裝備的資料，最多 MAX_EQUIPMENTS 件（20 件）
static EquipmentData equipmentList[MAX_EQUIPMENTS];

// 當前裝備數量
static int equipmentCount = 0;

// 紀錄每個欄位目前裝備的裝備 index（未裝備則為 -1）
static int equippedIndices[EQUIP_SLOT_COUNT];



// 初始化所有裝備資料
// - 清除已裝備狀態
// - 載入預設裝備資料（46 件，含四季與五欄位）
void InitAllEquipments(void) {
    equipmentCount = 0;

    // 所有裝備欄位預設為未裝備（-1）
    for (int i = 0; i < EQUIP_SLOT_COUNT; i++) {
        equippedIndices[i] = -1;
    }

    // 數值暫定
    // 第一層
    // 0 頭
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Vine Circlet",
        .description = "Head.",
        .price = 1,
        .slot = SLOT_HEAD,
        .atkPhysical = 5,
        .atkMagical = 10,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SPRING,
        .image = &equipmentImages[0]
    };

    // 1 身體
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Beast Skin Cloak",
        .description = "Body.",
        .price = 1,
        .slot = SLOT_BODY,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 10,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SPRING,
        .image = &equipmentImages[1]
    };

    // 2 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Beast Bone Saber",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SPRING,
        .image = &equipmentImages[2]
    };

    // 3 首飾
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Fang Necklace",
        .description = "Accessory.",
        .price = 1,
        .slot = SLOT_ACCESSORY,
        .atkPhysical = 8,
        .atkMagical = 8,
        .defValue = 8,
        .maxHP = 8,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SPRING,
        .image = &equipmentImages[3]
    };

    // 4 腳
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Beast Skin Leggings",
        .description = "Foot.",
        .price = 1,
        .slot = SLOT_FOOT,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 10,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SPRING,
        .image = &equipmentImages[4]
    };

    // 第二層
    // 5 頭
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Flower Crown",
        .description = "Head.",
        .price = 1,
        .slot = SLOT_HEAD,
        .atkPhysical = 5,
        .atkMagical = 10,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SPRING,
        .image = &equipmentImages[5]
    };

    // 6 身體
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Leaf Shawl",
        .description = "Body.",
        .price = 1,
        .slot = SLOT_BODY,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 10,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SPRING,
        .image = &equipmentImages[6]
    };

    // 7 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Wand",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SPRING,
        .image = &equipmentImages[7]
    };

    // 8 首飾
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Flower Collar",
        .description = "Accessory.",
        .price = 1,
        .slot = SLOT_ACCESSORY,
        .atkPhysical = 8,
        .atkMagical = 8,
        .defValue = 8,
        .maxHP = 8,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SPRING,
        .image = &equipmentImages[8]
    };

    //9 腳
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Grass Woven Sandals",
        .description = "Foot.",
        .price = 1,
        .slot = SLOT_FOOT,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 10,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SPRING,
        .image = &equipmentImages[9]
    };

    // 第三層
    // 10 頭
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Elven Crown",
        .description = "Head.",
        .price = 1,
        .slot = SLOT_HEAD,
        .atkPhysical = 5,
        .atkMagical = 10,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SPRING,
        .image = &equipmentImages[10]
    };

    // 11 身體
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Elven Robe",
        .description = "Body.",
        .price = 1,
        .slot = SLOT_BODY,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 10,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SPRING,
        .image = &equipmentImages[11]
    };

    // 12 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Staff of light",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SPRING,
        .image = &equipmentImages[12]
    };

    // 13 首飾
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Fairy Elf Wings",
        .description = "Accessory.",
        .price = 1,
        .slot = SLOT_ACCESSORY,
        .atkPhysical = 8,
        .atkMagical = 8,
        .defValue = 8,
        .maxHP = 8,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SPRING,
        .image = &equipmentImages[13]
    };

    //14 腳
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Gladiator Sandals",
        .description = "Foot.",
        .price = 1,
        .slot = SLOT_FOOT,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 10,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SPRING,
        .image = &equipmentImages[14]
    };

    // 第四層
    // 15 頭
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Straw Hat",
        .description = "Head.",
        .price = 1,
        .slot = SLOT_HEAD,
        .atkPhysical = 5,
        .atkMagical = 10,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[15]
    };

    // 16 身體
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Aloha Shirt",
        .description = "Body.",
        .price = 1,
        .slot = SLOT_BODY,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 10,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[16]
    };

    // 17 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Watch",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[17]
    };

    // 18 首飾
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Shell Necklace",
        .description = "Accessory.",
        .price = 1,
        .slot = SLOT_ACCESSORY,
        .atkPhysical = 8,
        .atkMagical = 8,
        .defValue = 8,
        .maxHP = 8,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[18]
    };

    // 19 腳
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Flip-flops",
        .description = "Foot.",
        .price = 1,
        .slot = SLOT_FOOT,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 10,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[19]
    };

    // 第五層
    // 20 頭
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Diving Mask",
        .description = "Head.",
        .price = 1,
        .slot = SLOT_HEAD,
        .atkPhysical = 5,
        .atkMagical = 10,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[20]
    };

    // 21 身體
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Wetsuit",
        .description = "Body.",
        .price = 1,
        .slot = SLOT_BODY,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 10,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[21]
    };

    // 22 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Flashlight",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[22]
    };

    //23 首飾
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Scuba Tank",
        .description = "Accessory.",
        .price = 1,
        .slot = SLOT_ACCESSORY,
        .atkPhysical = 8,
        .atkMagical = 8,
        .defValue = 8,
        .maxHP = 8,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[23]
    };

    // 24 腳
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Swim Fins",
        .description = "Foot.",
        .price = 1,
        .slot = SLOT_FOOT,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 10,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[24]
    };

    // 第六層
    // 25 頭
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Sailor Hat",
        .description = "Head.",
        .price = 1,
        .slot = SLOT_HEAD,
        .atkPhysical = 5,
        .atkMagical = 10,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[25]
    };

    // 26 身體
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Sailor Suit",
        .description = "Body.",
        .price = 1,
        .slot = SLOT_BODY,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 10,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[26]
    };

    // 27 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Compass",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[27]
    };

    //28 首飾
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Binoculars",
        .description = "Accessory.",
        .price = 1,
        .slot = SLOT_ACCESSORY,
        .atkPhysical = 8,
        .atkMagical = 8,
        .defValue = 8,
        .maxHP = 8,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[28]
    };

    // 29 腳
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Canvas Shoes",
        .description = "Foot.",
        .price = 1,
        .slot = SLOT_FOOT,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 10,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_SUMMER,
        .image = &equipmentImages[29]
    };

    //第七層
    // 30 頭
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Ninja Headband",
        .description = "Head.",
        .price = 1,
        .slot = SLOT_HEAD,
        .atkPhysical = 5,
        .atkMagical = 10,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[30]
    };

    // 31 身體
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Ninja Suit",
        .description = "Body.",
        .price = 1,
        .slot = SLOT_BODY,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 10,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[31]
    };

    // 32 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Hand Wraps",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[32]
    };

    // 33 首飾
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Shuriken",
        .description = "Accessory.",
        .price = 1,
        .slot = SLOT_ACCESSORY,
        .atkPhysical = 8,
        .atkMagical = 8,
        .defValue = 8,
        .maxHP = 8,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[33]
    };

    // 34 腳
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Geta Footwear",
        .description = "Foot.",
        .price = 1,
        .slot = SLOT_FOOT,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 10,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[34]
    };

    //第八層
    // 35 頭
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Soldier Helmet",
        .description = "Head.",
        .price = 1,
        .slot = SLOT_HEAD,
        .atkPhysical = 5,
        .atkMagical = 10,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[35]
    };

    // 36 身體
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Soldier Suit",
        .description = "Body.",
        .price = 1,
        .slot = SLOT_BODY,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 10,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[36]
    };

    // 37 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Half Finger Gloves",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[37]
    };

    // 38 首飾
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Dog Tag",
        .description = "Accessory.",
        .price = 1,
        .slot = SLOT_ACCESSORY,
        .atkPhysical = 8,
        .atkMagical = 8,
        .defValue = 8,
        .maxHP = 8,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[38]
    };

    // 39 腳
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Soldier Boots",
        .description = "Foot.",
        .price = 1,
        .slot = SLOT_FOOT,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 10,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[39]
    };

    //第九層
    // 40 頭
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Knight Helmet",
        .description = "Head.",
        .price = 1,
        .slot = SLOT_HEAD,
        .atkPhysical = 5,
        .atkMagical = 10,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[40]
    };

    // 41 身體
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Knight Armor",
        .description = "Body.",
        .price = 1,
        .slot = SLOT_BODY,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 10,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[41]
    };

    // 42 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Knight Gauntlets",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 0,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[42]
    };

    //  43 首飾
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Coat of arms",
        .description = "Accessory.",
        .price = 1,
        .slot = SLOT_ACCESSORY,
        .atkPhysical = 8,
        .atkMagical = 8,
        .defValue = 8,
        .maxHP = 8,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[43]
    };

    // 44 腳
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "Knight Boots",
        .description = "Foot.",
        .price = 1,
        .slot = SLOT_FOOT,
        .atkPhysical = 5,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 10,
        .isEquipped = 0,
        .isPurchased = 0,
        .locked = 1,
        .season = SEASON_AUTUMN,
        .image = &equipmentImages[44]
    };

    // 第十層
    // 45 手
    equipmentList[equipmentCount++] = (EquipmentData){
        .name = "The Infinity Gauntlet",
        .description = "Hand.",
        .price = 1,
        .slot = SLOT_HAND,
        .atkPhysical = 10,
        .atkMagical = 5,
        .defValue = 5,
        .maxHP = 5,
        .isEquipped = 0,
        .isPurchased = 0,
        .season = SEASON_WINTER,
        .image = &equipmentImages[45]
    };
}


// 根據 index 取得裝備資料指標
// - index 必須在有效範圍內（0 到 equipmentCount-1）
// - 否則回傳 NULL
EquipmentData* GetEquipmentByIndex(int index) {
    if (index < 0 || index >= equipmentCount) return NULL;
    return &equipmentList[index];
}


// 回傳目前已初始化的裝備總數
// - 通常最大為 46（MAX_EQUIPMENTS）
int GetTotalEquipments(void) {
    return equipmentCount;
}


// 查詢指定欄位目前裝備中的裝備
// - 若該欄位尚未穿戴裝備，回傳 NULL
EquipmentData* GetEquippedInSlot(EquipSlot slot) {
    int idx = equippedIndices[slot];
    if (idx == -1) return NULL;
    return &equipmentList[idx];
}


// 裝備指定 index 的裝備資料
// - 若該裝備所屬欄位已穿其他裝備，會自動卸下
// - 並將該裝備標記為「已裝備」
void EquipItem(int index) {
    EquipmentData* eq = GetEquipmentByIndex(index);
    if (!eq) return;

    // 先卸下該欄位原有裝備
    UnequipSlot(eq->slot);

    // 裝備此裝備
    eq->isEquipped = 1;
    equippedIndices[eq->slot] = index;
}


// 卸下指定欄位的裝備
// - 若該欄位未穿戴裝備，無動作
void UnequipSlot(EquipSlot slot) {
    int idx = equippedIndices[slot];
    if (idx != -1) {
        equipmentList[idx].isEquipped = 0;
        equippedIndices[slot] = -1;
    }
}


// 根據季節與欄位，尋找符合的裝備
// - 用於「季節自動推薦穿戴裝備」的邏輯
// - 若找不到符合條件的裝備，回傳 NULL
EquipmentData* GetEquipmentForSeason(Season season, EquipSlot slot) {
    for (int i = 0; i < equipmentCount; i++) {
        if (equipmentList[i].season == season &&
            equipmentList[i].slot == slot) {
            return &equipmentList[i];
        }
    }
    return NULL;
}

void UnlockAllAccessorySlots() {
    for (int i = 0; i < GetTotalEquipments(); ++i) {
        EquipmentData* eq = GetEquipmentByIndex(i);
        if (eq && eq->slot == SLOT_ACCESSORY) {
            eq->locked = false;
        }
    }
}

void UnlockAllBootSlots() {
    for (int i = 0; i < GetTotalEquipments(); ++i) {
        EquipmentData* eq = GetEquipmentByIndex(i);
        if (eq && eq->slot == SLOT_FOOT) {
            eq->locked = false;
        }
    }
}