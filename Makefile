# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Target executable
TARGET = main.exe

# Source files
SRCS = main.c Item.c Creature.c Player.c Room.c

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean generated files
clean:
	rm -f $(TARGET)

# Rebuild everything
rebuild: clean all