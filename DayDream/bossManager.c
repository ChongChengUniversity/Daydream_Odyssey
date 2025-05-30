// bossManager.c
// boss 所有機制另外計算
#include "bossManager.h"
#include "CardManager.h"
#include "CharacterStats.h"
#include "CombatSystem.h"
#include "enemyManager.h"
#include <stdio.h>
#include <stdbool.h>
#include "EnemyCard.h"
#include <stdlib.h>
#include "raylib.h"
#include "CardBase.h"
#include "EnemyStats.h"
#include "assetManager.h"

static int bossCD = 3;             // 初始冷卻：第一回合增益，下一回合開始攻擊
static bool bossAlive = true;     // 用來判斷 Boss 是否還活著
static int CDcount = 0;
static void DrawBoldText(const char* text, int posX, int posY, int fontSize, Color color) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx != 0 || dy != 0) {
                DrawText(text, posX + dx, posY + dy, fontSize, BLACK); // 黑邊
            }
        }
    }
    DrawText(text, posX, posY, fontSize, color); // 主文字
}
void InitBossState() {
    bossCD = 3;
    bossAlive = true;
}

void KillBoss() {
    bossAlive = false;
}

bool IsBossAlive() {
    return bossAlive;
}

int GetBossCD() {
    return bossCD;
}

// 每一回合呼叫：更新 CD、進行動作
void UpdateBossAction() {
    if (!bossAlive) return;

    EnemyStats* boss = &enemyInfo[BOSS_ROW][BOSS_COL].stats;
    if (boss->currentHp <= 0) {
        KillBoss();
        return;
    }

    if (bossCD > 0) {
        bossCD--;
        printf("Boss is preparing... CD = %d\n", bossCD);
        
    }
    if(bossCD == 0){
        CDcount ++;
        if(CDcount == 1){
            //全場增益
            for (int i = 0; i < TOTAL_CARDS; ++i) {
                if (cards[i] && cards[i]->type == TYPE_ENEMY) {
                    int row = cards[i]->row;
                    int col = cards[i]->col;

                    EnemyStats* stats = &enemyInfo[row][col].stats;
                    if (row == BOSS_ROW && col == BOSS_COL) continue; // 跳過 Boss 自己

                    stats->externalBonusAtk += 10;
                    stats->externalBonusDef += 2;
                }
            }
            printf("Boss buffed all monsters!\n");
        }else{
            boss->bonusAtk += 10;
            boss->atk = boss->baseAtk + boss->bonusAtk;
            printf("Boss powered up! Current ATK = %d\n", boss->atk);
        }
        bossCD = 3;
        ApplyBuffsToVisibleEnemies(); 

    }

    //攻擊玩家
    if (boss->currentHp < boss->maxHp / 2){
        PlayerStats* player = GetPlayerStats();
        int damage = CalculateDamage(boss->atk, player->def);
        ApplyDamageToPlayer(player, damage);
        printf("Boss attacks! Deals %d damage.\n", damage);
    }
    // 重置 CD
    
}

void ResetBoss(CardBase* self) {
    self->isRevealed = false;

    EnemyInfo* info = &enemyInfo[self->row][self->col];
    info->isVisible = true;
    info->isHidden = false;

    info->stats.maxHp = 80;
    info->stats.currentHp = 80;
    info->stats.baseAtk = 10;
    info->stats.baseDef = 6;
    info->stats.bonusAtk = 0;
    info->stats.bonusDef = 0;
    info->stats.externalBonusAtk = 0;
    info->stats.externalBonusDef = 0;
    info->stats.atk = info->stats.baseAtk;
    info->stats.def = info->stats.baseDef;

    bossCD = 3;
    CDcount = 0;
    bossAlive = true;
}


