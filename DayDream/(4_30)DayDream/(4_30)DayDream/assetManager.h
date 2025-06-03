// assetManager.h
#pragma once
#include "raylib.h"

#define BACKGROUND_COUNT 4
#define CARD_IMAGE_COUNT 3  // 新增 3 種卡片圖片

#define TEXTURE_BG_START 0
#define TEXTURE_CARD_START (TEXTURE_BG_START + BACKGROUND_COUNT)

#define TEXTURE_DOOR (TEXTURE_CARD_START + 0)
#define TEXTURE_ENEMY (TEXTURE_CARD_START + 1)
#define TEXTURE_ITEM (TEXTURE_CARD_START + 2)

#define MAX_TEXTURES (BACKGROUND_COUNT + CARD_IMAGE_COUNT)

extern Texture2D textures[MAX_TEXTURES];

void InitAssetManager();
void ShutdownAssetManager();
