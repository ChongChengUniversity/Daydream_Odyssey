﻿// game.c
#include "game.h"
#include "stateController.h"
#include "audioManager.h"
#include "assetManager.h"
#include "inventory.h"
#include "money.h"
#include "equipmentSystem.h"  // 提供 InitAllEquipments()
#include "itemSystem.h"
#include "state_shop.h"       // 提供 InitShopState()

void GameStartup() {
    InitAssetManager(); // load assets
    InitAudioManager(); // load audios
    InitInventory(); // load backpack assets
    InitMoneySystem();
    InitAllEquipments();
    InitAllItems();
    PlayMusicStream(music[MUSIC_ONE]);

    SetMusicVolume(music[MUSIC_ONE], 0.5f); // adjust the volume
    SetSoundVolume(sounds[SOUND_ONE], 0.4f); // adjust the volume
    SetSoundVolume(sounds[SOUND_TWO], 0.2f); // adjust the volume
    SetSoundVolume(sounds[SOUND_THREE], 0.4f); // adjust the volume

    GOTO(MAIN_MENU);
}

void GameShutdown() {
    ShutdownAssetManager(); // unload assets
    ShutdownAudioManager(); // unload audios
    ShutdownMoneySystem();
    // unload inventory?
}
