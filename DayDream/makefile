# 編譯器
CC = gcc

# 編譯旗標
CFLAGS = -Wall -Wextra -g

# raylib 路徑
RAYLIB_PATH = C:/raylib/raylib/src

# 包含的資料夾（.h 檔用）
INCLUDES = -I. -I$(RAYLIB_PATH)

# 連結用的程式庫
LIBS = -L$(RAYLIB_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm

# 所有要編譯的 .c 檔
SRC = \
    game.c \
    main.c \
    state_lose.c \
    state_main_menu.c \
    state_option_menu.c \
    state_playing.c \
    state_win.c \
    audioManager.c \
    stateController.c \
    levelManager.c \
    CardManager.c \
    assetManager.c \
    DoorCard.c \
    EmptyCard.c \
    EnemyCard.c \
    ItemCard.c \
    CharacterStats.c \
    CombatSystem.c \
    playerUI.c \
    shopicon.c \
    state_shop.c \
    inventory.c \
    backpackicon.c \
    money.c \
	KeyCard.c \
    Cardbase.c \
    enemyManager.c \
    equipmentSystem.c \
    itemSystem.c \
    scrollManager.c \
    itemUse.c \
    shopSystem.c \
    bossManager.c \
    portalCard.c \
    story.c \
    openingScene.c \
    endingChoice.c \
    dialogues.c \
    gauntletEvent.c

# 輸出檔案名稱
TARGET = test.exe

# 預設規則
all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(INCLUDES) $(LIBS)

# 清除物件檔和執行檔（適用 Git Bash / MinGW）
clean:
	rm -f *.exe *.o
