/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:20:23 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/08 15:34:27 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double	pont_dist(t_vec3 a[3], t_vec3 b[3])
{
	t_vec3	res[3];

	vec3_sub(res, a, b);
	return (fabs(vec3_lenght(res)));
}

void	init_cylinder_cap_vars(t_cylinder_cap_vars *vars, t_cylinder *cylinder,
		const t_ray *ray)
{
	vec3_copy(vars->normalized_axis, cylinder->vec3);
	vec3_normalize(vars->normalized_axis, vars->normalized_axis);
	vars->denom = vec3_dot(vars->normalized_axis, ray->direction);
}

void	init_cylinder_body_vars(t_cylinder_body_vars *vars,
		t_cylinder *cylinder, const t_ray *ray)
{
	vec3_copy(vars->axis, cylinder->vec3);
	vec3_normalize(vars->axis, vars->axis);
	vec3_sub(vars->oc, ray->origin, cylinder->cords);
	vars->dir_dot_axis = vec3_dot(ray->direction, vars->axis);
	vars->oc_dot_axis = vec3_dot(vars->oc, vars->axis);
	vec3_scale(vars->dir_parallel, vars->axis, vars->dir_dot_axis);
	vec3_sub(vars->dir_perp, ray->direction, vars->dir_parallel);
	vec3_scale(vars->oc_parallel, vars->axis, vars->oc_dot_axis);
	vec3_sub(vars->oc_perp, vars->oc, vars->oc_parallel);
	vars->a = vec3_dot(vars->dir_perp, vars->dir_perp);
	vars->b = 2 * vec3_dot(vars->dir_perp, vars->oc_perp);
	vars->c = vec3_dot(vars->oc_perp, vars->oc_perp) - cylinder->radius
		* cylinder->radius;
}

void	init_have_hit_cyl_struct(t_have_hit_cylinder_vars *vars,
		t_cylinder *cylinder, t_interval t_ray)
{
	vars->hit_anything = false;
	vars->closest_so_far = t_ray.max;
	ft_memset(&vars->temp_rec, 0, sizeof(t_hit_record));
	vars->cylinder = cylinder;
	vars->original_cylinder = *cylinder;
	vec3_copy(vars->original_rgb, cylinder->rgb);
	vec3_copy(vars->axis, vars->original_cylinder.vec3);
	vec3_normalize(vars->axis, vars->axis);
}
