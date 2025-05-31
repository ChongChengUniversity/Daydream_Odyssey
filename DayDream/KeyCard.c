// KeyCard.c
#include "KeyCard.h"
#include "config.h"
#include <stdlib.h>
#include "stateController.h"
#include "assetManager.h"
#include "levelManager.h"
#include "CardManager.h"
#include "story.h"     // 引入 keyDialogueTriggered 的 extern 宣告)
#include "dialogues.h" // 引入 所有對話文本的 extern 宣告)

static void ResetKey(CardBase *self)
{
    self->isRevealed = false;
}

static void DrawKey(CardBase *self)
{
    if (!self->isRevealed) {
        DrawRectangleLinesEx(self->bounds, 2.0f, WHITE);
        return;
    }

    DrawTextureEx(textures[TEXTURE_KEY], (Vector2){self->bounds.x, self->bounds.y}, 0.0f,
        (float)TILE_SIZE / textures[TEXTURE_DOOR].width, WHITE);
}

static void OnRevealKey(CardBase *self)
{
    self->isRevealed = true;
}

static void OnInteractKey(CardBase *self)
{
    if (self->isRevealed)
    {
        AcquireKey(); // hasKey = true
        ReplaceCardWithEmpty(self->indexInArray, true);

        // 根據當前關卡觸發不同的鑰匙對話
        int currentLvl = GetCurrentLevel();
        if (currentLvl >= 1 && currentLvl <= 10 && !keyDialogueTriggered[currentLvl - 1]) { // 陣列索引從0開始，並檢查範圍
            switch (currentLvl) {
                case 1: StartDialogue(keyAcquiredDialogue_L1, keyAcquiredDialogue_L1_Count); break;
                case 2: StartDialogue(keyAcquiredDialogue_L2, keyAcquiredDialogue_L2_Count); break;
                case 3: StartDialogue(keyAcquiredDialogue_L3, keyAcquiredDialogue_L3_Count); break;
                case 4: StartDialogue(keyAcquiredDialogue_L4, keyAcquiredDialogue_L4_Count); break;
                case 5: StartDialogue(keyAcquiredDialogue_L5, keyAcquiredDialogue_L5_Count); break;
                case 6: StartDialogue(keyAcquiredDialogue_L6, keyAcquiredDialogue_L6_Count); break;
                case 7: StartDialogue(keyAcquiredDialogue_L7, keyAcquiredDialogue_L7_Count); break;
                case 8: StartDialogue(keyAcquiredDialogue_L8, keyAcquiredDialogue_L8_Count); break;
                case 9: StartDialogue(keyAcquiredDialogue_L9, keyAcquiredDialogue_L9_Count); break;
                case 10: StartDialogue(keyAcquiredDialogue_L10, keyAcquiredDialogue_L10_Count); break;
            }
            keyDialogueTriggered[currentLvl - 1] = true;
        }
    }
}

CardBase *CreateKeyCard(float x, float y, int index, int row, int col)
{ 
    CardBase *card = malloc(sizeof(CardBase));
    if (!card)return NULL;

    card->bounds = (Rectangle){x, y, TILE_SIZE, TILE_SIZE};
    card->isRevealed = false;
    card->reset = ResetKey;
    card->draw = DrawKey;
    card->onReveal = OnRevealKey;
    card->onInteract = OnInteractKey;
    card->indexInArray = index;
    card->row = row;
    card->col = col;
    card->type = TYPE_KEY;
    return card;
}