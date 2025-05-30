// backpackicon.c
#include "backpackicon.h"
#include "raylib.h"
#include "config.h"
#include "inventory.h"
#include "CharacterStats.h"
#include "equipmentSystem.h"
#include "assetManager.h"

static Vector2 equipSlotPositions[5];

// 狀態變數、背包欄和裝備欄圖片資源
bool isBackpackOpen = false;
Texture2D backpackMenu;
Texture2D backpackScreen;
Texture2D exitButton;
Texture2D equipmentScreen;
Texture2D nextButton;
Texture2D backButton;

// 按鈕和畫面位置
Rectangle backpackMenuRect;
Rectangle backpackScreenRect;
Rectangle exitButtonRect;
Rectangle nextButtonRect;
Rectangle backButtonRect;
// 不用equipmentScreenRect?

static BackpackPage currentPage = SCREEN_BACKPACK;

// 縮放比例
float menuScale = 0.4f; // 背包按鈕縮放比例
float screenScale = 1.25f; // 背包畫面縮放比例
float buttonScale = 0.75f; // 上下頁按鈕縮放比例
float exitScale = 0.4f; // screen的退出按鈕縮放比例
float closeScale = 0.25f; // infocard退出按鈕縮放比例

// 裝備介紹卡
extern Texture2D EQUIP_INFO_CARD;  // info 背景圖
extern Texture2D CLOSE_BUTTON_IMG; // 關閉按鈕圖

static bool isInfoVisible = false;
static EquipSlot selectedSlot = -1;
static Rectangle infoCardRect;
static Rectangle closeButtonRect;

// 檢查背包開啟狀態（供其他模組檢查）
bool IsBackpackOpen() {
    return isBackpackOpen;
}

// 獲取背包畫面區域（Rectangle）
Rectangle GetBackpackScreenRect(void) {
    return backpackScreenRect;
}

BackpackPage GetCurrentBackpackPage(void) {
    return currentPage;
}

void SetCurrentBackpackPage(BackpackPage page) {
    currentPage = page;
}

void InitBackpackIcon(void) {
    // 載入圖片
    backpackMenu = LoadTexture("assets/backpack_menu.png");
    backpackScreen = LoadTexture("assets/backpack_screen.png");
    equipmentScreen = LoadTexture("assets/equipment_screen.png");
    exitButton = LoadTexture("assets/exit.png");
    backButton = LoadTexture("assets/back.png");
    nextButton = LoadTexture("assets/next.png");
    EQUIP_INFO_CARD = LoadTexture("assets/infocard.png");
    CLOSE_BUTTON_IMG = LoadTexture("assets/closeinfo.png");

    // 設定背包按鈕和畫面位置
    backpackMenuRect = (Rectangle){
        SCREEN_WIDTH - (backpackMenu.width * menuScale) - 10,
        SCREEN_HEIGHT - (backpackMenu.height * menuScale) - 10,
        backpackMenu.width * menuScale,
        backpackMenu.height * menuScale};

    float scaledScreenWidth = backpackScreen.width * screenScale;
    float scaledScreenHeight = backpackScreen.height * screenScale;

    backpackScreenRect = (Rectangle){(SCREEN_WIDTH - scaledScreenWidth) / 2, (SCREEN_HEIGHT - scaledScreenHeight) / 2, scaledScreenWidth, scaledScreenHeight};

    equipSlotPositions[0] = (Vector2){backpackScreenRect.x + 153,  backpackScreenRect.y + 94};   // Head
    equipSlotPositions[1] = (Vector2){backpackScreenRect.x + 307, backpackScreenRect.y + 170};   // Body
    equipSlotPositions[2] = (Vector2){backpackScreenRect.x + 463, backpackScreenRect.y + 94};   // Hand
    equipSlotPositions[3] = (Vector2){backpackScreenRect.x + 153,  backpackScreenRect.y + 248};  // Leg
    equipSlotPositions[4] = (Vector2){backpackScreenRect.x + 463, backpackScreenRect.y + 248};   // Accessory

    exitButtonRect = (Rectangle){
        backpackScreenRect.x + backpackScreenRect.width - exitButton.width * exitScale - 55,
        backpackScreenRect.y + 55,
        exitButton.width * exitScale,
        exitButton.height * exitScale
    };

    nextButtonRect = (Rectangle){
        backpackScreenRect.x + backpackScreenRect.width - (nextButton.width * buttonScale) + 40,
        backpackScreenRect.y + backpackScreenRect.height - (nextButton.height * buttonScale) - 230,
        nextButton.width * buttonScale,
        nextButton.height * buttonScale};

    backButtonRect = (Rectangle){
        backpackScreenRect.x - 40,
        backpackScreenRect.y + backpackScreenRect.height - (backButton.height * buttonScale) - 230,
        backButton.width * buttonScale,
        backButton.height * buttonScale};
}

