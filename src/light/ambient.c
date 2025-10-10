/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:40:15 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/10 15:30:01 by randrade         ###   ########.fr       */
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
	double	temp[3];
	double	a;

	vec3_set(white, 1.0, 1.0, 1.0);
	a = get_ambient_mix(ray);
	vec3_scale(out_color, white, control_panel->amb_light.light_force - a);
	vec3_scale(temp, control_panel->amb_light.rgb, a);
	vec3_add(out_color, out_color, temp);
	vec3_scale(out_color, out_color, control_panel->amb_light.light_force);
}
