// EnemyCard.c
#include "EnemyCard.h"
#include "config.h"
#include <stdlib.h>
#include "stateController.h"
#include "assetManager.h"
#include "CombatSystem.h"
#include "CharacterStats.h"
#include "CardManager.h"

static void DrawBoldText(const char *text, int posX, int posY, int fontSize, Color color)
{
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 || dy != 0)
            {

                DrawText(text, posX + dx, posY + dy, fontSize, BLACK); // draw the edge
            }
        }
    }

    DrawText(text, posX, posY, fontSize, color); // draw the text itself
}

static void ResetEnemy(CardBase *self)
{
    self->isRevealed = false;
}

static void DrawEnemy(CardBase *self)
{
    if (self->isRevealed)
    {
        DrawTextureEx(textures[TEXTURE_ENEMY], (Vector2){self->bounds.x, self->bounds.y}, 0.0f,
                      (float)TILE_SIZE / textures[TEXTURE_ENEMY].width, WHITE);

        EnemyStats *enemy = (EnemyStats *)self->data;

        Rectangle bounds = self->bounds;

        float centerX = bounds.x + bounds.width / 2;
        float centerY = bounds.y + bounds.height / 2;
        float radius = bounds.width / 2;

        /*
        // 黃色圓：防禦
        if (enemy->def > 0) {
             DrawCircle(centerX, centerY, radius * 0.85f, YELLOW);
        }
        // 紅色圓：血量比例
        float hpRatio = (float)enemy->currentHp / (float)enemy->maxHp;
        DrawCircle(centerX, centerY, radius * hpRatio * 0.7f, RED);
        */

        int fontSize = 16;

        // 左上角：攻擊力（粗體黃色）
        DrawBoldText(TextFormat("%d", enemy->atk), bounds.x + 2, bounds.y + 2, fontSize, YELLOW);

        // 左下角：血量（粗體紅色）
        DrawBoldText(TextFormat("%d", enemy->currentHp), bounds.x + 2, bounds.y + bounds.height - fontSize - 2, fontSize, RED);
    }
    else
    {
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
    }
}

static void OnRevealEnemy(CardBase *self)
{
    self->isRevealed = true;
}

static void OnInteractEnemy(CardBase *self)
{
    PlayerStats *player = GetPlayerStats();

    EnemyStats *enemy = (EnemyStats *)self->data;

    bool enemyDead = AttackEnemy(player, enemy);

    if (enemyDead)
    {
        ReplaceCardWithEmpty(self->indexInArray);
    }
}

CardBase *CreateEnemyCard(float x, float y, int index)
{
    CardBase *card = malloc(sizeof(CardBase));
    if (!card)
        return NULL; // check malloc

    card->bounds = (Rectangle){x, y, TILE_SIZE, TILE_SIZE};
    card->isRevealed = false;
    card->reset = ResetEnemy;
    card->draw = DrawEnemy;
    card->onReveal = OnRevealEnemy;
    card->onInteract = OnInteractEnemy;
    card->indexInArray = index;
    card->data = CreateEnemyStats(10, 3, 1, false);
    return card;
}