void UpdateBackpackIcon(Vector2 mousePos) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (isBackpackOpen) {
            if (CheckCollisionPointRec(mousePos, exitButtonRect)) {
                isBackpackOpen = false;
                currentPage = SCREEN_BACKPACK;
                return;
            }
            if (currentPage == SCREEN_BACKPACK && CheckCollisionPointRec(mousePos, nextButtonRect)) {
                currentPage = SCREEN_EQUIPMENT;
                return;
            }
            if (currentPage == SCREEN_EQUIPMENT && CheckCollisionPointRec(mousePos, backButtonRect)) {
                currentPage = SCREEN_BACKPACK;
                return;
            }
        } else {
            if (CheckCollisionPointRec(mousePos, backpackMenuRect)) {
                isBackpackOpen = true;
            }
        }
    }
}

// 裝備欄位繪製
static void DrawEquipmentSlots(Rectangle screenRect) {
    float cellSize = 81;
    Vector2 slotPositions[5] = {
        {screenRect.x + 155,  screenRect.y + 210},   // Head（左上）
        {screenRect.x + 310, screenRect.y + 290},  // Body（中）
        {screenRect.x + 465, screenRect.y + 210},   // Hand（右上）
        {screenRect.x + 155,  screenRect.y + 365},  // Leg（左下）
        {screenRect.x + 465, screenRect.y + 365}   // Accessory（右下）
    };
    const char *slotLabels[5] = {"Head", "Body", "Hand", "Leg", "Accessory"};

    for (int i = 0; i < 5; i++) {
        DrawText(slotLabels[i], slotPositions[i].x, slotPositions[i].y - 20, 20, DARKGRAY);
    }

    DrawEquippedItems(screenRect); // 呼叫畫圖
}

// 主角能力值顯示
static void DrawPlayerStats(Rectangle screenRect) {
    PlayerStats* stats = GetPlayerStats();

    Vector2 statPositions[4] = {
        {screenRect.x + 140,  screenRect.y + 390},  // ATK
        {screenRect.x + 390, screenRect.y + 390},  // MATK
        {screenRect.x + 140,  screenRect.y + 453},  // DEF
        {screenRect.x + 390, screenRect.y + 453}   // MAX HP
    };

    const char* labels[4] = {"ATK", "MATK", "DEF", "MAX HP"};
    int values[4] = {
        stats->atk,
        stats->magic,
        stats->def,
        stats->maxHp
    };

    for (int i = 0; i < 4; i++) {
        DrawText(TextFormat("%s: %d", labels[i], values[i]), statPositions[i].x, statPositions[i].y, 25, DARKBROWN);
    }
}

