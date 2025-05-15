// stateController.h
#pragma once

// 狀態結構定義（每個狀態都符合這個結構）
typedef struct GameState {
    void (*enter)();
    void (*update)();
    void (*render)();
    void (*exit)();
} GameState;

// 當前狀態（由 main loop 每幀調用）
extern const GameState* currentState;

// 🔹 對外提供的語意化狀態變數（讓你寫 GOTO(PLAYING);）
extern const GameState* MAIN_MENU;
extern const GameState* PLAYING;
extern const GameState* WIN;
extern const GameState* LOSE;
extern const GameState* OPTION_MENU;

// 切換狀態（由 GOTO 宏呼叫）
void ChangeState(const GameState* newState);

// 更自然的狀態切換語法：GOTO(PLAYING);
#define GOTO(state) ChangeState(state)
