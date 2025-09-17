/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_object_properties.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:29:56 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/17 16:30:33 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	display_sphere_properties(t_control_panel *cp, int obj_index)
{
	char	info_text[256];

	sprintf(info_text, "Radius: %.2f", cp->sphere[obj_index].radius);
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70, 0xFFFFFF,
		info_text);
}

static void	display_plane_properties(t_control_panel *cp, int obj_index)
{
	char	info_text[256];

	sprintf(info_text, "Normal: %.2f,%.2f,%.2f", cp->plane[obj_index].vec3[0],
		cp->plane[obj_index].vec3[1], cp->plane[obj_index].vec3[2]);
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70, 0xFFFFFF,
		info_text);
}

static void	display_cylinder_cone_properties(t_control_panel *cp, int obj_index)
{
	char	info_text[256];

	if (cp->data.obj_type == 2)
	{
		sprintf(info_text, "Radius: %.2f, Height: %.2f",
			cp->cylinder[obj_index].radius, cp->cylinder[obj_index].height);
	}
	else if (cp->data.obj_type == 3)
	{
		sprintf(info_text, "Radius: %.2f, Height: %.2f",
			cp->cone[obj_index].radius, cp->cone[obj_index].height);
	}
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70, 0xFFFFFF,
		info_text);
}

void	display_object_properties(t_control_panel *cp, int obj_index)
{
	if (cp->data.obj_type == 0)
		display_sphere_properties(cp, obj_index);
	else if (cp->data.obj_type == 1)
		display_plane_properties(cp, obj_index);
	else if (cp->data.obj_type == 2 || cp->data.obj_type == 3)
		display_cylinder_cone_properties(cp, obj_index);
}
