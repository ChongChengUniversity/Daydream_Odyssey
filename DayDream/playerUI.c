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

// void DrawBoldText(const char* text, int posX, int posY, int fontSize, Color color, int thickness) {
//     // 黑色描邊
//     for (int dx = -thickness; dx <= thickness; dx++) {
//         for (int dy = -thickness; dy <= thickness; dy++) {
//             if (dx != 0 || dy != 0)
//                 DrawText(text, posX + dx, posY + dy, fontSize, BLACK);
//         }
//     }

//     // 畫彩色字體：中央一次
//     DrawText(text, posX, posY, fontSize, color);
//     // 額外畫幾次彩色文字，讓它更粗
//     DrawText(text, posX + 1, posY, fontSize, color);
//     DrawText(text, posX, posY + 1, fontSize, color);
// }

void DrawPlayerUI() {
    PlayerStats* player = GetPlayerStats();
    if (!player) return;

    int fontSize = 18;
    int thickness = 1;

    Texture2D texture = player->isHit ? textures[TEXTURE_CHARACTER_HURT] : textures[TEXTURE_CHARACTER];
    float scale = (float)TILE_SIZE * 1.6f / texture.width;
    float texW = texture.width * scale;
    float texH = texture.height * scale;

    Vector2 pos = {
        (SCREEN_WIDTH - texW) / 2,
        SCREEN_HEIGHT - texH + 26 
    };

    // draw player in middle down
    DrawTextureEx(texture, pos, 0.0f, scale, WHITE);

    // 文字位置計算
    int atkPosX = pos.x - 16;
    int atkPosY = pos.y + 14; 

    int hpPosX = pos.x - 16;
    int hpPosY = pos.y + texH - fontSize - 28;

    int magicPosX = pos.x + texW - 24;
    int magicPosY = pos.y + 14;

    int defPosX = pos.x + texW - 24;
    int defPosY = pos.y + texH - fontSize - 28;

    // 畫出攻擊（黃色）
    DrawBoldText(TextFormat("%d", player->atk), atkPosX, atkPosY, fontSize, ORANGE, thickness);

    // 畫出血量（紅色）
    DrawBoldText(TextFormat("%d", player->currentHp), hpPosX, hpPosY, fontSize, RED, thickness);

    // 畫出魔力（藍色）
    DrawBoldText(TextFormat("%d", player->magic), magicPosX, magicPosY, fontSize, PURPLE, thickness);

    // 畫出防禦（綠色）
    DrawBoldText(TextFormat("%d", player->def), defPosX, defPosY, fontSize, YELLOW, thickness);

    // // draw attack, yellow text
    // DrawBoldText(TextFormat("%d", player->atk), pos.x + 4, pos.y + 4, fontSize, YELLOW, thickness);

    // // draw HP, red text
    // DrawBoldText(TextFormat("%d", player->currentHp), pos.x + 4, pos.y + texH - fontSize - 4, fontSize, RED, thickness);

    // // draw magic, blue text (右上角)
    // DrawBoldText(TextFormat("%d", player->magic), pos.x + texW - 24, pos.y + 4, fontSize, BLUE, thickness);
}