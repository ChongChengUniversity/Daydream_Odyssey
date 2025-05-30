// state_main_menu.c
#include "raylib.h"
#include "stateController.h"
#include "config.h"
#include "audioManager.h"
#include "CharacterStats.h"

// ¹Ï¤ù¸ê·½
Texture2D menuBackground;
Texture2D buttonStart;
Texture2D buttonOptions;
Texture2D buttonExit;

// «ö¶s¦ì¸m
Rectangle rectStart;
Rectangle rectOptions;
Rectangle rectExit;

static void EnterMainMenu() {
    // e.g. play bgm, reset variables
    menuBackground = LoadTexture("assets/menu_background.png");
    buttonStart = LoadTexture("assets/menu_start.png");
    buttonOptions = LoadTexture("assets/menu_options.png");
    buttonExit = LoadTexture("assets/menu_exit.png");

    float scale = 0.8f;

    rectStart = (Rectangle){ SCREEN_WIDTH / 2 - buttonStart.width * scale / 2, 450, buttonStart.width * scale, buttonStart.height * scale };
    rectOptions = (Rectangle){ SCREEN_WIDTH / 2 - buttonOptions.width * scale / 2, 550, buttonOptions.width * scale, buttonOptions.height * scale };
    rectExit = (Rectangle){ SCREEN_WIDTH / 2 - buttonExit.width * scale / 2, 650, buttonExit.width * scale, buttonExit.height * scale };
}

static void UpdateMainMenu() {
    /*
    if (IsKeyPressed(KEY_N)) {
        GamePlaySound(SOUND_TWO);
        InitPlayerStats(); // ensure that player states won't reset in every level
        GOTO(PLAYING);
    }
    else if (IsKeyPressed(KEY_O)) {
        GamePlaySound(SOUND_TWO);
        GOTO(OPTION_MENU);
    }
    */

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, rectStart)) {
            GamePlaySound(SOUND_TWO);
            InitPlayerStats();
            GOTO(PLAYING);
        }
        else if (CheckCollisionPointRec(mouse, rectOptions)) {
            GamePlaySound(SOUND_TWO);
            GOTO(OPTION_MENU);
        }
        else if (CheckCollisionPointRec(mouse, rectExit)) {
            GamePlaySound(SOUND_TWO);
            CloseWindow();
        }
    }
}

static void RenderMainMenu() {
    /*
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKBLUE);
    DrawText("DAYDREAM", 20, 20, 40, WHITE);
    DrawText("[N]ew Game", 120, 220, 20, WHITE);
    DrawText("[O]ptions", 120, 250, 20, WHITE);
    DrawText("ESC to QUIT", 120, 280, 20, WHITE);
    */

    // ­I´º¹Ï
    float screenRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    float imageRatio = (float)menuBackground.width / (float)menuBackground.height;

    float scale;
    if (screenRatio > imageRatio) {
        scale = (float)SCREEN_WIDTH / (float)menuBackground.width;
    }
    else {
        scale = (float)SCREEN_HEIGHT / (float)menuBackground.height;
    }

    float bgWidth = menuBackground.width * scale;
    float bgHeight = menuBackground.height * scale;
    float offsetX = (SCREEN_WIDTH - bgWidth) / 2;
    float offsetY = (SCREEN_HEIGHT - bgHeight) / 2;

    DrawTexturePro(menuBackground,
        (Rectangle) {
        0, 0, menuBackground.width, menuBackground.height
    },
        (Rectangle) {
        offsetX, offsetY, bgWidth, bgHeight
    },
        (Vector2) {
        0, 0
    }, 0.0f, WHITE);

    // Åã¥Ü«ö¶s¡]Start¡BOptions¡BExit¡^
    Vector2 mouse = GetMousePosition();

    // Start «ö¶s
    Color tintStart = CheckCollisionPointRec(mouse, rectStart) ? (Color) { 255, 255, 255, 200 } : WHITE;
    DrawTextureEx(buttonStart, (Vector2) { rectStart.x, rectStart.y }, 0.0f, 0.8f, tintStart);

    // Options «ö¶s
    Color tintOptions = CheckCollisionPointRec(mouse, rectOptions) ? (Color) { 255, 255, 255, 200 } : WHITE;
    DrawTextureEx(buttonOptions, (Vector2) { rectOptions.x, rectOptions.y }, 0.0f, 0.8f, tintOptions);

    // Exit «ö¶s
    Color tintExit = CheckCollisionPointRec(mouse, rectExit) ? (Color) { 255, 255, 255, 200 } : WHITE;
    DrawTextureEx(buttonExit, (Vector2) { rectExit.x, rectExit.y }, 0.0f, 0.8f, tintExit);
}

static void ExitMainMenu() {
    // e.g. stop bgm
    UnloadTexture(menuBackground);
    UnloadTexture(buttonStart);
    UnloadTexture(buttonOptions);
    UnloadTexture(buttonExit);
}

const GameState STATE_MAIN_MENU = {
    .enter = EnterMainMenu,
    .update = UpdateMainMenu,
    .render = RenderMainMenu,
    .exit = ExitMainMenu
};