/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_click_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:28:17 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/17 14:28:49 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	check_sphere_hit(t_control_panel *cp, t_ray *ray,
		t_hit_record *record, int *obj_type)
{
	size_t			i;
	t_hit_record	sphere_record;
	t_interval		t_ray;

	t_ray = interval_create(0.001, D_INFINITY);
	i = 0;
	while (i < cp->data.sphere_count)
	{
		if (have_hit_sphere(&cp->sphere[i], ray, t_ray, &sphere_record))
		{
			if (fabs(sphere_record.t - record->t) < 0.001)
			{
				*obj_type = 0;
				return ((int)i);
			}
		}
		i++;
	}
	return (-1);
}

static int	check_plane_hit(t_control_panel *cp, t_ray *ray,
		t_hit_record *record, int *obj_type)
{
	size_t			i;
	t_hit_record	plane_record;
	t_interval		t_ray;

	t_ray = interval_create(0.001, D_INFINITY);
	i = 0;
	while (i < cp->data.plane_count)
	{
		if (have_hit_plane(&cp->plane[i], ray, t_ray, &plane_record))
		{
			if (fabs(plane_record.t - record->t) < 0.001)
			{
				*obj_type = 1;
				return ((int)i);
			}
		}
		i++;
	}
	return (-1);
}

static int	check_cylinder_hit(t_control_panel *cp, t_ray *ray,
		t_hit_record *record, int *obj_type)
{
	size_t			i;
	t_hit_record	cylinder_record;
	t_interval		t_ray;

	t_ray = interval_create(0.001, D_INFINITY);
	i = 0;
	while (i < cp->data.cylinder_count)
	{
		if (have_hit_cylinder(&cp->cylinder[i], ray, t_ray, &cylinder_record))
		{
			if (fabs(cylinder_record.t - record->t) < 0.001)
			{
				*obj_type = 2;
				return ((int)i);
			}
		}
		i++;
	}
	return (-1);
}

static int	check_cone_hit(t_control_panel *cp, t_ray *ray,
		t_hit_record *record, int *obj_type)
{
	size_t			i;
	t_hit_record	cone_record;
	t_interval		t_ray;

	t_ray = interval_create(0.001, D_INFINITY);
	i = 0;
	while (i < cp->data.cone_count)
	{
		if (have_hit_cone(&cp->cone[i], ray, t_ray, &cone_record))
		{
			if (fabs(cone_record.t - record->t) < 0.001)
			{
				*obj_type = 3;
				return ((int)i);
			}
		}
		i++;
	}
	return (-1);
}

int	find_clicked_object(t_control_panel *cp, int mouse_x, int mouse_y,
		int *obj_type)
{
	t_ray			ray;
	t_hit_record	record;
	int				result;
	t_interval		t_ray;

	ray = get_ray(mouse_x, mouse_y, cp);
	t_ray = interval_create(0.001, D_INFINITY);
	if (!hit_world(cp, &ray, t_ray, &record))
		return (-1);
	result = check_sphere_hit(cp, &ray, &record, obj_type);
	if (result != -1)
		return (result);
	result = check_plane_hit(cp, &ray, &record, obj_type);
	if (result != -1)
		return (result);
	result = check_cylinder_hit(cp, &ray, &record, obj_type);
	if (result != -1)
		return (result);
	result = check_cone_hit(cp, &ray, &record, obj_type);
	if (result != -1)
		return (result);
	return (-1);
}
