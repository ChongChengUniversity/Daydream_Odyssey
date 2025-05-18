# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files
SRC = $(wildcard *.c)

# Object files
OBJ = $(SRC:.c=.o)

# Output binary
TARGET = DayDream

# Default rule
all: $(TARGET)

# How to build the target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lraylib -lm -lpthread -ldl -lrt -lX11

# How to compile each .c file into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(TARGET) $(OBJ)
