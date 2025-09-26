/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glass.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/09/26 17:05:10 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static double	get_glass_ri(const t_hit_record *rec)
{
	double	ri;

	if (rec->front_face)
		ri = 1.0 / rec->material->refraction_index;
	else
		ri = rec->material->refraction_index;
	return (ri);
}

static bool	get_glass_direction(const double *unit_direction,
				const t_hit_record *rec, double ri, double *direction)
{
	double	neg_unit_direction[3];
	double	cos_theta;
	double	sin_theta;
	bool	cannot_refract;

	vec3_negate(neg_unit_direction, unit_direction);
	cos_theta = vec3_dot(neg_unit_direction, rec->normal);
	if (cos_theta > 1.0)
		cos_theta = 1.0;
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	cannot_refract = ri * sin_theta > 1.0;
	if (cannot_refract
		|| schlick_reflectance(cos_theta, ri) > random_double_0_to_1())
	{
		reflect(unit_direction, rec->normal, direction);
		return (true);
	}
	refract(unit_direction, rec->normal, ri, direction);
	return (false);
}

bool	glass_scatter(const t_ray *r_in, t_hit_record *rec,
			t_data_scatter *data_scatter)
{
	double	unit_direction[3];
	double	direction[3];
	double	ri;

	ri = get_glass_ri(rec);
	vec3_set(data_scatter->attenuation, 1.0, 1.0, 1.0);
	vec3_unit_vector(unit_direction, r_in->direction);
	get_glass_direction(unit_direction, rec, ri, direction);
	create_ray(&data_scatter->scattered, rec->position, direction);
	return (true);
}
