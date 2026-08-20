/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/10/12 23:49:32 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	get_checker_color(t_hit_record *rec, double scale,
		double *checker_color)
{
	int	x;
	int	y;
	int	z;

	if (scale <= 0.0)
		scale = 1.0;
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
