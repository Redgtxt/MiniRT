/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_pixel00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:05:49 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/08 15:43:13 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	calculate_viewport_center(t_control_panel *cp, double focal_length,
		double result[3])
{
	double	focal_length_w[3];

	vec3_scale(focal_length_w, cp->camera.w, focal_length);
	vec3_sub(result, cp->camera.cords, focal_length_w);
}

static void	subtract_viewport_offsets(double viewport_center[3], double vp_u[3],
		double vp_v[3], double result[3])
{
	double	viewport_u_half[3];
	double	viewport_v_half[3];

	vec3_divide(viewport_u_half, vp_u, 2.0);
	vec3_divide(viewport_v_half, vp_v, 2.0);
	vec3_sub(result, viewport_center, viewport_u_half);
	vec3_sub(result, result, viewport_v_half);
}

static void	calculate_half_pixel_offset(t_control_panel *cp, double result[3])
{
	double	pixel_delta_sum[3];

	vec3_add(pixel_delta_sum, cp->camera.pixel_delta_u,
		cp->camera.pixel_delta_v);
	vec3_scale(result, pixel_delta_sum, 0.5);
}

static void	calculate_viewport_v(t_control_panel *cp, double vp_v_scaled[3],
		double result[3])
{
	vec3_scale(result, vp_v_scaled, (double)cp->camera.image_height);
}

void	calculate_pixel00_location(t_control_panel *cp, double focal_length,
		double vp_u[3], double vp_v[3])
{
	double	viewport_center[3];
	double	viewport_upper_left[3];
	double	half_delta[3];
	double	vp_v_full[3];

	calculate_viewport_v(cp, vp_v, vp_v_full);
	calculate_viewport_center(cp, focal_length, viewport_center);
	subtract_viewport_offsets(viewport_center, vp_u, vp_v_full,
		viewport_upper_left);
	calculate_half_pixel_offset(cp, half_delta);
	vec3_add(cp->camera.pixel00_loc, viewport_upper_left, half_delta);
}
