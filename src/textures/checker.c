/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/09/26 15:54:54 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	get_checker_color(t_hit_record *rec, double scale,
		double *checker_color)
{
	int	x;
	int	y;
	int	z;

	x = floor(rec->position[0] / scale);
	y = floor(rec->position[1] / scale);
	z = floor(rec->position[2] / scale);
	if ((x + y + z) % 2 == 0)
		vec3_copy(checker_color, rec->material->albedo);
	else
	{
		checker_color[0] = rec->material->albedo[0] * 0.2;
		checker_color[1] = rec->material->albedo[1] * 0.2;
		checker_color[2] = rec->material->albedo[2] * 0.2;
	}
}

bool	checker_scatter(t_hit_record *rec, t_data_scatter *data_scatter)
{
	double	scatter_direction[3];
	double	checker_color[3];
	double	scale;

	scale = rec->material->checker_scale;
	if (scale <= 0)
		scale = 1.0;
	random_on_hemisphere(rec->normal, scatter_direction);
	if (vec3_near_zero(scatter_direction))
		vec3_copy(scatter_direction, rec->normal);
	create_ray(&data_scatter->scattered, rec->position, scatter_direction);
	get_checker_color(rec, scale, checker_color);
	vec3_copy(data_scatter->attenuation, checker_color);
	return (true);
}
