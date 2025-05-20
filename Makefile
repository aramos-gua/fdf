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
BONUS_NAME = fdf_bonus

# Paths
OBJ_DIR = build
BOBJ_DIR = build_bonus
SRC_DIR = src
BONUS_DIR = src_bonus

# Source Files
SRC = $(SRC_DIR)/fdf.c\
	  $(SRC_DIR)/validate_input.c\
	  $(SRC_DIR)/draw_tools.c\
	  $(SRC_DIR)/grid_maker_helpers.c\
	  $(SRC_DIR)/transforms.c\
	  $(SRC_DIR)/colors.c\
	  $(SRC_DIR)/freexit.c

# Bonus Source Files
BONUS_SRC = $(BONUS_DIR)/fdf_bonus.c\
			$(BONUS_DIR)/validate_input_bonus.c\
			$(BONUS_DIR)/draw_tools_bonus.c\
			$(BONUS_DIR)/grid_maker_helpers_bonus.c\
			$(BONUS_DIR)/transforms_bonus.c\
			$(BONUS_DIR)/colors_bonus.c\
			$(BONUS_DIR)/freexit_bonus.c\
			$(BONUS_DIR)/bonus.c\
			$(BONUS_DIR)/handle_input_bonus.c


# Objects and Dependency Files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BOBJ = $(BONUS_SRC:$(BONUS_DIR)/%.c=$(BOBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d) $(BOBJ:.o=.d)

# Create Mandatory
$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $@
	@echo "\n${GREEN} Created $(NAME) ${DEF_COLOR}\n"

# Create Libraries
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX_LIB):
	@make --no-print-directory -C $(MLX_DIR)

# Compile Mandatory .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "${MAGENTA} ~ ${BROWN} Compiling... ${MAGENTA}-> ${CYAN}$< ${DEF_COLOR}"
	@$(CC) $(CFLAGS) -I/usr/include -I$(MLX_DIR)mlx -c $< -o $@

# Compile Bonus .c files into .o files
$(BOBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "${MAGENTA} ~ ${BROWN} Compiling Bonus... ${MAGENTA}-> ${CYAN}$< ${DEF_COLOR}"
	@$(CC) $(CFLAGS) -I/usr/include -I$(MLX_DIR)mlx -c $< -o $@

# Build all
all: $(NAME)

# Build Bonus
$(BONUS_NAME): $(BOBJ) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(BOBJ) $(LIBFT) $(MLX) -o $(BONUS_NAME)
	@echo "\n${GREEN} Created Bonus $(BONUS_NAME) ${DEF_COLOR}\n"

bonus: CFLAGS := -Wall -Werror -Wextra -Iincludes_bonus -Ilibft -Iminilibx-linux -MMD -MP -g3
bonus: $(BONUS_NAME)
	@cp $(BONUS_NAME) $(NAME)

# Remove .o files
clean:
	@rm -rf $(OBJ_DIR) $(BOBJ_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@make --no-print-directory -C $(MLX_DIR) clean
	@echo "${GREEN} Cleaned $(OBJ_DIR) ${DEF_COLOR}"

# Remove everything
fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "${GREEN} Cleaned $(NAME) ${DEF_COLOR}"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re

-include $(OBJ:.o=.d) $(BOBJ:.o=.d)
