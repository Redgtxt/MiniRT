/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:29:42 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/12 17:19:53 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	init_values_main_win(t_mlx *mlx_data, t_control_panel *control_panel)
{
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
	{
		ft_printf("Error: Could not initialize MLX\n");
		return (1);
	}
	mlx_data->win = mlx_new_window(mlx_data->mlx,
			control_panel->camera.image_width,
			control_panel->camera.image_height, "miniRT");
	if (!mlx_data->win)
	{
		ft_printf("Error: Could not create window\n");
		return (1);
	}
	mlx_data->img = mlx_new_image(mlx_data->mlx,
			control_panel->camera.image_width,
			control_panel->camera.image_height);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, &mlx_data->bits_per_pixel,
			&mlx_data->line_length, &mlx_data->endian);
	control_panel->mlx = mlx_data;
	return (0);
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