void DrawBackpackIcon(void) {
    // 加上hover效果
    Vector2 mouse = GetMousePosition();

    if (!isBackpackOpen) {
        // 背包關閉狀態，只畫圖示按鈕
        DrawTextureEx(backpackMenu, (Vector2){backpackMenuRect.x, backpackMenuRect.y}, 0.0f, menuScale, WHITE);
        return;
    }

    if (currentPage == SCREEN_BACKPACK) {
        // 背包畫面、道具與 next 按鈕
        DrawTextureEx(backpackScreen, (Vector2){backpackScreenRect.x, backpackScreenRect.y}, 0.0f, screenScale, WHITE);
        DrawInventoryUI((Vector2){backpackScreenRect.x + 20, backpackScreenRect.y + 50}, backpackScreenRect);
        Color nextButtonTint = CheckCollisionPointRec(mouse, nextButtonRect) ? (Color){255, 255, 255, 200} : WHITE;
        DrawTextureEx(nextButton, (Vector2){nextButtonRect.x, nextButtonRect.y}, 0.0f, buttonScale, nextButtonTint);
    } else {
        // 裝備畫面、slot與 back 按鈕
        DrawTextureEx(equipmentScreen, (Vector2){backpackScreenRect.x, backpackScreenRect.y}, 0.0f, screenScale, WHITE);
        DrawEquipmentSlots(backpackScreenRect);
        DrawPlayerStats(backpackScreenRect);
        Color backButtonTint = CheckCollisionPointRec(mouse, backButtonRect) ? (Color){255, 255, 255, 200} : WHITE;
        DrawTextureEx(backButton, (Vector2){backButtonRect.x, backButtonRect.y}, 0.0f, buttonScale, backButtonTint);

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            for (int i = 0; i < EQUIP_SLOT_COUNT; i++) {
                EquipmentData* eq = GetEquippedInSlot(i);
                if (eq && eq->image) {
                    Rectangle slotRect = (Rectangle){equipSlotPositions[i].x, equipSlotPositions[i].y, eq->image->width * 0.3f, eq->image->height * 0.3f};
                    if (CheckCollisionPointRec(mousePos, slotRect)) {
                        isInfoVisible = true;
                        selectedSlot = i;

                        // 設定卡片和關閉鈕位置
                        infoCardRect = (Rectangle){SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 120, 360, 240};
                        closeButtonRect = (Rectangle){
                            infoCardRect.x + infoCardRect.width - CLOSE_BUTTON_IMG.width * closeScale - 12,
                            infoCardRect.y + 12,
                            CLOSE_BUTTON_IMG.width * closeScale,
                            CLOSE_BUTTON_IMG.height * closeScale
                        };
                        break;
                    }
                }
            }
        }

        if (isInfoVisible && selectedSlot >= 0) {
            EquipmentData* eq = GetEquippedInSlot(selectedSlot);
            if (eq) {
                // 背景卡片
                DrawTexturePro(EQUIP_INFO_CARD, (Rectangle){ 0, 0, EQUIP_INFO_CARD.width, EQUIP_INFO_CARD.height}, infoCardRect, (Vector2){0, 0}, 0.0f, WHITE);

                // 裝備名稱與能力值
                int fontSize = 18;
                int x = infoCardRect.x + 25;
                int y = infoCardRect.y + 50;

                DrawText(eq->name, x, y, 27, GOLD); y += 40;
                DrawText(TextFormat("ATK: %d", eq->atkPhysical), x, y, fontSize, WHITE); y += 25;
                DrawText(TextFormat("MATK: %d", eq->atkMagical), x, y, fontSize, WHITE); y += 25;
                DrawText(TextFormat("DEF: %d", eq->defValue), x, y, fontSize, WHITE); y += 25;
                DrawText(TextFormat("MAX HP: %d", eq->maxHP), x, y, fontSize, WHITE);

                // 畫關閉按鈕
                Vector2 mouse = GetMousePosition();
                bool hover = CheckCollisionPointRec(mouse, closeButtonRect);
                Color tint = hover ? (Color){255, 255, 255, 200} : WHITE;
                DrawTextureEx(CLOSE_BUTTON_IMG, (Vector2){closeButtonRect.x, closeButtonRect.y}, 0.0f, closeScale, tint);
                // 處理點擊關閉
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hover) {
                    isInfoVisible = false;
                    selectedSlot = -1;
                }
            }
        }
    }

    Color exitButtonTint = CheckCollisionPointRec(mouse, exitButtonRect) ? (Color){255, 255, 255, 200} : WHITE;
    DrawTextureEx(exitButton, (Vector2){exitButtonRect.x, exitButtonRect.y}, 0.0f, exitScale, exitButtonTint);
}

void ExitBackpackIcon(void) {
    UnloadTexture(backpackMenu);
    UnloadTexture(backpackScreen);
    UnloadTexture(equipmentScreen);
    UnloadTexture(exitButton);
    UnloadTexture(nextButton);
    UnloadTexture(backButton);
}
