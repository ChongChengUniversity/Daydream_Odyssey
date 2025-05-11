//playerUI.c
#include "playerUI.h"
#include "CharacterStats.h"
#include "raylib.h"
#include "config.h"
#include "assetManager.h"

void DrawBoldText(const char* text, int posX, int posY, int fontSize, Color color, int thickness) {
    // 畫黑邊框
    for (int dx = -thickness; dx <= thickness; dx++) {
        for (int dy = -thickness; dy <= thickness; dy++) {
            if (dx != 0 || dy != 0)
                DrawText(text, posX + dx, posY + dy, fontSize, BLACK);
        }
    }
    // 畫中間彩色字
    DrawText(text, posX, posY, fontSize, color);
}

void DrawPlayerUI() {
    PlayerStats* player = GetPlayerStats();
    if (!player) return;

    int fontSize = 16;
    int thickness = 1;

    Texture2D texture = textures[TEXTURE_ENEMY]; // 暫用主角圖
    float scale = (float)TILE_SIZE * 1.5f / texture.width;
    float texW = texture.width * scale;
    float texH = texture.height * scale;

    Vector2 pos = {
        (SCREEN_WIDTH - texW) / 2,
        SCREEN_HEIGHT - texH - 40
    };

    // 畫主角圖
    DrawTextureEx(texture, pos, 0.0f, scale, WHITE);

    // 血量（紅色文字＋黑框）在左上
    DrawBoldText(TextFormat("%d", player->currentHp), pos.x + 4, pos.y + 4, fontSize, RED, thickness);

    // 攻擊力（黃色文字＋黑框）在左下
    DrawBoldText(TextFormat("%d", player->atk), pos.x + 4, pos.y + texH - fontSize - 4, fontSize, YELLOW, thickness);
}

