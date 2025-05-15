// stateController.c
#include "stateController.h"

#include <stddef.h>

// 手動宣告每個 state 的 struct（不需要 .h）
extern const GameState STATE_MAIN_MENU;
extern const GameState STATE_PLAYING;
extern const GameState STATE_WIN;
extern const GameState STATE_LOSE;
extern const GameState STATE_OPTION_MENU;
extern const GameState STATE_SHOP;

// 全域目前狀態指標
const GameState* currentState = NULL;

// 實際的狀態切換函式
void ChangeState(const GameState* newState) {
    if (currentState && currentState->exit)
        currentState->exit();
    currentState = newState;
    if (currentState && currentState->enter)
        currentState->enter();
}

// 對外提供的語意化指標
const GameState* MAIN_MENU = &STATE_MAIN_MENU;
const GameState* PLAYING = &STATE_PLAYING;
const GameState* WIN = &STATE_WIN;
const GameState* LOSE = &STATE_LOSE;
const GameState* OPTION_MENU = &STATE_OPTION_MENU;
const GameState* SHOP = &STATE_SHOP;
