// state_shop.h
#pragma once                 // prevent the file from double definition
#include "stateController.h"

extern const GameState STATE_SHOP; // declared here, defined in state_shop.c ("extern")
extern const GameState* SHOP; // declared pointer to use GOTO(SHOP)
