// state_shop.c
#include "audioManager.h"    // 播放音效
#include "config.h"          // 螢幕寬度高度等常數（如 SCREEN_WIDTH）
#include "levelManager.h"    // 可用來調整商店內容依關卡變化（目前尚未使用）
#include "raylib.h"          // 圖形函式庫：繪圖、輸入、顏色等功能
#include "shopicon.h"        // 商店點擊
#include "stateController.h" // 狀態控制模組：切換遊戲狀態（例如回到遊玩中）


// 畫面標題與 UI 文字常數
static const char *labelTitle = "SHOP";
static const char *labelEnter = "[ENTER] Return to Game";
static const char *labelCoin = "COIN: 1543"; // 假設金幣值，未來可改為變數

// 商店格子排版設定：3x3 格子、每格尺寸、間距
#define SHOP_ROWS 3
#define SHOP_COLS 3
#define SHOP_ITEM_SIZE 160
#define SHOP_GAP 36

// 商店每格的位置與大小資訊（Rectangle 陣列）
static Rectangle shopItems[SHOP_ROWS * SHOP_COLS];
static const char *itemLabels[SHOP_ROWS * SHOP_COLS]; // 每格對應的文字標籤

// 進入商店狀態時呼叫：初始化每一格的顯示位置與販售項目（以第1層為例）
static void EnterShop() {
  // 計算整體寬高，使商店區域置中
  int totalWidth = SHOP_COLS * SHOP_ITEM_SIZE + (SHOP_COLS - 1) * SHOP_GAP;
  int totalHeight = SHOP_ROWS * SHOP_ITEM_SIZE + (SHOP_ROWS - 1) * SHOP_GAP;
  int startX = SCREEN_WIDTH / 2 - totalWidth / 2;
  int startY = SCREEN_HEIGHT / 2 - totalHeight / 2 + 40;

  // 定義第1層的商品內容（固定3裝備＋2欄位）
  itemLabels[0] = "Head Gear Lv1";
  itemLabels[1] = "Body Armor Lv1";
  itemLabels[2] = "Hand Guard Lv1";
  itemLabels[3] = "Slot +1";
  itemLabels[4] = "Slot +1";

  // 剩餘格子設為空（未販售）
  for (int i = 5; i < SHOP_ROWS * SHOP_COLS; ++i)
    itemLabels[i] = "-"; // 空格子

  // 計算每一格的位置，存在 shopItems 陣列
  for (int row = 0; row < SHOP_ROWS; ++row) {
    for (int col = 0; col < SHOP_COLS; ++col) {
      int index = row * SHOP_COLS + col;
      shopItems[index] = (Rectangle){startX + col * (SHOP_ITEM_SIZE + SHOP_GAP),
                                     startY + row * (SHOP_ITEM_SIZE + SHOP_GAP),
                                     SHOP_ITEM_SIZE, SHOP_ITEM_SIZE};
    }
  }
}

// 處理商店邏輯：偵測是否按下 ENTER 返回遊戲
static void UpdateShop() {
  if (IsKeyPressed(KEY_ENTER)) {
    GamePlaySound(SOUND_ONE);   // 播放音效
    SetReturningFromShop(true); // 設定旗標：我們是從商店回來的
    GOTO(PLAYING);              // 切換回遊玩中狀態
  }
}

// 畫出商店畫面內容
static void RenderShop() {
  ClearBackground((Color){24, 66, 42, 255}); // 深綠背景

  // 畫上方橫條與標題
  DrawRectangle(0, 0, SCREEN_WIDTH, 80, (Color){193, 117, 56, 255});
  DrawText(labelTitle, SCREEN_WIDTH / 2 - MeasureText(labelTitle, 48) / 2, 20,
           48, YELLOW);
  DrawText(labelCoin, SCREEN_WIDTH - 200, 30, 24, GOLD);

  // 繪製所有商店格子
  for (int i = 0; i < SHOP_ROWS * SHOP_COLS; ++i) {
    DrawRectangleRounded(shopItems[i], 0.1f, 12, (Color){245, 199, 110, 255});
    DrawRectangleRoundedLines(shopItems[i], 0.1f, 12, BROWN);

    // 顯示物品文字
    if (itemLabels[i]) {
      int textWidth = MeasureText(itemLabels[i], 18);
      DrawText(itemLabels[i],
               shopItems[i].x + SHOP_ITEM_SIZE / 2 - textWidth / 2,
               shopItems[i].y + SHOP_ITEM_SIZE / 2 - 10, 18, DARKBROWN);
    }
  }

  // 下方提示文字：「按 ENTER 返回遊戲」
  DrawText(labelEnter, SCREEN_WIDTH / 2 - MeasureText(labelEnter, 20) / 2,
           SCREEN_HEIGHT - 50, 20, LIGHTGRAY);
}

static void ExitShop() {} // 離開商店狀態時執行（目前沒特別要清理的）

const GameState STATE_SHOP = {
    .enter = EnterShop,   // 進入商店狀態時要做的事
    .update = UpdateShop, // 每幀更新邏輯（例如偵測鍵盤）
    .render = RenderShop, // 每幀畫畫面
    .exit = ExitShop};    // 離開商店狀態時要清理的事（目前無）