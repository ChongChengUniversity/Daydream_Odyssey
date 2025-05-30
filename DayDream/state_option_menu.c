// state_option_menu.c
#include "raylib.h"
#include "stateController.h"
#include "config.h"
#include "audioManager.h"
#include <stdlib.h>

Texture2D optionBackground;

const char* labelEnter = "PRESS ENTER FOR MAIN MENU";

static void EnterOptionMenu() {
    optionBackground = LoadTexture("assets/option_background.png");
}

static void UpdateOptionMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        GamePlaySound(SOUND_TWO);
        GOTO(MAIN_MENU);
    }

    if (IsKeyPressed(KEY_S)) {
        isSoundEnabled = !isSoundEnabled;
        PlaySound(sounds[SOUND_ONE]);
    }

    if (IsKeyPressed(KEY_M)) {
        isMusicEnabled = !isMusicEnabled;
        PlaySound(sounds[SOUND_ONE]);
        if (isMusicEnabled) {
            StopMusicStream(music[MUSIC_ONE]);
            PlayMusicStream(music[MUSIC_ONE]);
        }
        else {
            StopMusicStream(music[MUSIC_ONE]);
        }
    }
}

static void RenderOptionMenu() {
    // 背景圖
    float screenRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    float imageRatio = (float)optionBackground.width / (float)optionBackground.height;

    float scale;
    if (screenRatio > imageRatio) {
        scale = (float)SCREEN_WIDTH / (float)optionBackground.width;
    } else {
        scale = (float)SCREEN_HEIGHT / (float)optionBackground.height;
    }

    float bgWidth = optionBackground.width * scale;
    float bgHeight = optionBackground.height * scale;
    float offsetX = (SCREEN_WIDTH - bgWidth) / 2;
    float offsetY = (SCREEN_HEIGHT - bgHeight) / 2;

    DrawTexturePro(optionBackground,
                   (Rectangle){0, 0, optionBackground.width, optionBackground.height},
                   (Rectangle){offsetX, offsetY, bgWidth, bgHeight},
                   (Vector2){0, 0}, 0.0f, WHITE);

    // DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKBLUE);
    DrawText("DAYDREAM :: OPTIONS", 20, 20, 45, WHITE);

    DrawText("[S]ound ", 120, 220, 30, WHITE);
    if (isSoundEnabled) {
        DrawText("ON", 280, 220, 30, YELLOW);
        DrawText(" / ", 310, 220, 25, WHITE);
        DrawText("OFF", 350, 220, 25, WHITE);
    }
    else {
        DrawText("ON", 280, 220, 25, WHITE);
        DrawText(" / ", 310, 220, 25, WHITE);
        DrawText("OFF", 350, 220, 30, YELLOW);
    }

    DrawText("[M]usic", 120, 250, 30, WHITE);
    if (isMusicEnabled) {
        DrawText("ON", 280, 250, 30, YELLOW);
        DrawText(" / ", 310, 250, 25, WHITE);
        DrawText("OFF", 350, 250, 25, WHITE);
    }
    else {
        DrawText("ON", 280, 250, 25, WHITE);
        DrawText(" / ", 310, 250, 25, WHITE);
        DrawText("OFF", 350, 250, 30, YELLOW);
    }
    DrawText(labelEnter, 120, 500, 30, WHITE);

}

static void ExitOptionMenu() {
    UnloadTexture(optionBackground);
}

const GameState STATE_OPTION_MENU = {
    .enter = EnterOptionMenu,
    .update = UpdateOptionMenu,
    .render = RenderOptionMenu,
    .exit = ExitOptionMenu
};