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

bool	solid_scatter(t_control_panel *cp, t_hit_record *rec, const t_ray *ray,
		t_vec3 color[3])
{
	t_vec3	ambient_sample[3];
	t_vec3	material_ambient[3];
	t_vec3	albedo[3];

	vec3_copy(albedo, rec->material->albedo);
	if (rec->material->has_bump)
		apply_texture_color(cp, rec, albedo);
	set_amb_light(cp, ray, ambient_sample);
	vec3_multiply(material_ambient, ambient_sample, albedo);
	vec3_add(color, color, material_ambient);
	return (false);
}
