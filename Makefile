# ======================== #
#         COLORS           #
# ======================== #
RESET   = \033[0m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
MAGENTA = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m

# ======================== #
#       FLAGS              #
# ======================== #
CC        = cc
FLAGS     = -Wall -Werror -Wextra
MLX_FLAGS = -lm -lX11 -lXext

NAME      = miniRT

# ======================== #
#       PATHS              #
# ======================== #
LIBFT_DIR    = ./Library
MLX_DIR      = $(LIBFT_DIR)/minilibx-linux
SRC_DIR      = ./src
OBJ_DIR      = $(SRC_DIR)/obj

# ======================== #
#        SRC/OBJ           #
# ======================== #
LIBFT     = $(LIBFT_DIR)/libft.a
MLX       = $(MLX_DIR)/libmlx.a

SRC_FILES = main.c \
	    $(addprefix utils/, utils.c) \
	    $(addprefix Maths/, count.c)

SRC  = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ======================== #
#        RULES             #
# ======================== #
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/Maths
	@echo "$(YELLOW)Created object directory: $(OBJ_DIR)$(RESET)"

$(LIBFT):
	@echo "$(CYAN)Compiling Libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "$(CYAN)Compiling MLX...$(RESET)"
	@chmod +x $(MLX_DIR)/configure
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)MLX compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(MAGENTA)Compiling: $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation successful! ✅$(RESET)"
	@echo "$(BLUE)Running checks...$(RESET)"
	@if [ -f $(NAME) ]; then echo "$(GREEN)$(NAME) created successfully! 🎉$(RESET)"; fi

#mudar regra quando tiver-mos cena para executar
rt:	re
	./miniRT


valgrind: $(NAME)
	@echo "$(YELLOW)Running with Valgrind... 🧠$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Executable removed!$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean -s

re: fclean all

# ======================== #
#        PHONY             #
# ======================== #
.PHONY: all clean fclean re rt valgrind
