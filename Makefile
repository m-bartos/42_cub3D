# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
UTILS_DIR = utils
OBJ_DIR_SRC = $(SRC_DIR)/obj_files
OBJ_DIR_UTILS = $(UTILS_DIR)/obj_files
LIBFT_DIR = 42_libft

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
UTILS_FILES = $(wildcard $(UTILS_DIR)/*.c)
MAIN_FILE = main.c

# Object files
OBJ_FILES_SRC = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_SRC)/%.o, $(SRC_FILES))
OBJ_FILES_UTILS = $(patsubst $(UTILS_DIR)/%.c, $(OBJ_DIR_UTILS)/%.o, $(UTILS_FILES))
MAIN_OBJ = $(MAIN_FILE:.c=.o)

OBJ_FILES = $(OBJ_FILES_SRC) $(OBJ_FILES_UTILS) $(MAIN_OBJ)

# Executable
EXEC = cube

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJ_FILES) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
$(OBJ_DIR_SRC)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_UTILS)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR_UTILS)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build the libft library
$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR_SRC) $(OBJ_DIR_UTILS) $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean object files and executable
fclean: clean
	rm -f $(EXEC)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re
