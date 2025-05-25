// shopSystem.c
#include "shopSystem.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

void UpdateShopInteraction(Rectangle* itemBounds, int itemCount, int* hoverIndex, int* infoIndex, const bool* isActive) {
    Vector2 mouse = GetMousePosition();
    *hoverIndex = -1;

    for (int i = 0; i < itemCount; ++i) {
        if (!isActive[i]) continue;

        if (CheckCollisionPointRec(mouse, itemBounds[i])) {
            *hoverIndex = i;

            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                *infoIndex = i; // 顯示道具資訊
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && *hoverIndex == -1) {
        *infoIndex = -1; // 點空白區域關閉資訊框
    }
}


void RenderItemHover(int hoverIndex, Rectangle* itemBounds, int itemCount) {
    if (hoverIndex >= 0 && hoverIndex < itemCount) {
        DrawRectangleRec(itemBounds[hoverIndex], (Color){220, 180, 100, 100});
    }
}

void RenderItemInfo(int infoIndex, Rectangle* itemBounds, const char* infoText) {
    if (infoIndex < 0) return;

    int infoWidth = 240;
    int infoHeight = 80;
    int padding = 10;

    Rectangle box = {
        itemBounds[infoIndex].x + (itemBounds[infoIndex].width / 2) - (infoWidth / 2),
        itemBounds[infoIndex].y - infoHeight - 10,
        infoWidth,
        infoHeight
    };

    DrawRectangleRec(box, (Color){50, 50, 50, 230});
    DrawRectangleLinesEx(box, 2, GOLD);
    DrawText(infoText, box.x + padding, box.y + padding, 18, RAYWHITE);
}
