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
FLAGS     = -Wall -Werror -Wextra -O3 -Ofast -g
VFLAGS    = --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s
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
	    $(addprefix utils/, utils.c vector_utils.c split_spaces.c list_handler.c free.c errors.c draw_color.c) \
	    $(addprefix Mlx/, hooks.c mlx_utils.c mlx_antialising.c mlx_brightness.c control_window.c mlx_init_values.c mouse_hooks.c buttons.c sliders.c mouse_handler_utils.c mouse_release_handler.c click_objects.c mouse_press_handler.c)  \
	    $(addprefix Sphere/,init_sphere.c sphere_collision.c plane_collisions.c cylinder_collision.c)  \
	    $(addprefix parsing/, parsing.c parse_elements.c parse_objects.c parse_values_1.c parse_values_2.c) \
	    $(addprefix interval/, interval.c)\
	    $(addprefix light/, light.c)\
	    $(addprefix ray/, ray.c ray_utils.c)\
	    $(addprefix effects/, antialiasing.c)\
	    $(addprefix camera/, camera.c)

SRC  = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ======================== #
#        RULES             #
# ======================== #
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/Mlx
	@mkdir -p $(OBJ_DIR)/Sphere
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/interval
	@mkdir -p $(OBJ_DIR)/ray
	@mkdir -p $(OBJ_DIR)/light
	@mkdir -p $(OBJ_DIR)/effects
	@mkdir -p $(OBJ_DIR)/camera
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

rt:
	./miniRT elements_input.rt

metal:
	./miniRT metal_elements.rt

room:
	./miniRT plane_input.rt

cylinder:
	./miniRT cylinder.rt


val: re
	@echo "$(YELLOW)Running with Valgrind... 🧠$(RESET)"
	@valgrind $(VFLAGS) ./miniRT elements_input.rt

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
.PHONY: all clean fclean re rt val
