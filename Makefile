# ======================== #
#       COLORS            #
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
INC_DIR      = ./includes
# Header organization:
# - core/: Basic types and constants  
# - math/: Mathematical utilities (vec3, interval)
# - graphics/: Rendering components (materials, ray, camera, lighting, render)
# - objects/: Geometric objects (sphere, plane, cylinder, cone)
# - ui/: User interface components
# - system/: System integration (MLX wrapper, memory management)
# - io/: Input/output (parsing, error handling)

# ======================== #
#        SRC/OBJ           #
# ======================== #
LIBFT     = $(LIBFT_DIR)/libft.a
MLX       = $(MLX_DIR)/libmlx.a

SRC_FILES = main.c \
	$(addprefix utils/, utils.c split_spaces.c list_handler.c draw_color.c free_cp.c free_elements.c math_utils.c reflect_types.c refract_utils.c vector_arithmetic.c vector_utils_1.c vector_utils_2.c vector_utils_3.c vector_utils_4.c) \
	$(addprefix mlx/, hooks.c update_sliders_from_selected_object.c change_object.c rgb_slider.c mlx_utils.c verifications.c init_dropdown_materials.c dropdown_interactions.c material_selector.c material_config.c material_apply.c ui_drawing.c slider_drawing.c slider_utils.c interface_display.c rgb_handlers.c interface_render.c mlx_antialising.c render_button.c interface_object_properties.c control_window.c mlx_init_values.c interaction_rgb_sliders.c update_interface_objects.c buttons.c sliders.c mouse_handlers.c mouse_click_handlers.c mouse_move_utils.c find_click_objects.c material_selector_sync.c) \
	$(addprefix objects/, sphere_collision.c plane_collisions.c cylinder_collision.c cylinder_caps.c cylinder_body.c cylinder_utils.c cone_collision.c cone_body.c cone_cap.c hit_world.c) \
	$(addprefix parsing/, parsing.c parse_elements.c parse_objects.c parse_values_1.c parse_values_2.c parse_values_utils.c init_element_array.c initialization.c parse_texture.c texture_loader.c free_texture_list.c) \
	$(addprefix interval/, interval.c) \
	$(addprefix light/, light.c ambient.c diffuse.c specular.c shadow.c) \
	$(addprefix textures/, textures.c base_values.c checker.c glass.c lambertian.c metal.c solid.c) \
	$(addprefix ray/, ray.c get_ray.c ray_utils.c) \
	$(addprefix effects/, antialiasing.c get_uv_map.c bump_map.c apply_texture_color.c) \
	$(addprefix render/, render.c render_utils.c) \
	$(addprefix camera/, camera.c camera_movement.c camera_utils.c viewport_pixel00.c) \
	$(addprefix errors/, error_utils.c error_element_value.c error_print.c error_print_helpers.c)

SRC  = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ======================== #
#        RULES             #
# ======================== #
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/mlx
	@mkdir -p $(OBJ_DIR)/objects
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/interval
	@mkdir -p $(OBJ_DIR)/ray
	@mkdir -p $(OBJ_DIR)/textures
	@mkdir -p $(OBJ_DIR)/light
	@mkdir -p $(OBJ_DIR)/effects
	@mkdir -p $(OBJ_DIR)/render
	@mkdir -p $(OBJ_DIR)/camera
	@mkdir -p $(OBJ_DIR)/errors
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


val: all
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
