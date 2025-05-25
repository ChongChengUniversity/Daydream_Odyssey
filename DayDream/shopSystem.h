#pragma once
#include "raylib.h"
#include <stdbool.h>

void UpdateShopInteraction(Rectangle* itemBounds, int itemCount, int* hoverIndex, int* infoIndex, const bool* isActive);
void RenderItemHover(int hoverIndex, Rectangle* itemBounds, int itemCount);
void RenderItemInfo(int infoIndex, Rectangle* itemBounds, const char* infoText);

