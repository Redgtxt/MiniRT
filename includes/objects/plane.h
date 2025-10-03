/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "../core/types.h"
# include "../math/vec3.h"
# include "../math/interval.h"
# include "../graphics/materials.h"

/* Plane structure */
typedef struct s_plane
{
	vec3		cords[3];
	vec3		vec3[3];
	double		rgb[3];
	t_material	material;
	struct s_plane	*prev;
	struct s_plane	*next;
}	t_plane;

/* Plane collision variables */
typedef struct s_plane_vars
{
	double	denom;
	double	p0l0[3];
	double	t;
}	t_plane_vars;

/* Plane function prototypes */
bool	have_hit_plane(t_plane *plane, const t_ray *ray, t_interval t_ray,
			t_hit_record *record);
bool	hit_planes(t_control_panel *scene, const t_ray *ray, t_interval t_ray,
			t_hit_record *record);

/* Plane list management */
void	lstadd_last_plane(t_control_panel *control_panel, t_plane *new_plane);
void	free_plane(t_plane *plane);

#endif