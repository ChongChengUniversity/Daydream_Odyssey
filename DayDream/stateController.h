// stateController.h
#pragma once

typedef struct GameState {
    void (*enter)();
    void (*update)();
    void (*render)();
    void (*exit)();
} GameState;

extern const GameState* currentState;
extern const GameState* MAIN_MENU;
extern const GameState* PLAYING;
extern const GameState* WIN;
extern const GameState* LOSE;
extern const GameState* OPTION_MENU;

void ChangeState(const GameState* newState);

#define GOTO(state) ChangeState(state)
