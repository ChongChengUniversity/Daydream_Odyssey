// state_playing.c
#include "stateController.h"
#include "CardManager.h"
#include "raylib.h"

#include "levelManager.h"     // �s�W�G���d�޲z
#include "assetManager.h"     // �s�W�G���o�I���K��

void EnterPlaying(void) {
    InitCards();
}

void UpdatePlaying(void) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        OnMouseClick(mousePos); // �� CardManager �B�z�I��
    }
}

void RenderPlaying(void) {
    ClearBackground(RAYWHITE);

    // �̷ӥثe���d�e�X�I���ϡ]�q assets/1.png ~ assets/4.png�^
    DrawTexture(textures[GetCurrentLevel() - 1], 0, 0, WHITE);

    DrawAllCards(); // �� CardManager �e�Ҧ��d��
}

void ExitPlaying(void) {
    // �Y���ݭn����O����A�i�H�b�o�̰�
}

const GameState STATE_PLAYING = {
    .enter = EnterPlaying,
    .update = UpdatePlaying,
    .render = RenderPlaying,
    .exit = ExitPlaying
};
