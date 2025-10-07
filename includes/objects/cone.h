/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "../core/types.h"
# include "../graphics/materials.h"
# include "../math/interval.h"
# include "../math/vec3.h"

/* Cone structure */
typedef struct s_cone
{
	vec3			cords[3];
	vec3			vec3[3];
	double			d;
	double			radius;
	double			height;
	double			rgb[3];
	t_material		material;
	struct s_cone	*prev;
	struct s_cone	*next;
}					t_cone;

/* Cone collision variables */
typedef struct s_cone_cap_vars
{
	double			cap_center[3];
	double			p_minus_o[3];
	double			intersection_point[3];
	double			dist_vec[3];
	double			denom;
	double			t;
}					t_cone_cap_vars;

typedef struct s_cone_body_vars
{
	double			oc[3];
	double			tan_theta;
	double			k;
	double			dot_d_v;
	double			dot_oc_v;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			sqrt_d;
	double			t1;
	double			t2;
	double			t;
	double			m1;
	double			m2;
	double			m;
	double			temp[3];
	double			normal[3];
	double			p_minus_c[3];
	double			cone_tip[3];
}					t_cone_body_vars;

/* Cone function prototypes */
bool				have_hit_cone(t_cone *cone, const t_ray *ray,
						t_interval t_ray, t_hit_record *record);
bool				hit_cones(t_control_panel *scene, const t_ray *ray,
						t_interval t_ray, t_hit_record *record);
bool				have_hit_cone_cap(t_cone *cone, const t_ray *ray,
						t_interval t_ray, t_hit_record *record);
bool				hit_cone_body(t_cone *cone, const t_ray *ray,
						t_interval t_ray, t_hit_record *record);

/* Cone list management */
void				lstadd_last_cone(t_control_panel *control_panel,
						t_cone *new_cone);
void				free_cone(t_cone *cone);

#endif