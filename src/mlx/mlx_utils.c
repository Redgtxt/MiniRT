/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:52:01 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/18 12:36:27 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	my_mlx_pixel_put(t_control_panel *control_panel, int x, int y,
		int color)
{
	char	*dst;
	t_mlx	*mlx_data;

	mlx_data = control_panel->mlx;
	if (x >= 0 && x < control_panel->camera.image_width && y >= 0
		&& y < control_panel->camera.image_height)
	{
		dst = mlx_data->addr + (y * mlx_data->line_length + x
				* (mlx_data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	close_window(t_control_panel *cp)
{
	if (cp && cp->config_win)
	{
		if (cp->config_win->image.sphere)
			mlx_destroy_image(cp->config_win->mlx,
				cp->config_win->image.sphere);
		if (cp->config_win->image.plane)
			mlx_destroy_image(cp->config_win->mlx, cp->config_win->image.plane);
		if (cp->config_win->image.cylinder)
			mlx_destroy_image(cp->config_win->mlx,
				cp->config_win->image.cylinder);
		if (cp->config_win->img)
			mlx_destroy_image(cp->config_win->mlx, cp->config_win->img);
		if (cp->config_win->win)
			mlx_destroy_window(cp->config_win->mlx, cp->config_win->win);
		free(cp->config_win);
		cp->config_win = NULL;
	}
	exit(0);
	return (0);
}

void	clear_image(t_control_panel *cp)
{
	t_mlx	*mlx_data;

	mlx_data = cp->mlx;
	ft_bzero(mlx_data->addr, cp->camera.image_height * mlx_data->line_length);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	init_images(t_control_panel *cp, t_win_config *control_data,
		int img_width, int img_height)
{
	control_data->img = mlx_new_image(control_data->mlx, W_WIDTH, W_HEIGHT);
	control_data->addr = mlx_get_data_addr(control_data->img,
			&control_data->bits_per_pixel, &control_data->line_length,
			&control_data->endian);
	control_data->image.sphere = mlx_xpm_file_to_image(cp->mlx->mlx,
			"src/images/sphere_small.xpm", &img_width, &img_height);
	control_data->image.plane = mlx_xpm_file_to_image(cp->mlx->mlx,
			"src/images/plane_resized.xpm", &img_width, &img_height);
	control_data->image.cylinder = mlx_xpm_file_to_image(cp->mlx->mlx,
			"src/images/cylinder.xpm", &img_width, &img_height);
	control_data->image.cone = mlx_xpm_file_to_image(cp->mlx->mlx,
			"src/images/cone_resized.xpm", &img_width, &img_height);
}

void	clear_image_slider(t_control_panel *cp)
{
	int	i;
	int	j;

	i = 0;
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
		{
			pixel_put_win_control(cp, j, i, 0x000000);
			j++;
		}
		i++;
	}
}
