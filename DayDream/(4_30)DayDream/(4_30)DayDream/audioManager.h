#pragma once

#define MAX_SOUNDS 3 //�γ~:�γo�ӱ`�ƨөw�q�}�C�j�p
typedef enum {
    SOUND_ONE = 0, //���]�n�s���AGameStartUP�ɦALoad
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