CardBase* CreateBossCard(float x, float y, int index, int row, int col) {
    CardBase* card = malloc(sizeof(CardBase));
    if (!card) return NULL;

    card->bounds = (Rectangle){ x, y, TILE_SIZE, TILE_SIZE };
    card->isRevealed = true; // Boss 一開始就顯示
    card->indexInArray = index;
    card->row = row;
    card->col = col;
    card->data = NULL;
    card->type = TYPE_ENEMY;

    // ----- 行為 -----
    card->reset = ResetBoss; // 如有需求可以寫 ResetBoss
    card->onReveal = NULL; // 不需要額外 reveal 行為
    card->onInteract = OnInteractBoss;
    card->draw = DrawBoss;

    // ----- 數值 -----
    EnemyInfo* info = &enemyInfo[row][col];
    info->type = MONSTER_BOSS; 
    info->isVisible = true;
    info->isHidden = false;
    info->stats.maxHp = 80;
    info->stats.currentHp = 80;
    info->stats.baseAtk = 10;
    info->stats.baseDef = 6;
    info->stats.bonusAtk = 0;
    info->stats.bonusDef = 0;
    info->stats.atk = info->stats.baseAtk;
    info->stats.def = info->stats.baseDef;
    info->stats.type = MONSTER_BOSS;
    info->stats.externalBonusAtk = 0;
    info->stats.externalBonusDef = 0;


    return card;
}


void DrawBoss(CardBase* self) {
    if (!self || !self->isRevealed) {
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
        return;
    }

    Rectangle bounds = self->bounds;

    // 畫底色（紫色）
    DrawRectangleRec(bounds, (Color) { 100, 0, 150, 255 });

    // 放大倍率
    float scale = 1.8f;

    // 取得圖片原始寬高
    int texWidth = monsters[MONSTER_BOSS].width;
    int texHeight = monsters[MONSTER_BOSS].height;

    // 計算圖片縮放後的寬高
    float drawWidth = texWidth * scale;
    float drawHeight = texHeight * scale;

    // 計算圖片左上角座標，讓圖片中心對齊格子中心
    float drawX = bounds.x + (bounds.width - drawWidth) / 2;
    float drawY = bounds.y + (bounds.height - drawHeight) / 2;

    // 畫 Boss 圖
    DrawTextureEx(
        monsters[MONSTER_BOSS],
        (Vector2) {
        drawX, drawY
    },
        0.0f,
        scale,
        WHITE
    );

    // 顯示資訊（滑鼠碰到才畫數值）
    if (CheckCollisionPointRec(GetMousePosition(), self->bounds)) {
        EnemyStats* boss = &enemyInfo[self->row][self->col].stats;
        int fontSize = 16;
        // 用 drawX, drawY, drawWidth, drawHeight 作為新的座標依據
        DrawBoldText(TextFormat("%d", boss->atk), drawX + 2, drawY + 2, fontSize, YELLOW); // 左上角
        DrawBoldText(TextFormat("%d", boss->currentHp), drawX + 2, drawY + drawHeight - fontSize - 2, fontSize, RED); // 左下角
        DrawBoldText(TextFormat("%d", boss->def), drawX + drawWidth - fontSize - 2, drawY + drawHeight - fontSize - 2, fontSize, YELLOW); // 右下角
    }
}


void OnInteractBoss(CardBase* self) {
    PlayerStats* player = GetPlayerStats();
    EnemyInfo* bossInfoPtr = &enemyInfo[self->row][self->col];
    EnemyStats* boss = &bossInfoPtr->stats;

    bool bossDead = AttackEnemy(player, boss);  // 玩家攻擊 Boss

    if (bossDead) {
        ReplaceCardWithPortal(self->indexInArray, true); // Boss 死了 → 換成空卡
        KillBoss(); // 更新狀態為死亡
        AbleToReveal();
        UpdateVisibleBufferCounts();
        ApplyBuffsToVisibleEnemies();
        printf("BOSS DEFEATED!\n");
    } else {
        UpdateBossAction(); // Boss 活著 → 進行行動（CD、增益、攻擊玩家）
    }
}