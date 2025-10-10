/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_body.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:20:19 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/09/30 16:06:07 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	cylinder_body_discriminant_check(t_cylinder_body_vars *vars)
{
	vars->discriminant = vars->b * vars->b - 4 * vars->a * vars->c;
	if (vars->discriminant < 0)
		return (0);
	vars->sqrt_disc = sqrt(vars->discriminant);
	return (1);
}

static int	cylinder_body_t_check(t_cylinder_body_vars *vars, t_interval t_ray)
{
	vars->t1 = (-vars->b - vars->sqrt_disc) / (2 * vars->a);
	vars->t2 = (-vars->b + vars->sqrt_disc) / (2 * vars->a);
	vars->t = vars->t1;
	if (vars->t < t_ray.min || vars->t > t_ray.max)
	{
		vars->t = vars->t2;
		if (vars->t < t_ray.min || vars->t > t_ray.max)
			return (0);
	}
	return (1);
}

static int	cylinder_body_height_check(t_cylinder_body_vars *vars,
		t_cylinder *cylinder, const t_ray *ray)
{
	ray_at(vars->t, *ray, vars->hit_point);
	vec3_sub(vars->hit_vec, vars->hit_point, cylinder->cords);
	vars->hit_height = vec3_dot(vars->hit_vec, vars->axis);
	if (vars->hit_height < -cylinder->height / 2
		|| vars->hit_height > cylinder->height / 2)
		return (0);
	return (1);
}

static void	set_cylinder_body_record(t_cylinder *cylinder, const t_ray *ray,
		t_cylinder_body_vars *vars, t_hit_record *record)
{
	ray_at(vars->t, *ray, vars->hit_point);
	vec3_sub(vars->hit_vec, vars->hit_point, cylinder->cords);
	vars->hit_height = vec3_dot(vars->hit_vec, vars->axis);
	record->t = vars->t;
	vec3_copy(record->position, vars->hit_point);
	vec3_scale(vars->cp, vars->axis, vars->hit_height);
	vec3_add(vars->cp, cylinder->cords, vars->cp);
	vec3_sub(vars->outward_normal, vars->hit_point, vars->cp);
	vec3_normalize(vars->outward_normal, vars->outward_normal);
	set_face_normal(ray, vars->outward_normal, record);
	record->material = &cylinder->material;
	get_uv_cylinder(record, cylinder);
}

bool	hit_cylinder_body(t_cylinder *cylinder, const t_ray *ray,
		t_interval t_ray, t_hit_record *record)
{
	t_cylinder_body_vars	vars;

	init_cylinder_body_vars(&vars, cylinder, ray);
	if (!cylinder_body_discriminant_check(&vars))
		return (false);
	if (!cylinder_body_t_check(&vars, t_ray))
		return (false);
	if (!cylinder_body_height_check(&vars, cylinder, ray))
		return (false);
	set_cylinder_body_record(cylinder, ray, &vars, record);
	return (true);
}
