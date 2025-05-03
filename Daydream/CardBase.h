// CardBase.h
#pragma once
#include "raylib.h"

// 前向宣告（為了可以用 CardBase* 指標）
typedef struct CardBase CardBase;

// 定義卡片共通結構
struct CardBase {
    Rectangle bounds;           // 這張卡片的位置和大小（x, y, width, height）
    bool isRevealed;            // 這張卡片目前是否已經被翻開

    // 三個插座（函式指標）
    void (*reset)(CardBase* self);    // 重置卡片（蓋回去）
    void (*draw)(CardBase* self);     // 畫自己（正面或背面）
    void (*onReveal)(CardBase* self); // 被翻開時要做什麼
    void (*onInteract)(CardBase* self); // 新增的插座！
};
