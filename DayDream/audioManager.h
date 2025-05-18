#pragma once
#include "raylib.h"

#define MAX_SOUNDS 3
typedef enum {
    SOUND_ONE = 0,
    SOUND_TWO,
    SOUND_THREE
} sound_asset;


#define MAX_MUSIC 1
typedef enum {
    MUSIC_ONE = 0
} music_asset;


extern Sound sounds[MAX_SOUNDS];
extern Music music[MAX_MUSIC];


extern bool isSoundEnabled;
extern bool isMusicEnabled;

void GamePlaySound(int sound);

void InitAudioManager();
void ShutdownAudioManager();