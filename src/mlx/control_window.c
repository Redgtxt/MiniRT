/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:01:36 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/10 00:24:19 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_win_config	*init_control_window(t_control_panel *cp)
{
	t_win_config	*control_data;
	int				img_width;
	int				img_height;

	img_width = 0;
	img_height = 0;
	control_data = ft_calloc(1, sizeof(t_win_config));
	if (!control_data)
		return (NULL);
	control_data->mlx = cp->mlx->mlx;
	if (!control_data->mlx)
	{
		ft_printf("Error: Could not initialize MLX\n");
		return (free(control_data), NULL);
	}
	control_data->win = mlx_new_window(control_data->mlx, W_WIDTH, W_HEIGHT,
			"miniRT Control");
	if (!control_data->win)
	{
		ft_printf("Error: Could not create window\n");
		return (free(control_data), NULL);
	}
	init_images(cp, control_data, img_width, img_height);
	return (control_data);
}

static void	setup_control_components(t_control_panel *cp,
		t_win_config *control_data)
{
	t_button	my_button;
	t_slider	my_slider;

	my_button = (t_button){100, 100, 200, 50, 0x00FF00};
	my_slider = (t_slider){50, 200, 300, 10, 20, 30, 0.0, 1.0,
		cp->amb_light.light_force, 0xFF0000, 0};
	control_data->button = my_button;
	control_data->slider = my_slider;
	init_mat_select(&cp->config_win->material_selector);
	update_material_selector_from_selected_object(cp);
}

static void	display_object_image(t_control_panel *cp)
{
	t_win_config	*data;

	data = cp->config_win;
	if (cp->data.obj_type == 0 && data->image.sphere)
		mlx_put_image_to_window(data->mlx, data->win, data->image.sphere, 10,
			10);
	else if (cp->data.obj_type == 1 && data->image.plane)
		mlx_put_image_to_window(data->mlx, data->win, data->image.plane, 10,
			10);
	else if (cp->data.obj_type == 2 && data->image.cylinder)
		mlx_put_image_to_window(data->mlx, data->win, data->image.cylinder, 10,
			10);
	else if (cp->data.obj_type == 3 && data->image.cone)
		mlx_put_image_to_window(data->mlx, data->win, data->image.cone, 10, 10);
}

static int	should_update_sliders(t_control_panel *cp)
{
	return ((cp->data.obj_type == 0 && cp->sphere && cp->data.sphere_count > 0)
		|| (cp->data.obj_type == 1 && cp->plane && cp->data.plane_count > 0)
		|| (cp->data.obj_type == 2 && cp->cylinder
			&& cp->data.cylinder_count > 0) || (cp->data.obj_type == 3
			&& cp->cone && cp->data.cone_count > 0));
}

int	create_control_window(t_control_panel *cp)
{
	t_win_config	*control_data;

	control_data = init_control_window(cp);
	if (!control_data)
		return (1);
	cp->config_win = control_data;
	setup_control_components(cp, control_data);
	if (should_update_sliders(cp))
		update_sliders_from_selected_object(cp);
	draw_button(cp, control_data->button);
	draw_slider(cp, control_data->slider);
	mlx_put_image_to_window(control_data->mlx, control_data->win,
		control_data->img, 0, 0);
	display_object_image(cp);
	mlx_string_put(control_data->mlx, control_data->win, 175, 130, 0xFF0000,
		"RENDER");
	draw_slider_amb_light(cp, control_data->slider);
	if (cp->sphere && cp->data.sphere_count > 0)
		redraw_interface(cp);
	control_win_hooks(control_data, cp);
	return (0);
}
