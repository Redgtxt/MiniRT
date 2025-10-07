/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:22:02 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/07 17:04:58 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	have_hit_cylinder_caps(t_have_hit_cylinder_vars *vars,
		const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
	vec3_copy(vars->cylinder->cords, vars->original_cylinder.cords);
	vec3_add_dir(vars->cylinder->cords, vars->axis,
		vars->original_cylinder.height / 2);
	vec3_copy(vars->cylinder->vec3, vars->axis);
	if (have_hit_cylinder_cap(vars->cylinder, ray, interval_create(t_ray.min,
				vars->closest_so_far), &vars->temp_rec))
	{
		vars->hit_anything = true;
		vars->closest_so_far = vars->temp_rec.t;
		*record = vars->temp_rec;
	}
	vec3_copy(vars->cylinder->cords, vars->original_cylinder.cords);
	vec3_add_dir(vars->cylinder->cords, vars->axis,
		-vars->original_cylinder.height / 2);
	vec3_copy(vars->cylinder->vec3, vars->axis);
	if (have_hit_cylinder_cap(vars->cylinder, ray, interval_create(t_ray.min,
				vars->closest_so_far), &vars->temp_rec))
	{
		vars->hit_anything = true;
		vars->closest_so_far = vars->temp_rec.t;
		*record = vars->temp_rec;
	}
}

static void	have_hit_cylinder_body(t_have_hit_cylinder_vars *vars,
		const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
	*vars->cylinder = vars->original_cylinder;
	if (hit_cylinder_body(vars->cylinder, ray, interval_create(t_ray.min,
				vars->closest_so_far), &vars->temp_rec))
	{
		vars->hit_anything = true;
		vars->closest_so_far = vars->temp_rec.t;
		*record = vars->temp_rec;
	}
}

bool	have_hit_cylinder(t_cylinder *cylinder, const t_ray *ray,
		t_interval t_ray, t_hit_record *record)
{
	t_have_hit_cylinder_vars	vars;

	init_have_hit_cylinder_struct(&vars, cylinder, t_ray);
	have_hit_cylinder_caps(&vars, ray, t_ray, record);
	have_hit_cylinder_body(&vars, ray, t_ray, record);
	*cylinder = vars.original_cylinder;
	vec3_copy(cylinder->rgb, vars.original_rgb);
	vec3_copy(cylinder->material.albedo, vars.original_rgb);
	return (vars.hit_anything);
}

bool	hit_cylinders(t_control_panel *scene, const t_ray *ray,
		t_interval t_ray, t_hit_record *record)
{
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	size_t			i;

	hit_anything = false;
	closest_so_far = t_ray.max;
	ft_memset(&temp_rec, 0, sizeof(t_hit_record));
	i = 0;
	while (i < scene->data.cylinder_count)
	{
		if (have_hit_cylinder(&scene->cylinder[i], ray,
				interval_create(t_ray.min, closest_so_far), &temp_rec))
			set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
		i++;
	}
	return (hit_anything);
}
