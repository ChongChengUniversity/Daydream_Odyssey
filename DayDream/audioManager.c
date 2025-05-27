// audioManager.c

#include "raylib.h"       // 引入 Raylib 函式庫，提供音效/音樂/音訊裝置功能
#include "audioManager.h" // 引入自己寫的音訊管理標頭檔

bool isSoundEnabled = true; // 預設開啟音效功能 // 真正定義：只出現在這個 .c 裡一次
bool isMusicEnabled = true; // 預設開啟背景音樂功能

Sound sounds[MAX_SOUNDS]; 
Music music[MAX_MUSIC];   

void InitAudioManager()
{
    InitAudioDevice(); // 初始化音訊裝置（Raylib 必需呼叫）

    // 載入三種音效資源並存入陣列中
    sounds[SOUND_ONE] = LoadSound("assets/music/click.wav");        // 點擊音效
    sounds[SOUND_TWO] = LoadSound("assets/music/explosion.wav");    // 爆炸音效
    sounds[SOUND_THREE] = LoadSound("assets/music/pickupCoin.wav"); // 撿金幣音效

    // 載入一種背景音樂流（支援長時間播放）
    music[MUSIC_ONE] = LoadMusicStream("assets/music/8-bit-game-158815.mp3");
}

void ShutdownAudioManager()
{
    for (int i = 0; i < MAX_SOUNDS; i++)
    {
        UnloadSound(sounds[i]); // 卸載每一個音效，釋放資源
    }

    StopMusicStream(music[MUSIC_ONE]);   // 停止音樂播放
    UnloadMusicStream(music[MUSIC_ONE]); // 卸載音樂資源

    CloseAudioDevice(); // 關閉 Raylib 的音訊裝置（乾淨收尾）
}

void GamePlaySound(int sound)
{
    // 如果音效功能被開啟
    if (isSoundEnabled) // 傳入enum 就是打程式的時候是打英文字 但傳入實際是int
    {
        PlaySound(sounds[sound]); // 播放指定索引的音效
    }
}
