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
    cardManager.c \
    assetManager.c \
    DoorCard.c \
    EmptyCard.c \
    EnemyCard.c \
    ItemCard.c \
    CharacterStats.c \
    CombatSystem.c \
    playerUI.c

# 輸出檔案名稱
TARGET = test.exe

# 預設規則
all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(INCLUDES) $(LIBS)  # 編譯並生成 test.exe
	# $(TARGET)  # 執行編譯後的檔案

# 清除物件檔和執行檔
clean:
	del /Q *.exe *.o
