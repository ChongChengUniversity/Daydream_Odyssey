// game.c
#include "game.h"
#include "stateController.h"
#include "audioManager.h"
#include "assetManager.h"

void GameStartup() {
    InitAssetManager(); // 初始化素材
    InitAudioManager(); // 初始化音效
    PlayMusicStream(music[MUSIC_ONE]);
    GOTO(MAIN_MENU);
}

void GameShutdown() {
    ShutdownAssetManager(); // 卸載素材
    ShutdownAudioManager(); // 卸載音效
}
