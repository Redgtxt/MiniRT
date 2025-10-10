/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:57:21 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/10 11:53:14 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	init_cone_body_vars(t_cone_body_vars *vars, t_cone *cone,
		const t_ray *ray)
{
	vec3_add_scaled(vars->cone_tip, cone->cords, cone->vec3, cone->height
		/ 2.0);
	vec3_sub(vars->oc, ray->origin, vars->cone_tip);
	vars->tan_theta = cone->radius / cone->height;
	vars->k = vars->tan_theta * vars->tan_theta;
	vars->dot_d_v = vec3_dot(ray->direction, cone->vec3);
	vars->dot_oc_v = vec3_dot(vars->oc, cone->vec3);
	vars->a = vec3_dot(ray->direction, ray->direction) - (1 + vars->k)
		* vars->dot_d_v * vars->dot_d_v;
	vars->b = 2 * (vec3_dot(ray->direction, vars->oc) - (1 + vars->k)
			* vars->dot_d_v * vars->dot_oc_v);
	vars->c = vec3_dot(vars->oc, vars->oc) - (1 + vars->k) * vars->dot_oc_v
		* vars->dot_oc_v;
}

static int	cone_body_discriminant_check(t_cone_body_vars *vars)
{
	vars->discriminant = vars->b * vars->b - 4 * vars->a * vars->c;
	if (vars->discriminant < 0)
		return (0);
	vars->sqrt_d = sqrt(vars->discriminant);
	return (1);
}

static int	cone_body_t_check(t_cone_body_vars *vars, t_cone *cone,
		t_interval t_ray)
{
	vars->t1 = (-vars->b - vars->sqrt_d) / (2 * vars->a);
	vars->t2 = (-vars->b + vars->sqrt_d) / (2 * vars->a);
	vars->t = -1;
	vars->m1 = vars->dot_d_v * vars->t1 + vars->dot_oc_v;
	if (interval_contains(vars->t1, t_ray) && vars->m1 < 0 && vars->m1
		> -cone->height)
		vars->t = vars->t1;
	vars->m2 = vars->dot_d_v * vars->t2 + vars->dot_oc_v;
	if (interval_contains(vars->t2, t_ray) && vars->m2 < 0 && vars->m2
		> -cone->height)
	{
		if (vars->t < 0 || vars->t2 < vars->t)
			vars->t = vars->t2;
	}
	if (vars->t < 0)
		return (0);
	return (1);
}

static void	set_cone_body_record(t_cone *cone, const t_ray *ray,
		t_cone_body_vars *vars, t_hit_record *record)
{
	double	outward_normal[3];

	record->t = vars->t;
	ray_at(vars->t, *ray, record->position);
	vars->m = vars->dot_d_v * vars->t + vars->dot_oc_v;
	vec3_scale(vars->temp, cone->vec3, vars->m * (1 + vars->k));
	vec3_sub(vars->p_minus_c, record->position, vars->cone_tip);
	vec3_sub(vars->normal, vars->p_minus_c, vars->temp);
	vec3_normalize(outward_normal, vars->normal);
	set_face_normal(ray, outward_normal, record);
	record->material = &cone->material;
}

bool	hit_cone_body(t_cone *cone, const t_ray *ray, t_interval t_ray,
		t_hit_record *record)
{
	t_cone_body_vars	vars;

	init_cone_body_vars(&vars, cone, ray);
	if (!cone_body_discriminant_check(&vars))
		return (false);
	if (!cone_body_t_check(&vars, cone, t_ray))
		return (false);
	set_cone_body_record(cone, ray, &vars, record);
	return (true);
}
