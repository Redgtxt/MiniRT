/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:40:15 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/12 20:50:42 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static double	get_ambient_mix(const t_ray *ray)
{
	return (0.5 * (ray->direction[1] + 1.0));
}

void	set_amb_light(t_control_panel *control_panel, const t_ray *ray,
		double out_color[3])
{
	double	white[3];
	double	bg_mix[3];
	double	w_weight;
	double	a;

	vec3_set(white, 1.0, 1.0, 1.0);
	a = get_ambient_mix(ray);
	w_weight = 1.0 - a;
	vec3_scale(out_color, white, w_weight);
	vec3_scale(bg_mix, control_panel->amb_light.rgb, a);
	vec3_add(out_color, out_color, bg_mix);
	vec3_scale(out_color, out_color, control_panel->amb_light.light_force);
}
