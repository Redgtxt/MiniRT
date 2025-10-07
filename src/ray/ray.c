/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:06:32 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/07 17:06:35 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	process_lights(t_control_panel *panel, t_hit_record *rec,
		const t_ray *ray, vec3 color[3])
{
	size_t			i;
	t_light_args	light_args;

	i = 0;
	while (i < panel->data.light_count)
	{
		light_args.panel = panel;
		light_args.rec = rec;
		light_args.ray = ray;
		light_args.color = color;
		light_args.i = i;
		process_light(&light_args);
		i++;
	}
}

static void	process_scatter(t_scatter_args *args, vec3 color[3])
{
	t_data_scatter	data_scatter;
	vec3			scattered_color[3];

	if (scatter(args->rec->material, args->ray, args->rec, &data_scatter))
	{
		ray_color(args->panel, args->depth - 1, &data_scatter.scattered,
			scattered_color);
		vec3_multiply(scattered_color, scattered_color,
			data_scatter.attenuation);
		vec3_add(color, color, scattered_color);
	}
}

void	init_scatter_args(t_scatter_args *args, int depth, const t_ray *ray,
		t_hit_record *rec)
{
	args->depth = depth;
	args->ray = ray;
	args->rec = rec;
}

void	ray_color(t_control_panel *panel, int depth, const t_ray *ray,
		double out_color[3])
{
	t_hit_record	rec;
	vec3			color[3];
	t_scatter_args	scatter_args;

	if (depth <= 0)
	{
		vec3_zero(out_color);
		return ;
	}
	vec3_zero(color);
	if (hit_world(panel, ray, interval_create(0.001, D_INFINITY), &rec))
	{
		if (rec.material->type != GLASS)
			process_lights(panel, &rec, ray, color);
		if (rec.material->type == SOLID)
			solid_scatter(panel, &rec, color);
		else
		{
			scatter_args.panel = panel;
			scatter_args.depth = depth;
			scatter_args.ray = ray;
			scatter_args.rec = &rec;
			process_scatter(&scatter_args, color);
		}
		vec3_copy(out_color, color);
	}
	else
		set_amb_light(panel, ray, out_color);
}
