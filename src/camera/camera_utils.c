/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:04:03 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/08 12:11:24 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	setup_camera_dimensions(t_control_panel *control_panel)
{
	int	height_calc;

	control_panel->camera.aspect_ratio = 16.0 / 9.0;
	setup_antialiasing(control_panel, 100);
	control_panel->camera.image_width = WINDOW_WIDTH;
	height_calc = (int)control_panel->camera.image_width;
	control_panel->camera.image_height = height_calc
		/ control_panel->camera.aspect_ratio;
	if (control_panel->camera.image_height < 1)
		control_panel->camera.image_height = 1;
}

double	calculate_focal_length(t_control_panel *cp)
{
	double	lookfrom_minus_lookat[3];

	vec3_sub(lookfrom_minus_lookat, cp->camera.cords, cp->camera.lookat);
	return (vec3_lenght(lookfrom_minus_lookat));
}

void	apply_movement(double camera_pos[3], double axis[3], double speed,
		bool *moved)
{
	double	direction[3];

	vec3_scale(direction, axis, speed);
	vec3_add(camera_pos, camera_pos, direction);
	*moved = true;
}
