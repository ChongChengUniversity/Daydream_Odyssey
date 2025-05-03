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
    // �o��i�H�[�G�C�������޿�
}

static void OnInteractEnemy(CardBase* self) {
    // �ĤH�Q���ĤG���A�i�H�]�p������Bĵ�i����
    GOTO(LOSE);
}


CardBase* CreateEnemyCard(float x, float y) {
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL; // �p�G malloc ���ѡA�����^�� NULL

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = false;
    card->reset = ResetEnemy;
    card->draw = DrawEnemy;
    card->onReveal = OnRevealEnemy;
    card->onInteract = OnInteractEnemy; 
    return card;
}