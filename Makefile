


CC = gcc
CFLAGS = -Wall -Wextra -I./include
TARGET = sorting_program
SRC_DIR = src
OBJ_DIR = obj

.PHONY: all clean run test

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/stack.c $(SRC_DIR)/sort.c $(SRC_DIR)/file_operations.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/stack.o $(OBJ_DIR)/sort.o $(OBJ_DIR)/file_operations.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) previous_run.txt sorted_array.txt sorted_from_file.txt

run: $(TARGET)
	./$(TARGET)

test:
	./$(TARGET) --file previous_run.txt