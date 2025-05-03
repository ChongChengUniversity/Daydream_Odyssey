#include "raylib.h"
#include "stateController.h"
#include "config.h"
#include "audioManager.h"
#include <stdlib.h>

const char* labelEnter = "PRESS ENTER FOR MAIN MENU";

static void EnterOptionMenu() {

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
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKBLUE);
    DrawText("MINESWEEPER :: OPTIONS", 20, 20, 40, WHITE);

    DrawText("[S]ound ", 120, 220, 20, WHITE);
    if (isSoundEnabled) { //�]���|�C���H�ɳ��i���ܡA�ҥH��GameRender��
        DrawText("ON", 280, 220, 20, YELLOW);
        DrawText(" / ", 310, 220, 20, WHITE);
        DrawText("OFF", 350, 220, 20, WHITE);
    }
    else {
        DrawText("ON", 280, 220, 20, WHITE);
        DrawText(" / ", 310, 220, 20, WHITE);
        DrawText("OFF", 350, 220, 20, YELLOW);
    }

    DrawText("[M]usic", 120, 250, 20, WHITE);
    if (isMusicEnabled) {
        DrawText("ON", 280, 250, 20, YELLOW);
        DrawText(" / ", 310, 250, 20, WHITE);
        DrawText("OFF", 350, 250, 20, WHITE);
    }
    else {
        DrawText("ON", 280, 250, 20, WHITE);
        DrawText(" / ", 310, 250, 20, WHITE);
        DrawText("OFF", 350, 250, 20, YELLOW);
    }
    DrawText(labelEnter, 120, 400, 20, WHITE);

}

static void ExitOptionMenu() {
    // �Ҧp����I�����ֵ�
}

const GameState STATE_OPTION_MENU = {
    .enter = NULL,
    .update = UpdateOptionMenu,
    .render = RenderOptionMenu,
    .exit = NULL
};