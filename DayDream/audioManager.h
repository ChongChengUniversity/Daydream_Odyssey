// audioManager.h
#pragma once // 防止這個標頭檔被重複包含多次
#include "raylib.h"

#define MAX_SOUNDS 12// 定義最多 12 種音效
typedef enum
{
    SOUND_ONE = 0, // 音效索引 0：點擊音效
    SOUND_TWO,     // 音效索引 1：爆炸音效
    SOUND_THREE ,  // 音效索引 2：撿金幣音效
    SOUND_FOUR,    // 音效索引 3：購買失敗音效
    SOUND_FIVE,    // 音效索引 4：購買成功音效
    SOUND_SIX,     // 音效索引 5: 時間卷軸
    SOUND_SEVEN,   // 音效索引 6: 盾卷軸
    SOUND_EIGHT,   // 音效索引 7: 怪物
    SOUND_NINE,   // 音效索引 8: 開門
    SOUND_TEN,   // 音效索引 9: 法術
    SOUND_ELEVEN,   // 音效索引 10: 普攻
    SOUND_TWELVE,   // 音效索引 11: 血瓶


} sound_asset;     // 自訂 enum 型別表示音效資產

#define MAX_MUSIC 1 // 定義最多 1 種背景音樂
typedef enum
{
    MUSIC_ONE = 0 // 音樂索引 0
} music_asset;    // 自訂 enum 型別表示音樂資產

extern Sound sounds[MAX_SOUNDS]; // 聲明音效陣列（由 .c 檔定義）
extern Music music[MAX_MUSIC];   // 聲明音樂陣列（由 .c 檔定義）

extern bool isSoundEnabled; // 聲明是否啟用音效的布林變數
extern bool isMusicEnabled; // 聲明是否啟用音樂的布林變數

void GamePlaySound(int sound); // 播放指定音效的函式

void InitAudioManager();     // 初始化音訊系統的函式
void ShutdownAudioManager(); // 關閉音訊系統並釋放資源的函式