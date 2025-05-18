// ItemCard.h
#pragma once
#include "CardBase.h"
#include "assetManager.h"

CardBase* CreateItemCard(float x, float y, int index, ItemType type);
ItemType GetRandomItemType();
