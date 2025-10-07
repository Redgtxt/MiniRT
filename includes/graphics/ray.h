/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "../core/types.h"
# include "../math/interval.h"
# include "../math/vec3.h"

/* Ray structure */
typedef struct s_ray
{
	vec3			origin[3];
	double			direction[3];
}					t_ray;

/* Hit record structure */
typedef struct s_hit_record
{
	double			position[3];
	double			normal[3];
	double			t;
	bool			front_face;
	t_material		*material;
}					t_hit_record;

/* Ray argument structures for complex functions */
typedef struct s_specular_args
{
	t_hit_record	*rec;
	const t_ray		*ray;
	vec3			*light_dir;
	t_light			*light;
	double			attenuation;
}					t_specular_args;

typedef struct s_scatter_args
{
	t_control_panel	*panel;
	int				depth;
	const t_ray		*ray;
	t_hit_record	*rec;
}					t_scatter_args;

/* Ray function prototypes */
void				init_ray(t_ray *ray);
void				create_ray(t_ray *ray, const double origin[3],
						const double direction[3]);
void				ray_origin(const t_ray *ray, double out[3]);
void				ray_direction(const t_ray *ray, double out[3]);
void				ray_at(double t, t_ray ray, double result[3]);
void				ray_color(t_control_panel *control_panel, int depth,
						const t_ray *ray, double out_color[3]);
t_ray				get_ray(t_coord coord, t_control_panel *control_panel);

/* Hit detection functions */
void				set_face_normal(const t_ray *ray,
						const double outward_normal[3], t_hit_record *record);
void				random_on_hemisphere(double normal[3], double out[3]);

#endif