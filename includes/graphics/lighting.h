/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "../core/types.h"
# include "../math/vec3.h"
# include "ray.h"

/* Light structures */
typedef struct s_amb_light
{
	double			light_force;
	double			rgb[3];
}					t_amb_light;

typedef struct s_light
{
	t_vec3			cords[3];
	double			brightness;
	double			rgb[3];
	struct s_light	*prev;
	struct s_light	*next;
}					t_light;

/* Light argument structures */
typedef struct s_light_args
{
	t_control_panel	*panel;
	t_hit_record	*rec;
	const t_ray		*ray;
	t_vec3			*color;
	size_t			i;
}					t_light_args;

typedef struct s_intensity_args
{
	t_control_panel	*panel;
	t_light			*light;
	double			*light_distance;
	double			*light_transmission;
}					t_intensity_args;

typedef struct s_intensity_data
{
	t_ray			shadow_ray;
	t_vec3			light_dir[3];
	double			light_distance;
	double			light_transmission;
}					t_intensity_data;

/* Light function prototypes */
double				get_shadow_intensity(t_control_panel *panel,
						t_vec3 point[3], t_light *light);
void				diffuse_comp(t_light_args *args, t_vec3 light_dir[3],
						double attenuation);
void				process_light(t_light_args *args);
void				set_amb_light(t_control_panel *control_panel,
						const t_ray *ray, double out_color[3]);
void				init_spec_args(t_specular_args *spec_args,
						t_light_args *args, t_vec3 light_dir[3],
						double attenuation);
void				add_specular(t_specular_args *args, t_vec3 color[3]);

#endif