// EnemyCard.c
#include "EnemyCard.h"
#include "config.h"
#include <stdlib.h>
#include "stateController.h"
#include "assetManager.h"

static void ResetEnemy(CardBase* self) {
    self->isRevealed = false;
}

static void DrawEnemy(CardBase* self) {
    if (self->isRevealed)
        DrawTextureEx(textures[TEXTURE_ENEMY], (Vector2) { self->bounds.x, self->bounds.y }, 0.0f,
            (float)TILE_SIZE / textures[TEXTURE_ENEMY].width, WHITE);
    else
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
}

static void OnRevealEnemy(CardBase* self) {
    self->isRevealed = true;
    // 這邊可以加：遊戲失敗邏輯
}

static void OnInteractEnemy(CardBase* self) {
    // 敵人被按第二次，可以設計成扣血、警告等等
    GOTO(LOSE);
}


CardBase* CreateEnemyCard(float x, float y) {
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL; // 如果 malloc 失敗，直接回傳 NULL

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = false;
    card->reset = ResetEnemy;
    card->draw = DrawEnemy;
    card->onReveal = OnRevealEnemy;
    card->onInteract = OnInteractEnemy; 
    return card;
}