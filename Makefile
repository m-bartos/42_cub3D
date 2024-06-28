# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -I/opt/X11/include -I/opt/homebrew/include

# Directories
SRC_DIR = src
UTILS_DIR = utils
PARSER_DIR = $(SRC_DIR)/parser
OBJ_DIR = obj_files
LIBFT_DIR = 42_Libft
MLX42_DIR = MLX42

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES += $(wildcard $(SRC_DIR)/**/*.c) # Ensure only source files in subdirectories
UTILS_FILES = $(wildcard $(UTILS_DIR)/*.c)
PARSER_FILES = $(wildcard $(PARSER_DIR)/*.c)
MAIN_FILE = main.c

# Combine all source files, ensuring no duplicates
ALL_SRC_FILES = $(SRC_FILES) $(UTILS_FILES) $(PARSER_FILES) $(MAIN_FILE)
ALL_SRC_FILES := $(sort $(ALL_SRC_FILES)) # Remove duplicates

# Object files
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(ALL_SRC_FILES))

# Libraries
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a

# Executable
EXEC = cub3D

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJ_FILES) $(LIBFT_LIB) $(MLX42_LIB)
	$(CC) $(CFLAGS) -o $@ $^ -L$(MLX42_DIR)/build -lmlx42 -L/opt/X11/lib -lX11 -lXext -L/opt/homebrew/lib -lglfw -lpthread -lm -ldl

# Compile source files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build the libft library
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

# Build the MLX42 library
$(MLX42_LIB):
	cd $(MLX42_DIR) && cmake -B build
	cd $(MLX42_DIR) && cmake --build build -j4

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(MLX42_DIR)/build

# Clean object files and executable
fclean: clean
	rm -f $(EXEC)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re
