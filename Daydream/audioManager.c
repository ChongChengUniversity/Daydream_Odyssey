#include "raylib.h"
#include "audioManager.h"


bool isSoundEnabled = true;   // 真正定義：只出現在這個 .c 裡一次
bool isMusicEnabled = true;

Sound sounds[MAX_SOUNDS];
Music music[MAX_MUSIC];

void InitAudioManager()
{
    InitAudioDevice();

    sounds[SOUND_ONE] = LoadSound("assets/click.wav");
    sounds[SOUND_TWO] = LoadSound("assets/explosion.wav");
    sounds[SOUND_THREE] = LoadSound("assets/pickupCoin.wav");

    music[MUSIC_ONE] = LoadMusicStream("assets/8-bit-game-158815.mp3");
}

void ShutdownAudioManager()
{
    for (int i = 0; i < MAX_SOUNDS; i++) {
        UnloadSound(sounds[i]);
    }

    StopMusicStream(music[MUSIC_ONE]);
    UnloadMusicStream(music[MUSIC_ONE]);

    CloseAudioDevice();
}

void GamePlaySound(int sound) { //傳入enum 就是打程式的時候是打英文字 但傳入實際是int
    if (isSoundEnabled) {
        PlaySound(sounds[sound]); //sound是儲存sound的陣列
    }
}