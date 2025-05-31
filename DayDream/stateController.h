// stateController.h
#pragma once

typedef struct GameState {
    void (*enter)();
    void (*update)();
    void (*render)();
    void (*exit)();
} GameState;

extern const GameState* currentState;

// 現有狀態
extern const GameState* MAIN_MENU;
extern const GameState* PLAYING;
extern const GameState* WIN;
extern const GameState* LOSE;
extern const GameState* OPTION_MENU;
extern const GameState STATE_OPENING_CUTSCENE;

// 新增的結局選擇狀態
extern const GameState* ENDING_CHOICE; // 宣告新的結局選擇狀態

void ChangeState(const GameState* newState);
const GameState* GetCurrentGameState(void); // 新增：獲取當前狀態的函式

#define GOTO(state) ChangeState(state)