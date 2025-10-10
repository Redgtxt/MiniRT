/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:20:14 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/09/30 16:05:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	cylinder_cap_denom_check(t_cylinder_cap_vars *vars)
{
	if (fabs(vars->denom) < 0.0001)
		return (0);
	return (1);
}

static int	cylinder_cap_t_check(t_cylinder_cap_vars *vars,
		t_cylinder *cylinder, const t_ray *ray, t_interval t_ray)
{
	vec3_sub(vars->p0l0, cylinder->cords, ray->origin);
	vars->t = vec3_dot(vars->p0l0, vars->normalized_axis) / vars->denom;
	if (!interval_surrounds(vars->t, t_ray))
		return (0);
	return (1);
}

static int	cylinder_cap_radius_check(t_cylinder_cap_vars *vars,
		t_cylinder *cylinder, const t_ray *ray)
{
	ray_at(vars->t, *ray, vars->outward_normal);
	if (pont_dist(vars->outward_normal, cylinder->cords) <= cylinder->radius)
		return (1);
	return (0);
}

static void	set_cylinder_cap_record(t_cylinder *cylinder, const t_ray *ray,
		t_cylinder_cap_vars *vars, t_hit_record *record)
{
	record->t = vars->t;
	ray_at(vars->t, *ray, record->position);
	vec3_copy(vars->outward_normal, vars->normalized_axis);
	set_face_normal(ray, vars->outward_normal, record);
	record->material = &cylinder->material;
	get_uv_cylinder(record, cylinder);
}

bool	have_hit_cylinder_cap(t_cylinder *cylinder, const t_ray *ray,
		t_interval t_ray, t_hit_record *record)
{
	t_cylinder_cap_vars	vars;

	init_cylinder_cap_vars(&vars, cylinder, ray);
	if (!cylinder_cap_denom_check(&vars))
		return (false);
	if (!cylinder_cap_t_check(&vars, cylinder, ray, t_ray))
		return (false);
	if (!cylinder_cap_radius_check(&vars, cylinder, ray))
		return (false);
	set_cylinder_cap_record(cylinder, ray, &vars, record);
	return (true);
}
