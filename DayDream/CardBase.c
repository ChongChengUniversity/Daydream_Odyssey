// CardBase.c（新增）
#include "CardBase.h"
#include "config.h"  // for BOARD_START_X, TILE_SIZE, etc.
#include <stddef.h>
#include "CardManager.h"

GridPos GetCardGridPosition(Rectangle bounds) {
    GridPos pos;
    int start_x = BOARD_START_X;
    int start_y = BOARD_START_Y;
    pos.col = (bounds.x - start_x - TILE_GAP) / (TILE_SIZE + TILE_GAP);
    pos.row = (bounds.y - start_y - TILE_GAP) / (TILE_SIZE + TILE_GAP);
    return pos;
}

// 反推：用 row col 得到卡片 index
int GetCardIndexByGridPos(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return -1; // 超出範圍
    }
    return row * COLS + col;
}

// 反推：用 row col 得到卡片指標
CardBase* GetCardAt(int row, int col) {
    int index = GetCardIndexByGridPos(row, col);
    if (index == -1) return NULL;
    return cards[index];
}