/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:52:01 by hguerrei          #+#    #+#             */
/*   Updated: 2025/06/20 17:49:07 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * Coloca um pixel na imagem em uma posição específica
 * @param data Estrutura contendo informações MLX
 * @param x Coordenada X do pixel
 * @param y Coordenada Y do pixel
 * @param color Cor em formato RGB (0xRRGGBB)
 */
void my_mlx_pixel_put(t_control_panel *control_panel, int x, int y, int color)
{
    char *dst;
    t_mlx *mlx_data;

    mlx_data = control_panel->mlx;
    if (x >= 0 && x < control_panel->camera.image_width && y >= 0 && y < control_panel->camera.image_height)
    {
        dst = mlx_data->addr + (y * mlx_data->line_length + x * (mlx_data->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}

void control_mlx_pixel_put(t_control_window *control_win, int x, int y, int color)
{
    char *dst;
    
    if (x < 0 || x >= control_win->width || y < 0 || y >= control_win->height)
        return;
    dst = control_win->addr + (y * control_win->line_length + x * (control_win->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int close_window(t_control_panel *control_panel)
{
    t_mlx *mlx_data;

    mlx_data = control_panel->mlx;
    if (mlx_data->img)
        mlx_destroy_image(mlx_data->mlx, mlx_data->img);
    if (mlx_data->win)
        mlx_destroy_window(mlx_data->mlx, mlx_data->win);
    if (mlx_data->mlx)
    {
        mlx_destroy_display(mlx_data->mlx);
        free(mlx_data->mlx);
    }
    free_control_panel_lists(control_panel);
    exit(0);
    return (0);
}

void clear_image(t_control_panel *control_panel)
{
    t_mlx *mlx_data;

    mlx_data = control_panel->mlx;
    ft_bzero(mlx_data->addr, control_panel->camera.image_height * mlx_data->line_length);

    mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}
