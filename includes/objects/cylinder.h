/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "../core/types.h"
# include "../graphics/materials.h"
# include "../math/interval.h"
# include "../math/vec3.h"

/* Cylinder structure */
typedef struct s_cylinder
{
	t_vec3				cords[3];
	t_vec3				vec3[3];
	double				d;
	double				radius;
	double				height;
	double				rgb[3];
	t_material			material;
	struct s_cylinder	*prev;
	struct s_cylinder	*next;
}						t_cylinder;

/* Cylinder collision variables */
typedef struct s_cylinder_body_vars
{
	t_vec3				axis[3];
	t_vec3				oc[3];
	double				dir_dot_axis;
	double				oc_dot_axis;
	t_vec3				dir_parallel[3];
	t_vec3				dir_perp[3];
	t_vec3				oc_parallel[3];
	t_vec3				oc_perp[3];
	double				a;
	double				b;
	double				c;
	double				discriminant;
	double				sqrt_disc;
	double				t1;
	double				t2;
	double				t;
	t_vec3				hit_point[3];
	t_vec3				hit_vec[3];
	double				hit_height;
	t_vec3				cp[3];
	t_vec3				outward_normal[3];
}						t_cylinder_body_vars;

typedef struct s_cylinder_cap_vars
{
	double				denom;
	double				p0l0[3];
	double				t;
	t_vec3				normalized_axis[3];
	double				outward_normal[3];
}						t_cylinder_cap_vars;

typedef struct s_have_hit_cylinder_vars
{
	bool				hit_anything;
	double				closest_so_far;
	t_hit_record		temp_rec;
	t_cylinder			*cylinder;
	t_cylinder			original_cylinder;
	double				original_rgb[3];
	t_vec3				axis[3];
}						t_have_hit_cylinder_vars;

/* Cylinder function prototypes */
bool					have_hit_cylinder(t_cylinder *cylinder,
							const t_ray *ray, t_interval t_ray,
							t_hit_record *record);
bool					hit_cylinders(t_control_panel *scene, const t_ray *ray,
							t_interval t_ray, t_hit_record *record);
bool					hit_cylinder_body(t_cylinder *cylinder,
							const t_ray *ray, t_interval t_ray,
							t_hit_record *record);
bool					have_hit_cylinder_cap(t_cylinder *cylinder,
							const t_ray *ray, t_interval t_ray,
							t_hit_record *record);

/* Cylinder utility functions */
double					pont_dist(t_vec3 a[3], t_vec3 b[3]);
void					init_cylinder_cap_vars(t_cylinder_cap_vars *vars,
							t_cylinder *cylinder, const t_ray *ray);
void					init_cylinder_body_vars(t_cylinder_body_vars *vars,
							t_cylinder *cylinder, const t_ray *ray);
void					init_have_hit_cyl_struct(t_have_hit_cylinder_vars *vars,
							t_cylinder *cylinder, t_interval t_ray);

/* Cylinder list management */
void					lstadd_last_cylinder(t_control_panel *control_panel,
							t_cylinder *new_cylinder);
void					free_cylinder(t_cylinder *cylinder);

#endif