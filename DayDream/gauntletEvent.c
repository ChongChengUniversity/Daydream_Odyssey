// gauntletEvent.c
#include "gauntletEvent.h"
#include "raylib.h"
#include "config.h"          
#include "assetManager.h"    
#include "enemyManager.h"
#include "CardBase.h"
#include "levelManager.h"
#include "story.h"
#include "CardManager.h"
#include "CharacterStats.h"
#include "assetManager.h"

// 可由其他模組使用的變數
bool infinityGauntletAvailable = false;
float infinityGauntletScale = 0.3f;

void GivePlayerInfinityGauntlet(void) {
    infinityGauntletAvailable = true;
}

Rectangle GetInfinityGauntletRect(void) {
    float iconWidth = TEX_INFINITY_GAUNTLET.width * infinityGauntletScale;
    float iconHeight = TEX_INFINITY_GAUNTLET.height * infinityGauntletScale;

    // 與背包 icon 對稱（鏡像）：10 px from left, same Y as backpack
    float x = 3;
    float y = SCREEN_HEIGHT - iconHeight - 10;

    return (Rectangle){ x, y, iconWidth, iconHeight };
}

void KillAllEnemiesOnBoard(void)
{
    for (int i = 0; i < TOTAL_CARDS; ++i) {
        if (cards[i]->type != TYPE_ENEMY) continue;

        int row = cards[i]->row;
        int col = cards[i]->col;
        EnemyInfo* enemyInfoPtr = &enemyInfo[row][col];
        EnemyStats* enemy = &enemyInfoPtr->stats;

        // 直接把怪物血量設為0，或用 ApplyDamageToEnemy 並傳入足夠大數字
        bool enemyDead = ApplyDamageToEnemy(enemy, 9999); // 確保秒殺

        if (enemyDead) {
            if(i==12){
                ReplaceCardWithPortal(cards[i]->indexInArray, true);
            }
            else{
                ReplaceCardWithEmpty(cards[i]->indexInArray, true);
            }
            
        }

        AbleToReveal();
        UpdateVisibleBufferCounts();
        ApplyBuffsToVisibleEnemies();
    }
}

void DrawInfinityGauntletIcon(void) {
    if (!infinityGauntletAvailable) return;

    Rectangle rect = GetInfinityGauntletRect();
    Vector2 mousePos = GetMousePosition();

    Color tint = CheckCollisionPointRec(mousePos, rect) ? (Color){255, 255, 255, 200} : WHITE;

    DrawTextureEx(TEX_INFINITY_GAUNTLET, (Vector2){rect.x, rect.y}, 0.0f, infinityGauntletScale, tint);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, rect)) {
        KillAllEnemiesOnBoard();
        infinityGauntletAvailable = false;
    }
}

// void CheckLevelProgress(void)
// {
//     if (GetCurrentLevel()==10 && !HasEnemyOnBoard() && !IsDialogueActive())
//     {
//         // StartDialogue(infinityGauntletDialogue, infinityGauntletDialogueCount);
//         GivePlayerInfinityGauntlet(); // 這會讓左下角icon顯示
//     }
// }
