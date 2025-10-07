/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_cap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:57:21 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/09/30 18:30:59 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	cone_cap_denom_check(t_cone_cap_vars *vars, t_cone *cone,
		const t_ray *ray)
{
	vars->denom = vec3_dot(cone->vec3, ray->direction);
	if (fabs(vars->denom) < 1e-8)
		return (0);
	return (1);
}

static int	cone_cap_t_check(t_cone_cap_vars *vars, t_cone *cone,
		const t_ray *ray, t_interval t_ray)
{
	vec3_add_scaled(vars->cap_center, cone->cords, cone->vec3, -cone->height
		/ 2.0);
	vec3_sub(vars->p_minus_o, vars->cap_center, ray->origin);
	vars->t = vec3_dot(vars->p_minus_o, cone->vec3) / vars->denom;
	if (!interval_contains(vars->t, t_ray))
		return (0);
	return (1);
}

static int	cone_cap_radius_check(t_cone_cap_vars *vars, t_cone *cone,
		const t_ray *ray)
{
	ray_at(vars->t, *ray, vars->intersection_point);
	vec3_sub(vars->dist_vec, vars->intersection_point, vars->cap_center);
	if (vec3_length(vars->dist_vec) > cone->radius)
		return (0);
	return (1);
}

static void	set_cone_cap_record(t_cone *cone, const t_ray *ray,
		t_cone_cap_vars *vars, t_hit_record *record)
{
	record->t = vars->t;
	ray_at(vars->t, *ray, record->position);
	vec3_negate(record->normal, cone->vec3);
	record->material = &cone->material;
}

bool	have_hit_cone_cap(t_cone *cone, const t_ray *ray, t_interval t_ray,
		t_hit_record *record)
{
	t_cone_cap_vars	vars;

	if (!cone_cap_denom_check(&vars, cone, ray))
		return (false);
	if (!cone_cap_t_check(&vars, cone, ray, t_ray))
		return (false);
	if (!cone_cap_radius_check(&vars, cone, ray))
		return (false);
	set_cone_cap_record(cone, ray, &vars, record);
	return (true);
}
