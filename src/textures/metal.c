/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:47:40 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/12 20:50:42 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	metal_scatter(const t_ray *r_in, t_hit_record *rec,
		t_data_scatter *data)
{
	double	reflected[3];

	reflect(r_in->direction, rec->normal, reflected);
	create_ray(&data->scattered, rec->position, reflected);
	vec3_copy(data->attenuation, rec->material->albedo);
	return (vec3_dot(data->scattered.direction, rec->normal) > 0);
}
