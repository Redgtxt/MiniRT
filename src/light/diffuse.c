/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:37:43 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/08 15:52:36 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	diffuse_comp(t_light_args *args, t_vec3 light_dir[3], double atten)
{
	t_vec3	diffuse[3];
	double	diff;

	diff = fmax(vec3_dot(args->rec->normal, light_dir), 0.0);
	vec3_scale(diffuse, args->rec->material->albedo, diff * DIFFUSE_INTENSITY);
	vec3_multiply(diffuse, diffuse, args->panel->light[args->i].rgb);
	vec3_scale(diffuse, diffuse, args->panel->light[args->i].brightness
		* atten);
	vec3_add(args->color, args->color, diffuse);
}
