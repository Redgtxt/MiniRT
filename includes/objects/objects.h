/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "../core/types.h"
# include "../graphics/materials.h"
# include "../math/interval.h"
# include "../math/vec3.h"

/* Object hit detection functions */
bool	hit_world(t_control_panel *scene, const t_ray *ray, t_interval t_ray,
			t_hit_record *record);
void	set_hit_record(bool *hit, double *closest_so_far, t_hit_record *record,
			t_hit_record *temp_rec);

/* Array conversion functions */
bool	linked_to_array(t_control_panel *control_panel);
bool	linked_list_to_light_array(t_light **light_list, int size_array);
bool	linked_list_to_sphere_array(t_sphere **sphere_list, int size_array);
bool	linked_list_to_plane_array(t_plane **plane_list, int size_array);
bool	linked_list_to_cylinder_array(t_cylinder **cylinder_list,
			int size_array);
bool	linked_list_to_cone_array(t_cone **cone_list, int size_array);

/* Object initialization */
void	init_object_selection(t_control_panel *control_panel);

#endif