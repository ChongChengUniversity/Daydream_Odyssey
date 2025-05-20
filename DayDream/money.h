// money.h
#pragma once

// 金幣操作
void InitMoneySystem();
void ShutdownMoneySystem();
void AddCoins(int amount);
void SubtractCoins(int amount);
int GetPlayerCoins(void);
void DrawMoneyUI(void);