/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	add_amb_texture(t_control_panel *cp, t_hit_record *rec,
					const t_ray *ray, t_vec3 color[3])
{
	t_vec3			ambient_sample[3];
	t_vec3			material_ambient[3];
	t_vec3			tile_color[3];

	set_amb_light(cp, ray, ambient_sample);
	if (rec->material->type == CHECKERPATTERN)
	{
		get_checker_color(rec, rec->material->checker_scale,
			tile_color);
		vec3_multiply(material_ambient, ambient_sample, tile_color);
	}
	else
		vec3_multiply(material_ambient, ambient_sample, rec->material->albedo);
	vec3_add(color, color, material_ambient);
	return (false);
}
