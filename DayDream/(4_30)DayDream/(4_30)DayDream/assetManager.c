// assetManager.c
#include "assetManager.h"
#include <stdio.h>

Texture2D textures[MAX_TEXTURES];

void InitAssetManager() {
    for (int i = 0; i < BACKGROUND_COUNT; ++i) {
        char path[64];
        sprintf_s(path, sizeof(path), "assets/%d.png", i + 1); // 1.png 2.png ...
        textures[TEXTURE_BG_START + i] = LoadTexture(path);
    }

    textures[TEXTURE_DOOR] = LoadTexture("assets/door.png");
    textures[TEXTURE_ENEMY] = LoadTexture("assets/enemy.png");
    textures[TEXTURE_ITEM] = LoadTexture("assets/item.png");
}


void ShutdownAssetManager() {
    for (int i = 0; i < MAX_TEXTURES; i++) {
        UnloadTexture(textures[i]);
    }
}
