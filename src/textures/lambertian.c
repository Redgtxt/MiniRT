/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:47:13 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/13 01:14:11 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	lambertian_scatter(t_hit_record *rec, t_data_scatter *data_scatter)
{
	double	scatter_direction[3];
	double	random_unit[3];

	vec3_random_utit_vector(random_unit);
	vec3_add(scatter_direction, rec->normal, random_unit);
	if (vec3_near_zero(scatter_direction))
		vec3_copy(scatter_direction, rec->normal);
	create_ray(&data_scatter->scattered, rec->position, scatter_direction);
	vec3_copy(data_scatter->attenuation, rec->material->albedo);
	return (true);
}
