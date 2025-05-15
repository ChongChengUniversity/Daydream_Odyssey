// state_shop.h

#pragma once                 // 防止重複包含這個標頭檔
#include "stateController.h" // 需要 GameState 結構定義

extern const GameState STATE_SHOP; // 宣告本體：由 state_shop.c 提供內容
extern const GameState* SHOP; // 宣告指標：讓你在其他模組直接用 GOTO(SHOP) 這種簡寫
