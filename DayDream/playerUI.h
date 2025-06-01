// playerUI.h
#ifndef PLAYER_UI_H
#define PLAYER_UI_H
#include <raylib.h>

void DrawPlayerUI(void);
void DrawBoldText(const char* text, int posX, int posY, int fontSize, Color color, int thickness);

#endif