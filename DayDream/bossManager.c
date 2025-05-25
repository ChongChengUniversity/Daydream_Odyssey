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


// 假設 BOSS 固定在地圖中央
#define BOSS_ROW 2
#define BOSS_COL 2

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
    card->reset = NULL; // 如有需求可以寫 ResetBoss
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
    DrawRectangleRec(bounds, (Color){100, 0, 150, 255});

    // 畫 Boss 圖示（用 normal 怪圖作為測試）
    DrawTextureEx(
        monsters[MONSTER_NORMAL],
        (Vector2){ bounds.x, bounds.y },
        0.0f,
        (float)TILE_SIZE / monsters[MONSTER_NORMAL].width,
        WHITE
    );

    // 抓對應 enemyInfo 中的 stats（依照卡片的格子位置）
    EnemyStats* boss = &enemyInfo[self->row][self->col].stats;

    // 滑鼠滑上去時顯示資訊
    if (CheckCollisionPointRec(GetMousePosition(), self->bounds)) {
        int fontSize = 16;
        DrawBoldText(TextFormat("%d", boss->atk), bounds.x + 2, bounds.y + 2, fontSize, YELLOW); // 攻擊
        DrawBoldText(TextFormat("%d", boss->currentHp), bounds.x + 2, bounds.y + bounds.height - fontSize - 2, fontSize, RED); // 血量
        DrawBoldText(TextFormat("%d", boss->def), bounds.x + bounds.width - fontSize - 2, bounds.y + bounds.height - fontSize - 2, fontSize, YELLOW); // 防禦
    }
}

void OnInteractBoss(CardBase* self) {
    PlayerStats* player = GetPlayerStats();
    EnemyInfo* bossInfoPtr = &enemyInfo[self->row][self->col];
    EnemyStats* boss = &bossInfoPtr->stats;

    bool bossDead = AttackEnemy(player, boss);  // 玩家攻擊 Boss

    if (bossDead) {
        ReplaceCardWithEmpty(self->indexInArray, true); // Boss 死了 → 換成空卡
        KillBoss(); // 更新狀態為死亡
        AbleToReveal();
        UpdateVisibleBufferCounts();
        ApplyBuffsToVisibleEnemies();
        printf("BOSS DEFEATED!\n");
    } else {
        UpdateBossAction(); // Boss 活著 → 進行行動（CD、增益、攻擊玩家）
    }
}