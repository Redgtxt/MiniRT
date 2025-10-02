/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:42:40 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/02 14:49:07 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static double	get_attenuation(double distance, double shadow_intensity)
{
    double attenuation;

    attenuation = 1.0 / (LIGHT_CONSTANT + LIGHT_LINEAR * distance +
									LIGHT_QUADRATIC * distance * distance);
    attenuation *= shadow_intensity;
    return (attenuation);
}

static void	apply_lighting(t_light_args *args, vec3 light_dir[3],
				double attenuation)
{
	t_specular_args spec_args;

	diffuse_comp(args, light_dir, attenuation);
	if (args->rec->material->shininess > 0)
	{
		init_spec_args(&spec_args, args, light_dir, attenuation);
		add_specular(&spec_args, args->color);
	}
}

void	process_light(t_light_args *args)
{
	vec3 light_dir[3];
	double distance;
	double shadow_intensity;
	double attenuation;

	vec3_sub(light_dir, args->panel->light[args->i].cords,
		args->rec->position);
	distance = vec3_length(light_dir);
	shadow_intensity = get_shadow_intensity(args->panel,
		args->rec->position, &args->panel->light[args->i]);
	if (shadow_intensity > 0.0)
	{
		vec3_normalize(light_dir, light_dir);
		attenuation = get_attenuation(distance, shadow_intensity);
		apply_lighting(args, light_dir, attenuation);
	}
}
