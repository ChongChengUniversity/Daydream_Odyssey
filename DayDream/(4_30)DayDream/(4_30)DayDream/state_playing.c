// state_playing.c
#include "stateController.h"
#include "CardManager.h"
#include "raylib.h"

#include "levelManager.h"     // 新增：關卡管理
#include "assetManager.h"     // 新增：取得背景貼圖

void EnterPlaying(void) {
    InitCards();
}

void UpdatePlaying(void) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        OnMouseClick(mousePos); // 用 CardManager 處理點擊
    }
}

void RenderPlaying(void) {
    ClearBackground(RAYWHITE);

    // 依照目前關卡畫出背景圖（從 assets/1.png ~ assets/4.png）
    DrawTexture(textures[GetCurrentLevel() - 1], 0, 0, WHITE);

    DrawAllCards(); // 用 CardManager 畫所有卡片
}

void ExitPlaying(void) {
    // 若有需要釋放記憶體，可以在這裡做
}

const GameState STATE_PLAYING = {
    .enter = EnterPlaying,
    .update = UpdatePlaying,
    .render = RenderPlaying,
    .exit = ExitPlaying
};
