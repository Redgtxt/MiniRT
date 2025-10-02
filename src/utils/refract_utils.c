/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:24:20 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/02 15:34:30 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	calc_perpendicular(t_refract_data *data, const double uv[3],
			const double n[3], double etai_over_etat)
{
	vec3_scale(data->cos_theta_n, n, data->cos_theta);
	vec3_add(data->temp, uv, data->cos_theta_n);
	vec3_scale(data->r_out_perp, data->temp, etai_over_etat);
}

void	calc_parallel(double r_out_parallel[3], const double n[3],
			double r_out_perp[3])
{
	double	perp_length_sq;
	double	parallel_magnitude;

	perp_length_sq = lenght_squared(r_out_perp);
	parallel_magnitude = sqrt(fabs(1.0 - perp_length_sq));
	vec3_scale(r_out_parallel, n, -parallel_magnitude);
}
