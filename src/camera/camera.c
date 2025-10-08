/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:45:45 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/08 15:42:54 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	calculate_viewport_dimensions(t_control_panel *cp,
		double focal_length, double *vp_height, double *vp_width)
{
	double	theta;
	double	h;

	theta = degrees_to_radians(cp->camera.fov);
	h = tan(theta / 2);
	*vp_height = 2.0 * h * focal_length;
	*vp_width = *vp_height * ((double)cp->camera.image_width
			/ (double)cp->camera.image_height);
}

static void	calculate_camera_basis(t_control_panel *cp)
{
	double	lookfrom_minus_lookat[3];
	double	cross_vup_w[3];

	vec3_sub(lookfrom_minus_lookat, cp->camera.cords, cp->camera.lookat);
	vec3_unit_vector(cp->camera.w, lookfrom_minus_lookat);
	vec3_cross(cross_vup_w, cp->camera.vup, cp->camera.w);
	vec3_unit_vector(cp->camera.u, cross_vup_w);
	vec3_cross(cp->camera.v, cp->camera.w, cp->camera.u);
}

static void	calculate_viewport_u_v(t_control_panel *cp, double vp_width,
		double vp_height, double vp_u[3])
{
	double	vp_v[3];
	double	neg_v[3];

	vec3_scale(vp_u, cp->camera.u, vp_width);
	vec3_negate(neg_v, cp->camera.v);
	vec3_scale(vp_v, neg_v, vp_height);
	vec3_divide(cp->camera.pixel_delta_u, vp_u, (double)cp->camera.image_width);
	vec3_divide(cp->camera.pixel_delta_v, vp_v,
		(double)cp->camera.image_height);
}

static void	setup_camera_viewport(t_control_panel *control_panel)
{
	double	focal_length;
	double	viewport_height;
	double	viewport_width;
	double	viewport_u[3];

	focal_length = calculate_focal_length(control_panel);
	calculate_viewport_dimensions(control_panel, focal_length, &viewport_height,
		&viewport_width);
	calculate_camera_basis(control_panel);
	calculate_viewport_u_v(control_panel, viewport_width, viewport_height,
		viewport_u);
	calculate_pixel00_location(control_panel, focal_length, viewport_u,
		control_panel->camera.pixel_delta_v);
}

void	get_values_camera(t_control_panel *control_panel)
{
	setup_camera_dimensions(control_panel);
	vec3_add(control_panel->camera.lookat, control_panel->camera.cords,
		control_panel->camera.vec3);
	vec3_set(control_panel->camera.vup, 0, 1, 0);
	setup_camera_viewport(control_panel);
	control_panel->camera.max_bounces = MAX_CAMERA_BOUNCES;
}
