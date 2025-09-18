/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:36:29 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/18 12:58:24 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

typedef struct s_cp	t_control_panel;
typedef struct s_mt	t_material;
typedef enum e_mt_t	t_material_type;

# define WINDOW_HEIGHT 360
# define WINDOW_WIDTH 1280
# define W_WIDTH 450 // window de controlo
# define W_HEIGHT 600 // window de controlo
# define KEY_ESC 65307
# define ARROW_UP_KEY 65362
# define ARROW_DOWN_KEY 65364
# define ARROW_LEFT_KEY 65361
# define ARROW_RIGHT_KEY 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113 // Move up
# define KEY_E 101 // Move down
# define KEY_R 114 // Reset camera position
// Cores para a interface
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_GRAY 0x808080
# define COLOR_DARK_GRAY 0x404040
# define COLOR_BLUE 0x0080FF
# define COLOR_RED 0xFF0000
// Cores para UI
# define COLOR_BUTTON_BG 0x404040
# define COLOR_DROPDOWN_BG 0x303030
# define COLOR_HOVER 0x4080FF
# define COLOR_TEXT_SOFT 0xE0E0E0
# define COLOR_SELECTED 0x206040
# define COLOR_BORDER 0x606060
# define COLOR_HIGHLIGHT 0x40FF40
# define COLOR_SHADOW 0x106010

typedef struct s_button
{
	int				x;
	int				y;
	int				width;
	int				height;
	int				color;
}					t_button;

typedef struct s_obj_info
{
	char			*obj_type;
	double			**rgb;
	double			*pos;
}					t_obj_info;

typedef struct s_slider
{
	int				x;
	int				y;
	int				width;
	int				height;
	int				handle_width;
	int				handle_height;
	float			min_value;
	float			max_value;
	float			current_value;
	int				color_bar;
	int				color_handle;
	int				is_dragging;
}					t_slider;

typedef struct s_image
{
	void			*sphere;
	void			*plane;
	void			*cylinder;
	void			*cone;
}					t_image;

// Quadrado do Dropwdown
typedef struct s_rect
{
	int				x;
	int				y;
	int				width;
	int				height;
}					t_rect;

typedef struct s_mat_select
{
	int				x;
	int				y;
	int				width;
	int				height;
	int				dropdown_height;
	int				is_open;
	int				selected_material;
	int				hover_index;
	char			*material_names[4];
	int				item_height;
	int				color_button;
	int				color_dropdown;
	int				color_hover;
	int				color_text;
}					t_mat_select;

// Posição do dropdown
// render button
// amb_light
// Slider para vermelho
// Slider para verde
// Slider para azul
typedef struct s_win_config
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_mat_select	material_selector;
	t_button		button;
	t_slider		slider;
	t_slider		red_slider;
	t_slider		green_slider;
	t_slider		blue_slider;
	t_image			image;
}					t_win_config;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx;

// utils
int					is_valid_sphere(t_control_panel *cp);
int					is_valid_plane(t_control_panel *cp);
int					is_valid_cylinder(t_control_panel *cp);
int					is_valid_cone(t_control_panel *cp);
void				init_images(t_control_panel *cp, t_win_config *control_data,
						int img_width, int img_height);
void				change_object(int keycode, t_control_panel *cp);
void				control_win_hooks(t_win_config *control_data,
						t_control_panel *cp);
// rgb
void				create_rgb_sliders(t_control_panel *cp);
int					get_rgb_values(t_control_panel *cp, double *r, double *g,
						double *b);
// button
void				update_objects_properties(t_control_panel *cp,
						t_slider *slider);
int					render_button(t_control_panel *cp, t_slider *slider, int x,
						int y);

// mouse
int					mouse_release_handler(int button, int x, int y,
						void *param);
int					mouse_move_handler(int x, int y, void *param);
int					mouse_press_handler(int button, int x, int y, void *param);
void				update_slider_value(t_slider *slider, int mouse_x);
int					is_mouse_on_slider_handle(t_slider slider, int mouse_x,
						int mouse_y);

// mouse click handlers
int					handle_render_button_click(t_control_panel *cp, int x,
						int y);
int					handle_material_selector_click_event(t_control_panel *cp,
						int x, int y);
void				handle_ambient_light_slider(t_control_panel *cp, int x,
						int y);
void				handle_rgb_sliders_group(t_control_panel *cp, int x, int y);
void				handle_dragging_rgb_slider(t_control_panel *cp);

// mouse move utilities
void				slider_sphere_rgb(t_control_panel *cp, int x);

// slider
void				draw_slider(t_control_panel *cp, t_slider slider);
void				draw_slider_amb_light(t_control_panel *cp, t_slider slider);
void				clear_image_slider(t_control_panel *cp);
int					is_mouse_on_slider_bar(t_slider slider, int mouse_x,
						int mouse_y);
void				redraw_interface(t_control_panel *cp);
void				update_sliders_from_selected_object(t_control_panel *cp);
// Dropdown
void				init_mat_select(t_mat_select *selector);
void				draw_material_selector(t_control_panel *cp);
void				handle_material_selector_click(t_control_panel *cp,
						int mouse_x, int mouse_y);
void				handle_material_selector_hover(t_control_panel *cp,
						int mouse_x, int mouse_y);
void				apply_material_to_selected_object(t_control_panel *cp,
						t_material_type material_type);
void				configure_material_properties(t_material *material,
						t_material_type type);
int					is_mouse_on_material_selector(t_mat_select *selector,
						int mouse_x, int mouse_y);
int					get_dropdown_item_index(t_mat_select *selector, int mouse_x,
						int mouse_y);

// Drawing functions
void				draw_filled_rectangle(t_control_panel *cp, t_rect rect,
						int color);
void				draw_text_at_position(t_control_panel *cp, int x, int y,
						char *text);

// Novas funções para UI melhorada
void				draw_border(t_control_panel *cp, t_rect rect, int color);
void				draw_arrow_down(t_control_panel *cp, int x, int y);
void				draw_slider_bar(t_control_panel *cp, t_slider slider);
void				draw_slider_handle_improved(t_control_panel *cp,
						t_rect rect, int color);
void				draw_button(t_control_panel *cp, t_button button);

// Mouse utilities
void				set_slider_value_from_position(t_slider *slider,
						int mouse_x);

// RGB handling
void				update_object_rgb(t_control_panel *cp, int rgb_index,
						float value);
void				handle_rgb_slider_interaction(t_control_panel *cp,
						t_slider *slider, int x, int y);

// Interface display
void				display_object_stats(t_control_panel *cp, int obj_index);
void				display_object_properties(t_control_panel *cp,
						int obj_index);

// MLX
void				my_mlx_pixel_put(t_control_panel *control_panel, int x,
						int y, int color);
int					close_window(t_control_panel *cp);
int					key_hook(int keycode, t_control_panel *cp);
void				game_hooks(t_control_panel *control_panel);
void				clear_image(t_control_panel *cp);
void				config_antialising_render(int keycode,
						t_control_panel *control_panel);
int					init_values_main_win(t_mlx *mlx_data,
						t_control_panel *control_panel);
void				pixel_put_win_control(t_control_panel *cp, int x, int y,
						int color);
int					main_window_mouse_handler(int button, int x, int y,
						void *param);
int					is_mouse_on_selector_button(t_mat_select *selector, int x,
						int y);
// Window control
int					create_control_window(t_control_panel *cp);
int					find_clicked_object(t_control_panel *cp, int mouse_x,
						int mouse_y, int *obj_type);
void				update_control_interface_with_object(t_control_panel *cp,
						int obj_index, int obj_type);
#endif