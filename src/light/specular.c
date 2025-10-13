/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:37:43 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/13 00:07:45 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	init_spec_args(t_specular_args *spec_args, t_light_args *args,
		t_vec3 light_dir[3], double attenuation)
{
	spec_args->rec = args->rec;
	spec_args->ray = args->ray;
	spec_args->light_dir = light_dir;
	spec_args->light = &args->panel->light[args->i];
	spec_args->attenuation = attenuation;
}

static double	calculate_spec(t_specular_args *args)
{
	t_vec3	view_dir[3];
	t_vec3	reflect_dir[3];
	t_vec3	neg_light_dir[3];
	double	spec;
    double  vdn;

	vec3_negate(view_dir, args->ray->direction);
	vec3_normalize(view_dir, view_dir);
	vdn = vec3_dot(view_dir, args->rec->normal);
	if (vdn <= 0.0)
		return (0.0);
	vec3_negate(neg_light_dir, args->light_dir);
	reflect(neg_light_dir, args->rec->normal, reflect_dir);
	vec3_normalize(reflect_dir, reflect_dir);
	spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0),
			args->rec->material->shininess);
	return (spec);
}

void	add_specular(t_specular_args *args, t_vec3 color[3])
{
	double	spec;
	t_vec3	specular[3];

	spec = calculate_spec(args);
	vec3_scale(specular, args->rec->material->specular, spec
		* SPECULAR_INTENSITY);
	vec3_multiply(specular, specular, args->light->rgb);
	vec3_scale(specular, specular, args->light->brightness * args->attenuation);
	vec3_add(color, color, specular);
}
