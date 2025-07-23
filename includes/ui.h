/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:36:29 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/23 14:40:06 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
#define UI_H

typedef struct s_control_panel t_control_panel;
typedef struct s_material t_material;
typedef enum e_material_type t_material_type;

#define WINDOW_HEIGHT 360
#define WINDOW_WIDTH 1280
#define W_WIDTH 450  // window de controlo
#define W_HEIGHT 600 // window de controlo
#define KEY_ESC 65307
#define ARROW_UP_KEY 65362
#define ARROW_DOWN_KEY 65364
#define ARROW_LEFT_KEY 65361
#define ARROW_RIGHT_KEY 65363
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_Q 113 // Move up
#define KEY_E 101 // Move down
#define KEY_R 114 // Reset camera position
// Cores para a interface
#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLACK 0x000000
#define COLOR_GRAY 0x808080
#define COLOR_DARK_GRAY 0x404040
#define COLOR_BLUE 0x0080FF
#define COLOR_RED 0xFF0000
// Cores para UI
#define COLOR_BUTTON_BG 0x404040
#define COLOR_DROPDOWN_BG 0x303030
#define COLOR_HOVER 0x4080FF
#define COLOR_TEXT_SOFT 0xE0E0E0
#define COLOR_SELECTED 0x206040
#define COLOR_BORDER 0x606060
#define COLOR_HIGHLIGHT 0x40FF40
#define COLOR_SHADOW 0x106010

typedef struct s_button
{
	int x;
	int y;
	int width;
	int height;
	int color;
} t_button;

typedef struct s_slider
{
	int x;				 // posição x do slider
	int y;				 // posição y do slider
	int width;			 // largura total do slider
	int height;			 // altura da barra do slider
	int handle_width;	 // largura do "handle" (botão deslizante)
	int handle_height;	 // altura do handle
	float min_value;	 // valor mínimo
	float max_value;	 // valor máximo
	float current_value; // valor atual
	int color_bar;		 // cor da barra
	int color_handle;	 // cor do handle
	int is_dragging;	 // flag para saber se está sendo arrastado
} t_slider;

typedef struct s_image
{
	void *sphere;
	void *plane;
	void *cylinder;
	void *cone;
} t_image;

typedef struct s_material_selector
{
	int x, y;				 // Posição do dropdown
	int width, height;		 // Tamanho do botão principal
	int dropdown_height;	 // Altura do dropdown quando aberto
	int is_open;			 // Flag se está aberto
	int selected_material;	 // Material atualmente selecionado
	int hover_index;		 // Índice do item em hover
	char *material_names[5]; // Nomes dos materiais
	int item_height;		 // Altura de cada item no dropdown
	int color_button;		 // Cor do botão principal
	int color_dropdown;		 // Cor do dropdown
	int color_hover;		 // Cor do item em hover
	int color_text;			 // Cor do texto
} t_material_selector;


typedef struct s_win_config
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_material_selector material_selector;
	t_button material_apply_btn; // Botão para aplicar material
	t_button button;			 // render button
	t_slider slider;			 // amb_light
	t_slider red_slider;		 // Slider para vermelho
	t_slider green_slider;		 // Slider para verde
	t_slider blue_slider;		 // Slider para azul
	t_image image;
} t_win_config;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_mlx;

// button
void draw_button(t_control_panel *cp, t_button button);

// mouse
int mouse_release_handler(int button, int x, int y, void *param);
int mouse_move_handler(int x, int y, void *param);
int mouse_press_handler(int button, int x, int y, void *param);
void update_slider_value(t_slider *slider, int mouse_x);
int is_mouse_on_slider_handle(t_slider slider, int mouse_x, int mouse_y);

// slider
void draw_slider(t_control_panel *cp, t_slider slider);
void draw_slider_amb_light(t_control_panel *cp, t_slider slider);
void clear_image_slider(t_control_panel *cp);
int is_mouse_on_slider_bar(t_slider slider, int mouse_x, int mouse_y);
void redraw_interface(t_control_panel *cp);
void create_rgb_sliders(t_control_panel *cp);
void set_slider_value_from_position(t_slider *slider, int mouse_x);

// Dropdown
void init_material_selector(t_material_selector *selector);
void draw_material_selector(t_control_panel *cp);
void handle_material_selector_click(t_control_panel *cp, int mouse_x, int mouse_y);
void handle_material_selector_hover(t_control_panel *cp, int mouse_x, int mouse_y);
void apply_material_to_selected_object(t_control_panel *cp, t_material_type material_type);
void configure_material_properties(t_material *material, t_material_type type);
int is_mouse_on_material_selector(t_material_selector *selector, int mouse_x, int mouse_y);
int get_dropdown_item_index(t_material_selector *selector, int mouse_x, int mouse_y);

// Funções auxiliares de desenho
void draw_rectangle(t_control_panel *cp, int x, int y, int width, int height, int color);
void draw_text(t_control_panel *cp, int x, int y, char *text, int color);

// Novas funções para UI melhorada
void draw_border(t_control_panel *cp, int x, int y, int width, int height, int color);
void draw_arrow_down(t_control_panel *cp, int x, int y);
void draw_slider_bar_improved(t_control_panel *cp, t_slider slider);
void draw_slider_handle_improved(t_control_panel *cp, int x, int y, int width, int height, int color);

// MLX
void my_mlx_pixel_put(t_control_panel *control_panel, int x, int y, int color);
int close_window(t_control_panel *control_panel);
int key_hook(int keycode, t_control_panel *cp);
void game_hooks(t_control_panel *control_panel);
void clear_image(t_control_panel *control_panel);
void config_antialising_render(int keycode, t_control_panel *control_panel);
void change_amb_light_brightness(int keycode, t_control_panel *control_panel);
int init_values_main_win(t_mlx *mlx_data, t_control_panel *control_panel);
void pixel_put_win_control(t_control_panel *cp, int x, int y, int color);
int main_window_mouse_handler(int button, int x, int y, void *param);
// Window control
int create_control_window(t_control_panel *cp);
int	find_clicked_object(t_control_panel *cp, int mouse_x,
					int mouse_y, int *obj_type);
void	update_control_interface_with_object(t_control_panel *cp,
	int obj_index, int obj_type);
#endif