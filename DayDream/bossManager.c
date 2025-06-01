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
#include "itemUse.h"
#include <string.h>
#include "playerUI.h"
static int bossCD = 3;             // 初始冷卻：第一回合增益，下一回合開始攻擊
static bool bossAlive = true;     // 用來判斷 Boss 是否還活著
static int CDcount = 0;

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
            boss->bonusDef += 2;
            boss->def = boss->baseDef + boss->bonusDef;
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
    EnemyStats* boss = &enemyInfo[self->row][self->col].stats;
    int fontSize = 16;
    // 用 drawX, drawY, drawWidth, drawHeight 作為新的座標依據
    DrawBoldText(TextFormat("%d", boss->atk), drawX + 2, drawY + 2, fontSize, YELLOW, 1); // 左上角
    DrawBoldText(TextFormat("%d", boss->currentHp), drawX + 2, drawY + drawHeight - fontSize - 2, fontSize, RED, 1); // 左下角
    DrawBoldText(TextFormat("%d", boss->def), drawX + drawWidth - fontSize - 2, drawY + drawHeight - fontSize - 2, fontSize, YELLOW, 1); // 右下角
    
    int cdFontSize = 40;
    int cdPaddingY = 30; // CD 距離 Boss 圖下方的距離
    int cdPosX = bounds.x + bounds.width / 2 - MeasureText(TextFormat("%d", GetBossCD()), cdFontSize) / 2;
    int cdPosY = bounds.y + bounds.height + cdPaddingY;

    DrawBoldText(TextFormat("%d", GetBossCD()), cdPosX, cdPosY, cdFontSize, PURPLE, 2);
}


void OnInteractBoss(CardBase* self) {
    
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        printf("show boss detial");
        ToggleBossMessage(
            "Boss Details:\n"
            "- Boss cooldown: 3\n"
            "- First cooldown ends -> Buffs all monsters.\n"
            "- Subsequent cooldowns -> Increases its own attack.\n"
            "- HP below half -> Attacks the player."
        );
    }
    

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        printf("attack");
        PlayerStats* player = GetPlayerStats();
        EnemyInfo* bossInfoPtr = &enemyInfo[self->row][self->col];
        EnemyStats* boss = &bossInfoPtr->stats;

        bool bossDead = AttackEnemy(player, boss);

        if (bossDead) {
            ReplaceCardWithEmpty(self->indexInArray, true);
            KillBoss();
            AbleToReveal();
            UpdateVisibleBufferCounts();
            ApplyBuffsToVisibleEnemies();
            printf("BOSS DEFEATED!\n");

            // 關掉訊息
            bossMessage[0] = '\0';
            bossMessageVisible = false;
        } else {
            UpdateBossAction();
        }
    }
}


void ToggleBossMessage(const char* text) {
    if (bossMessageVisible) {
        bossMessage[0] = '\0';   // 關掉訊息
        bossMessageVisible = false;
    } else {
        snprintf(bossMessage, sizeof(bossMessage), "%s", text); // 設訊息
        bossMessageVisible = true;
    }
}


void DrawBossMessage() {
    if (bossMessageVisible && bossMessage[0] != '\0') {
        int fontSize = 20;
        int lineSpacing = 32;
        int padding = 20; // 內邊距
        int borderThickness = 4; // 框邊寬度

        // 🧩 先抓最大行長
        int maxLineWidth = 0;
        const char* start = bossMessage;
        while (*start) {
            const char* end = strchr(start, '\n');
            if (!end) end = start + strlen(start);

            char line[256] = {0};
            strncpy(line, start, end - start);
            line[end - start] = '\0';

            int lineWidth = MeasureText(line, fontSize);
            if (lineWidth > maxLineWidth) {
                maxLineWidth = lineWidth;
            }

            if (*end == '\n') start = end + 1;
            else break;
        }

        // 總行數
        int lineCount = 1;
        for (const char* p = bossMessage; *p; ++p) {
            if (*p == '\n') lineCount++;
        }

        // 📐 框大小
        int boxWidth = maxLineWidth + padding * 2;
        int boxHeight = fontSize * lineCount + lineSpacing * (lineCount - 1) + padding * 2;

        // 🧩 Boss 中心位置
        int bossRow = 2;
        int bossCol = 2;
        float bossX = BOARD_START_X + TILE_GAP + bossCol * (TILE_SIZE + TILE_GAP);
        float bossY = BOARD_START_Y + TILE_GAP + bossRow * (TILE_SIZE + TILE_GAP);
        float centerX = bossX + TILE_SIZE / 2;
        float centerY = bossY; // 頭頂

        int boxX = centerX - boxWidth / 2;
        int boxY = centerY - boxHeight - 50; // 頭頂上 50 px

        // 🎨 畫黑底
        DrawRectangle(boxX, boxY, boxWidth, boxHeight, BLACK);

        // 🎨 畫白邊
        DrawRectangleLinesEx(
            (Rectangle){ boxX - borderThickness / 2.0f, boxY - borderThickness / 2.0f, boxWidth + borderThickness, boxHeight + borderThickness },
            borderThickness,
            WHITE
        );

        // 📝 畫文字（每行居中）
        int textY = boxY + padding;
        start = bossMessage;
        while (*start) {
            const char* end = strchr(start, '\n');
            if (!end) end = start + strlen(start);

            char line[256] = {0};
            strncpy(line, start, end - start);
            line[end - start] = '\0';

            int lineWidth = MeasureText(line, fontSize);
            int textX = boxX + (boxWidth - lineWidth) / 2; // 文字居中

            DrawText(line, textX, textY, fontSize, WHITE);
            textY += fontSize + lineSpacing;

            if (*end == '\n') start = end + 1;
            else break;
        }
    }
}
