/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:10:49 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/12 16:38:42 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void set_hit_record(bool *hit, double *closest_so_far, t_hit_record *record,
					t_hit_record *temp_rec)
{
	*hit = true;
	*closest_so_far = temp_rec->t;
	*record = *temp_rec;
}

bool hit_world(t_control_panel *scene, const t_ray *ray, t_interval t_ray,
			   t_hit_record *record)
{
	t_hit_record temp_rec;
	t_texture	*texture;
	bool hit_anything;
	double closest_so_far;

	texture = NULL;
	hit_anything = false;
	closest_so_far = t_ray.max;
	if (hit_spheres(scene, ray, interval_create(t_ray.min, closest_so_far),
					&temp_rec))
		set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
	if (hit_planes(scene, ray, interval_create(t_ray.min, closest_so_far),
				   &temp_rec))
		set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
	if (hit_cylinders(scene, ray, interval_create(t_ray.min, closest_so_far),
					  &temp_rec))
		set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
	if (hit_cones(scene, ray, interval_create(t_ray.min, closest_so_far),
				  &temp_rec))
		set_hit_record(&hit_anything, &closest_so_far, record, &temp_rec);
	if (hit_anything)
		apply_bump_map(scene, record, texture);
	return (hit_anything);
}

void random_on_hemisphere(double normal[3], double out[3])
{
	double on_unit_sphere[3];

	vec3_zero(on_unit_sphere);
	vec3_random_utit_vector(on_unit_sphere);
	if (vec3_dot(on_unit_sphere, normal) > 0.0)
		vec3_copy(out, on_unit_sphere);
	else
		vec3_negate(out, on_unit_sphere);
}
