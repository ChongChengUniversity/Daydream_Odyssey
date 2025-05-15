// shopicon.c
#include "shopicon.h"        // 此模組對外的函式宣告
#include "assetManager.h"    // 使用 TEX_SHOP_ICON（商店圖示）
#include "audioManager.h"    // 播放點擊音效
#include "stateController.h" // 使用 ChangeState() 切換狀態
#include "state_shop.h"      // 切換到商店狀態所需
#include <stdbool.h>         // 使用 bool 型別


#define SHOP_ICON_SIZE 80 // 商店圖示的邊長尺寸（寬高相同）

static Rectangle shopIconBox;            // 商店圖示的區域（碰撞判定與繪製位置）
static bool isReturningFromShop = false; // 管理從商店返回的狀態旗標

void SetReturningFromShop(bool flag) { isReturningFromShop = flag; }

bool IsReturningFromShop(void) { return isReturningFromShop; }

// 初始化商店圖示位置與大小（畫面右上角）
void InitShopIcon(void) {
  shopIconBox.x = GetScreenWidth() - SHOP_ICON_SIZE - 20;
  shopIconBox.y = 20;
  shopIconBox.width = SHOP_ICON_SIZE;
  shopIconBox.height = SHOP_ICON_SIZE;
}

// 繪製商店圖示（含背景框與圖示圖片）
void DrawShopIcon(void) {
  // 背景方框
  DrawRectangleRec(shopIconBox, DARKGRAY);     // 深灰底色
  DrawRectangleLinesEx(shopIconBox, 2, WHITE); // 白框邊界

  // 商店圖示圖片，縮放至合適大小並置中
  float scale = (float)SHOP_ICON_SIZE / TEX_SHOP_ICON.width;
  Vector2 pos = {
      shopIconBox.x + (SHOP_ICON_SIZE - TEX_SHOP_ICON.width * scale) / 2,
      shopIconBox.y + (SHOP_ICON_SIZE - TEX_SHOP_ICON.height * scale) / 2};

  DrawTextureEx(TEX_SHOP_ICON, pos, 0.0f, scale, WHITE); // 貼上圖示
}

// 更新商店圖示邏輯：偵測滑鼠點擊進入商店狀態
void UpdateShopIcon(void) {
  Vector2 mouse = GetMousePosition(); // 取得滑鼠目前位置

  if (CheckCollisionPointRec(mouse, shopIconBox)) // 如果滑鼠在圖示範圍內
  {
    // 畫出 hover 效果
    DrawRectangleLinesEx(shopIconBox, 3, YELLOW);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // 點擊左鍵
    {
      GamePlaySound(SOUND_ONE);   // 點擊音效
      SetReturningFromShop(true); // 設定旗標為從商店回來
      ChangeState(SHOP);          // 切換到商店狀態
    }
  }
}