# Directories
SRC_DIR = apps/msh/src
INC_DIR = apps/msh/include

# Source files
SRC = $(SRC_DIR)/builtin_commands.c \
      $(SRC_DIR)/env_variable.c \
      $(SRC_DIR)/handle_input.c \
      $(SRC_DIR)/handle_signal.c \
      $(SRC_DIR)/shell_parser.c \
      $(SRC_DIR)/main.c

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

# Output executable
OUT = msh

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)

# Targets
all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT)

# Compile each .c file to .o file
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and the output binary
clean:
	rm -f $(OBJ) $(OUT)

# Optional: Run the executable (msh)
run: $(OUT)
	./$(OUT)

# Rebuild everything
rebuild: clean all
