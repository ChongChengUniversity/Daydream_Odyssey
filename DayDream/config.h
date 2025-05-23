// config.h
#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define COLS 5
#define ROWS 5
#define TOTAL_CARDS (COLS * ROWS)

#define TILE_SIZE 100
#define TILE_GAP 10

#define BOARD_WIDTH  (COLS * TILE_SIZE + (COLS + 1) * TILE_GAP)
#define BOARD_HEIGHT (ROWS * TILE_SIZE + (ROWS + 1) * TILE_GAP)

#define BOARD_START_X ((SCREEN_WIDTH - BOARD_WIDTH) / 2)
#define BOARD_START_Y ((SCREEN_HEIGHT - BOARD_HEIGHT) / 2)
