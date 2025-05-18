// shopicon.h
#pragma once
#include "raylib.h"

void InitShopIcon(void);
void DrawShopIcon(void);
void UpdateShopIcon(void); // track mouse click
void SetReturningFromShop(bool flag); // state flag
bool IsReturningFromShop(void);
