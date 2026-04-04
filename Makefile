CC = gcc
SRC = src/main.c
BIN_DIR = bin
TARGET = $(BIN_DIR)/main

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all run clean


