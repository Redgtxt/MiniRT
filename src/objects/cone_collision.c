/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:57:21 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/09/30 18:31:24 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	have_hit_cone(t_cone *cone, const t_ray *ray, t_interval t_ray,
		t_hit_record *record)
{
	bool			hit_anything;
	double			closest_so_far;
	t_hit_record	temp_rec;
	t_cone			original_cone;

	hit_anything = false;
	closest_so_far = t_ray.max;
	ft_memset(&temp_rec, 0, sizeof(t_hit_record));
	original_cone = *cone;
	vec3_normalize(cone->vec3, cone->vec3);
	if (hit_cone_body(cone, ray, interval_create(t_ray.min, closest_so_far),
			&temp_rec))
		set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
	if (have_hit_cone_cap(cone, ray, interval_create(t_ray.min, closest_so_far),
			&temp_rec))
		set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
	*cone = original_cone;
	return (hit_anything);
}

bool	hit_cones(t_control_panel *scene, const t_ray *ray, t_interval t_ray,
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
	while (i < scene->data.cone_count)
	{
		if (have_hit_cone(&scene->cone[i], ray, interval_create(t_ray.min,
					closest_so_far), &temp_rec))
			set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
		i++;
	}
	return (hit_anything);
}
