/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:29:42 by hguerrei          #+#    #+#             */
/*   Updated: 2025/06/23 14:10:08 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int init_values_main_win(t_mlx *mlx_data, t_control_panel *control_panel)
{
    mlx_data->mlx = mlx_init();
    if (!mlx_data->mlx)
    {
        ft_printf("Error: Could not initialize MLX\n");
        return (1);
    }

    mlx_data->win = mlx_new_window(mlx_data->mlx, control_panel->camera.image_width, control_panel->camera.image_height, "miniRT");
    if (!mlx_data->win)
    {
        ft_printf("Error: Could not create window\n");
        return (1);
    }

    mlx_data->img = mlx_new_image(mlx_data->mlx, control_panel->camera.image_width, control_panel->camera.image_height);
    mlx_data->addr = mlx_get_data_addr(mlx_data->img, &mlx_data->bits_per_pixel,
                                      &mlx_data->line_length, &mlx_data->endian);

    control_panel->mlx = mlx_data;
    return 0;
}
