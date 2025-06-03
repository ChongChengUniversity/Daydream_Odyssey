#pragma once

#define MAX_SOUNDS 3 //用途:用這個常數來定義陣列大小
typedef enum {
    SOUND_ONE = 0, //先設好編號，GameStartUP時再Load
    SOUND_TWO,
    SOUND_THREE
} sound_asset;


#define MAX_MUSIC 1
typedef enum {
    MUSIC_ONE = 0
} music_asset;


Sound sounds[MAX_SOUNDS];
Music music[MAX_MUSIC];


bool isSoundEnabled;
bool isMusicEnabled;

void GamePlaySound(int sound);

void InitAudioManager();
void ShutdownAudioManager();