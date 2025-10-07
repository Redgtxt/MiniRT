/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:39:18 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/01 13:33:12 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	get_pixel_sample(t_coord coord, t_control_panel *control_panel,
		double offset[3], double pixel_sample[3])
{
	double	pixel_offset_u[3];
	double	pixel_offset_v[3];

	vec3_scale(pixel_offset_u, control_panel->camera.pixel_delta_u, coord.x
		+ offset[0]);
	vec3_scale(pixel_offset_v, control_panel->camera.pixel_delta_v, coord.y
		+ offset[1]);
	vec3_add(pixel_sample, control_panel->camera.pixel00_loc, pixel_offset_u);
	vec3_add(pixel_sample, pixel_sample, pixel_offset_v);
}

t_ray	get_ray(t_coord coord, t_control_panel *control_panel)
{
	double	offset[3];
	double	pixel_sample[3];
	double	ray_direction[3];
	t_ray	ray;

	vec3_zero(offset);
	if (control_panel->camera.antialiasing)
		sample_square(offset);
	get_pixel_sample(coord, control_panel, offset, pixel_sample);
	vec3_sub(ray_direction, pixel_sample, control_panel->camera.cords);
	create_ray(&ray, control_panel->camera.cords, ray_direction);
	return (ray);
}
