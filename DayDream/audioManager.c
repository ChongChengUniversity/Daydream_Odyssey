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

    
    sounds[SOUND_ONE] = LoadSound("assets/music/click.wav");    // 點擊音效
    sounds[SOUND_TWO] = LoadSound("assets/music/bell.mp3");    // 爆炸音效
    sounds[SOUND_THREE] = LoadSound("assets/music/coin.mp3"); // 撿金幣音效
    sounds[SOUND_FOUR] = LoadSound("assets/music/fail.mp3");    // 購買失敗
    sounds[SOUND_FIVE] = LoadSound("assets/music/success.mp3"); // 購買成功
    sounds[SOUND_SIX] = LoadSound("assets/music/ice.mp3"); // 時間卷軸
    sounds[SOUND_SEVEN] = LoadSound("assets/music/shield.mp3"); // 盾卷軸
    sounds[SOUND_EIGHT] = LoadSound("assets/music/boss.mp3"); //BOSS
    sounds[SOUND_NINE] = LoadSound("assets/music/opendoor.mp3"); // 開門
    sounds[SOUND_TEN] = LoadSound("assets/music/magic.mp3"); // 法術
    sounds[SOUND_ELEVEN] = LoadSound("assets/music/attack.mp3"); // 普攻
    sounds[SOUND_TWELVE] = LoadSound("assets/music/drink.mp3"); // 血瓶

    // 載入一種背景音樂流（支援長時間播放）
    music[MUSIC_ONE] = LoadMusicStream("assets/music/game_music.mp3");
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