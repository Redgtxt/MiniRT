/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:36:34 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/10 15:54:46 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void init_sphere_vars(t_sphere_vars *vars, const t_ray *ray,
							 t_sphere *sphere)
{
	vec3_sub(vars->oc, ray->origin, sphere->cords);
	vars->a = vec3_dot(ray->direction, ray->direction);
	vars->h = vec3_dot(ray->direction, vars->oc);
	vars->c = vec3_dot(vars->oc, vars->oc) - sphere->radius * sphere->radius;
}

static bool find_sphere_root(t_sphere_vars *vars, t_interval t_ray)
{
	double sqrtd;

	sqrtd = sqrt(vars->discriminant);
	vars->root = (-vars->h - sqrtd) / vars->a;
	if (!interval_surrounds(vars->root, t_ray))
	{
		vars->root = (-vars->h + sqrtd) / vars->a;
		if (!interval_surrounds(vars->root, t_ray))
			return (false);
	}
	return (true);
}

static void set_sphere_record(t_sphere *sphere, const t_ray *ray, double root,
							  t_hit_record *record)
{
	double outward_normal[3];

	record->t = root;
	ray_at(record->t, *ray, record->position);
	vec3_sub(outward_normal, record->position, sphere->cords);
	vec3_normalize(outward_normal, outward_normal);
	set_face_normal(ray, outward_normal, record);
	get_uv_sphere(record, sphere);
	record->material = &sphere->material;
}

bool have_hit_sphere(t_sphere *sphere, const t_ray *ray, t_interval t_ray,
					 t_hit_record *record)
{
	t_sphere_vars vars;

	init_sphere_vars(&vars, ray, sphere);
	vars.discriminant = vars.h * vars.h - vars.a * vars.c;
	if (vars.discriminant < 0)
		return (false);
	if (!find_sphere_root(&vars, t_ray))
		return (false);
	set_sphere_record(sphere, ray, vars.root, record);
	return (true);
}

bool hit_spheres(t_control_panel *scene, const t_ray *ray, t_interval t_ray,
				 t_hit_record *record)
{
	bool hit_anything;
	double closest_so_far;
	t_hit_record temp_rec;
	size_t i;

	hit_anything = false;
	closest_so_far = t_ray.max;
	ft_memset(&temp_rec, 0, sizeof(t_hit_record));
	i = 0;
	while (i < scene->data.sphere_count)
	{
		if (have_hit_sphere(&scene->sphere[i], ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
			set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
		i++;
	}
	return (hit_anything);
}
