/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:19:10 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/09/30 18:34:05 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	plane_denom_check(t_plane_vars *vars, t_plane *plane,
		const t_ray *ray)
{
	vars->denom = vec3_dot(plane->vec3, ray->direction);
	if (fabs(vars->denom) < 0.0001)
		return (0);
	return (1);
}

static int	plane_t_check(t_plane_vars *vars, t_plane *plane, const t_ray *ray,
		t_interval t_ray)
{
	vec3_sub(vars->p0l0, plane->cords, ray->origin);
	vars->t = vec3_dot(vars->p0l0, plane->vec3) / vars->denom;
	if (!interval_surrounds(vars->t, t_ray))
		return (0);
	return (1);
}

static void	set_plane_record(t_plane *plane, const t_ray *ray,
		t_plane_vars *vars, t_hit_record *record)
{
	double	outward_normal[3];

	record->t = vars->t;
	ray_at(record->t, *ray, record->position);
	vec3_copy(outward_normal, plane->vec3);
	vec3_normalize(outward_normal, outward_normal);
	set_face_normal(ray, outward_normal, record);
	record->material = &plane->material;
	get_uv_plane(record, plane);
}

bool	have_hit_plane(t_plane *plane, const t_ray *ray, t_interval t_ray,
		t_hit_record *record)
{
	t_plane_vars	vars;

	if (!plane_denom_check(&vars, plane, ray))
		return (false);
	if (!plane_t_check(&vars, plane, ray, t_ray))
		return (false);
	set_plane_record(plane, ray, &vars, record);
	return (true);
}

bool	hit_planes(t_control_panel *scene, const t_ray *ray, t_interval t_ray,
		t_hit_record *record)
{
	bool			hit_anything;
	double			closest_so_far;
	t_hit_record	temp_rec;
	size_t			i;

	hit_anything = false;
	closest_so_far = t_ray.max;
	ft_memset(&temp_rec, 0, sizeof(t_hit_record));
	i = 0;
	while (i < scene->data.plane_count)
	{
		if (have_hit_plane(&scene->plane[i], ray, interval_create(t_ray.min,
					closest_so_far), &temp_rec))
			set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
		i++;
	}
	return (hit_anything);
}
