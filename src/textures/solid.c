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

bool	solid_scatter(t_control_panel *cp, t_hit_record *rec, t_vec3 color[3])
{
	t_vec3	ambient_color[3];
	t_vec3	material_ambient[3];

	vec3_scale(ambient_color, cp->amb_light.rgb,
		cp->amb_light.light_force);
	vec3_multiply(material_ambient, ambient_color, rec->material->albedo);
	vec3_add(color, color, material_ambient);
	return (false);
}
