/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:41:34 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/13 00:02:50 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	create_shadow_ray(t_vec3 point[3], t_vec3 light_dir[3],
		t_ray *shadow_ray)
{
	t_vec3	shadow_origin[3];

	vec3_scale(shadow_origin, light_dir, 0.001);
	vec3_add(shadow_origin, shadow_origin, point);
	create_ray(shadow_ray, shadow_origin, light_dir);
}

static void	update_ray_after_glass(t_ray *shadow_ray, t_hit_record *rec,
		t_vec3 light_dir[3], t_intensity_args *args)
{
	t_vec3	new_origin[3];
	t_vec3	remaining_dir[3];

	vec3_scale(new_origin, shadow_ray->direction, 0.002);
	vec3_add(new_origin, new_origin, rec->position);
	create_ray(shadow_ray, new_origin, light_dir);
	vec3_sub(remaining_dir, args->light->cords, new_origin);
	*(args->light_distance) = vec3_length(remaining_dir);
}

static bool	process_shadow_hit(t_ray *shadow_ray, t_hit_record *rec,
		t_vec3 light_dir[3], t_intensity_args *args)
{
	if (rec->material->type == GLASS)
	{
		*(args->light_transmission) *= 0.75;
		if (*(args->light_transmission) <= 0.01)
			return (false);
		update_ray_after_glass(shadow_ray, rec, light_dir, args);
		return (true);
	}
	else
	{
		*(args->light_transmission) = 0.0;
		return (false);
	}
}

static void	init_intensity_data(t_intensity_data *data, t_vec3 point[3],
		t_light *light)
{
	vec3_sub(data->light_dir, light->cords, point);
	data->light_distance = vec3_length(data->light_dir);
	vec3_normalize(data->light_dir, data->light_dir);
	create_shadow_ray(point, data->light_dir, &data->shadow_ray);
	data->light_transmission = 1.0;
}

double	get_shadow_intensity(t_control_panel *panel, t_vec3 point[3],
		t_light *light)
{
	t_intensity_data	data;
	t_intensity_args	shadow_args;
	t_hit_record		rec;

	init_intensity_data(&data, point, light);
	shadow_args.panel = panel;
	shadow_args.light = light;
	shadow_args.light_distance = &data.light_distance;
	shadow_args.light_transmission = &data.light_transmission;
	while (hit_world(panel, &data.shadow_ray, interval_create(0.001,
				data.light_distance), &rec))
	{
		if (!process_shadow_hit(&data.shadow_ray, &rec, data.light_dir,
				&shadow_args))
			break ;
	}
	return (data.light_transmission);
}
