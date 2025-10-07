/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "../core/types.h"
# include "../graphics/materials.h"
# include "../math/interval.h"
# include "../math/vec3.h"

/* Sphere structure */
typedef struct s_sphere
{
	vec3			cords[3];
	double			d;
	double			radius;
	double			rgb[3];
	t_material		material;
	struct s_sphere	*prev;
	struct s_sphere	*next;
}					t_sphere;

/* Sphere collision variables */
typedef struct s_sphere_vars
{
	double			oc[3];
	double			a;
	double			h;
	double			c;
	double			discriminant;
	double			root;
}					t_sphere_vars;

/* Sphere function prototypes */
bool				have_hit_sphere(t_sphere *sphere, const t_ray *ray,
						t_interval t_ray, t_hit_record *record);
bool				hit_spheres(t_control_panel *scene, const t_ray *ray,
						t_interval t_ray, t_hit_record *record);

/* Sphere list management */
void				lstadd_last_sphere(t_control_panel *control_panel,
						t_sphere *new_sphere);
void				free_sphere(t_sphere *sphere);

#endif