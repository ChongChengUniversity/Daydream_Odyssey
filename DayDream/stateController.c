// stateController.c
#include "stateController.h"
#include<stddef.h>

extern const GameState STATE_MAIN_MENU;
extern const GameState STATE_PLAYING;
extern const GameState STATE_WIN;
extern const GameState STATE_LOSE;
extern const GameState STATE_OPTION_MENU;
extern const GameState STATE_SHOP;

const GameState* currentState = NULL;

void ChangeState(const GameState* newState) {
    if (currentState && currentState->exit)
        currentState->exit();
    currentState = newState;
    if (currentState && currentState->enter)
        currentState->enter();
}

const GameState* MAIN_MENU = &STATE_MAIN_MENU;
const GameState* PLAYING = &STATE_PLAYING;
const GameState* WIN = &STATE_WIN;
const GameState* LOSE = &STATE_LOSE;
const GameState* OPTION_MENU = &STATE_OPTION_MENU;
const GameState* SHOP = &STATE_SHOP;
