// stateController.c
#include "stateController.h"
#include <stddef.h> // For NULL

// 宣告外部定義的GameState實例
extern const GameState STATE_MAIN_MENU;
extern const GameState STATE_PLAYING;
extern const GameState STATE_WIN;
extern const GameState STATE_LOSE;
extern const GameState STATE_OPTION_MENU;
extern const GameState STATE_SHOP;
extern const GameState STATE_ENDING_CHOICE;

const GameState* currentState = NULL; // 初始化為NULL

void ChangeState(const GameState* newState) {
    if (currentState && currentState->exit) {
        currentState->exit();
    }
    currentState = newState;
    if (currentState && currentState->enter) {
        currentState->enter();
    }
}

// 實現獲取當前狀態的函式
const GameState* GetCurrentGameState(void) {
    return currentState;
}

// 初始化全域的GameState指針，指向實際的GameState實例
const GameState* MAIN_MENU = &STATE_MAIN_MENU;
const GameState* PLAYING = &STATE_PLAYING;
const GameState* WIN = &STATE_WIN;
const GameState* LOSE = &STATE_LOSE;
const GameState* OPTION_MENU = &STATE_OPTION_MENU;
const GameState* SHOP = &STATE_SHOP;
const GameState* ENDING_CHOICE = &STATE_ENDING_CHOICE;