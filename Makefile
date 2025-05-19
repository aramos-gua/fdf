# Text styles
DEL_LINE =		\033[2K
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m

# Basic bright colors
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m

# Other colors
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

#Compiler information
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft -Iminilibx-linux -MMD -MP -g3

# Libraries
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# Target names
NAME = fdf

# Paths
OBJ_DIR = build
SRC_DIR = src
INCLUDES = includes

# Source Files
SRC = $(SRC_DIR)/fdf.c\
	  $(SRC_DIR)/validate_input.c\
	  $(SRC_DIR)/draw_tools.c\
	  $(SRC_DIR)/grid_maker_helpers.c\
	  $(SRC_DIR)/transforms.c\
	  $(SRC_DIR)/colors.c\
	  $(SRC_DIR)/freexit.c

# Object and Dependency Files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

# Create program
$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $@
	@echo "\n${GREEN} Created $(NAME) ${DEF_COLOR}\n"

# Create Libraries
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX_LIB):
	@make --no-print-directory -C $(MLX_DIR)

# Compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "${MAGENTA} ~ ${BROWN} Compiling... ${MAGENTA}-> ${CYAN}$< ${DEF_COLOR}"
	@$(CC) $(CFLAGS) -I/usr/include -I$(MLX_DIR)mlx -c $< -o $@

# Build all
all: $(NAME)

# Remove .o files
clean:
	@rm -rf $(OBJ_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@make --no-print-directory -C $(MLX_DIR) clean

# Remove everything
fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "${GREEN} Cleaned $(NAME) ${DEF_COLOR}"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re

-include $(OBJ:.o=.d)
