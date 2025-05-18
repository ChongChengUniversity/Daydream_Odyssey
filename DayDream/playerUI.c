//playerUI.c
#include "playerUI.h"
#include "CharacterStats.h"
#include "raylib.h"
#include "config.h"
#include "assetManager.h"

// for drawing text close to the enemy and player
void DrawBoldText(const char* text, int posX, int posY, int fontSize, Color color, int thickness) {
    // draw black frame
    for (int dx = -thickness; dx <= thickness; dx++) {
        for (int dy = -thickness; dy <= thickness; dy++) {
            if (dx != 0 || dy != 0)
                DrawText(text, posX + dx, posY + dy, fontSize, BLACK);
        }
    }
    // draw colorful text in the middle of the frame
    DrawText(text, posX, posY, fontSize, color);
}

void DrawPlayerUI() {
    PlayerStats* player = GetPlayerStats();
    if (!player) return;

    int fontSize = 16;
    int thickness = 1;

    Texture2D texture = textures[TEXTURE_ENEMY]; // should be player's texture
    float scale = (float)TILE_SIZE * 1.5f / texture.width;
    float texW = texture.width * scale;
    float texH = texture.height * scale;

    Vector2 pos = {
        (SCREEN_WIDTH - texW) / 2,
        SCREEN_HEIGHT - texH - 40
    };

    // draw player in middle down
    DrawTextureEx(texture, pos, 0.0f, scale, WHITE);

    // draw HP, red text
    DrawBoldText(TextFormat("%d", player->currentHp), pos.x + 4, pos.y + 4, fontSize, RED, thickness);

    // draw attack, yellow text
    DrawBoldText(TextFormat("%d", player->atk), pos.x + 4, pos.y + texH - fontSize - 4, fontSize, YELLOW, thickness);
}