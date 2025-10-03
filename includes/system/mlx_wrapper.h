/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_WRAPPER_H
# define MLX_WRAPPER_H

# include "../core/types.h"

/* MLX structure */
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

/* MLX function prototypes */
void	my_mlx_pixel_put(t_control_panel *control_panel, int x, int y,
			int color);
int		close_window(t_control_panel *cp);
int		key_hook(int keycode, t_control_panel *cp);
void	game_hooks(t_control_panel *control_panel);
void	clear_image(t_control_panel *cp);
void	config_antialising_render(int keycode, t_control_panel *control_panel);
int		init_values_main_win(t_mlx *mlx_data, t_control_panel *control_panel);
void	pixel_put_win_control(t_control_panel *cp, int x, int y, int color);
int		main_window_mouse_handler(int button, int x, int y, void *param);

#endif