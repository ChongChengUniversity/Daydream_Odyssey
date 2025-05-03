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

    DrawTexture(textures[GetCurrentLevel() - 1], 0, 0, WHITE);

    DrawAllCards();
}

void ExitPlaying(void) {
    
}

const GameState STATE_PLAYING = {
    .enter = EnterPlaying,
    .update = UpdatePlaying,
    .render = RenderPlaying,
    .exit = ExitPlaying
};
