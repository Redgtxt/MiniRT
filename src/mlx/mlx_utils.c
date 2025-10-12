/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:52:01 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/12 17:22:36 by hguerrei         ###   ########.fr       */
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

static void	clear_config_window(t_control_panel *cp)
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
		if (cp->config_win->image.cone)
			mlx_destroy_image(cp->config_win->mlx, cp->config_win->image.cone);
		if (cp->config_win->img)
			mlx_destroy_image(cp->config_win->mlx, cp->config_win->img);
		if (cp->config_win->win)
			mlx_destroy_window(cp->config_win->mlx, cp->config_win->win);
		free(cp->config_win);
		cp->config_win = NULL;
	}
}

static void	free_mlx_features(t_control_panel *cp)
{
	size_t	i;

	if (cp->textures)
	{
		i = 0;
		while (i < cp->data.texture_count)
		{
			if (cp->textures[i].mlx_img)
				mlx_destroy_image(cp->mlx->mlx, cp->textures[i].mlx_img);
			i++;
		}
	}
	if (cp->mlx->img)
		mlx_destroy_image(cp->mlx->mlx, cp->mlx->img);
	if (cp->mlx->win)
		mlx_destroy_window(cp->mlx->mlx, cp->mlx->win);
	if (cp->mlx->mlx)
	{
		mlx_destroy_display(cp->mlx->mlx);
		free(cp->mlx->mlx);
	}
}

int	close_window(t_control_panel *cp)
{
	clear_config_window(cp);
	if (cp && cp->mlx)
		free_mlx_features(cp);
	free_control_panel(cp);
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
