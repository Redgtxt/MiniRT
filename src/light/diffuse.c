/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:37:43 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/13 00:56:06 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	diffuse_comp(t_light_args *args, t_vec3 light_dir[3], double atten)
{
	t_vec3	diffuse[3];
	double	diff;
	double	checker_color[3];

	diff = fmax(vec3_dot(args->rec->normal, light_dir), 0.0);
	if (args->rec->material->type == CHECKERPATTERN)
	{
		get_checker_color(args->rec, args->rec->material->checker_scale,
			checker_color);
		vec3_scale(diffuse, checker_color, diff * DIFFUSE_INTENSITY);
	}
	else if (args->rec->material->type == METAL)
	{
		vec3_scale(diffuse, args->rec->material->albedo,
			diff * DIFFUSE_INTENSITY * METAL_DIFFUSE_SCALE);
	}
	else
	{
		vec3_scale(diffuse, args->rec->material->albedo, diff
			* DIFFUSE_INTENSITY);
	}
	vec3_multiply(diffuse, diffuse, args->panel->light[args->i].rgb);
	vec3_scale(diffuse, diffuse, args->panel->light[args->i].brightness
		* atten);
	vec3_add(args->color, args->color, diffuse);
}
