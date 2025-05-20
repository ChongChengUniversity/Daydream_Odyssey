// game.c
#include "game.h"
#include "stateController.h"
#include "audioManager.h"
#include "assetManager.h"

#include"inventory.h"
#include "money.h" // 金幣系統

void GameStartup() {
    InitAssetManager(); // 初始化素材
    InitAudioManager(); // 初始化音效
    InitInventory(); // 初始化背包
    InitMoneySystem();  // 初始化金幣系統
    PlayMusicStream(music[MUSIC_ONE]);
    GOTO(MAIN_MENU);
}

void GameShutdown() {
    ShutdownAssetManager(); // 卸載素材
    ShutdownAudioManager(); // 卸載音效
    ShutdownMoneySystem();  // 釋放金幣系統資源
}
