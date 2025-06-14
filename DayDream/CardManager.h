// CardManager.h
#pragma once
#include "raylib.h"
#include "config.h"
#include "CardBase.h"

extern CardBase *cards[TOTAL_CARDS];

// 函式宣告
void InitCards();
void DrawAllCards();
void OnMouseClick(Vector2 mousePos);
void ResetAllCards(); 

// 賦予每個牌種類並打散
void InitCardTypes();

// 控制哪些格子允許被翻開
void AbleToReveal();

// 一開始自動翻開門並更新可翻開卡片
void RevealDoorCardAtStart();

bool IsEnemyCardAt(int row, int col);

//怪物死亡後怪物卡轉為空卡
void ReplaceCardWithEmpty(int index, bool shouldReveal);

void DestroyCard(CardBase* card);

void SafeDestroyCard(CardBase** pCard);

GridPos GetClickedGrid(Vector2 mousePos);

void ReplaceCardWithPortal(int index, bool shouldReveal);