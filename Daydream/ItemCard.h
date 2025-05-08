// ItemCard.h
#pragma once
#include "CardBase.h"
#include "assetManager.h"  // 引入 assetManager.h 而不是重新定義 ItemType

ItemType GetRandomItemType();  // 在此處添加函式原型宣告
 
CardBase* CreateItemCard(float x, float y, ItemType type);  // ItemCard.c
