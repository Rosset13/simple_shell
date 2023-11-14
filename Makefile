CC := gcc
CFLAGS := -Wall -Werror
LDFLAGS :=

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# List of source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
# Generate corresponding object file names
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
# Name of the final executable
EXECUTABLE := $(BIN_DIR)/myshell

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
