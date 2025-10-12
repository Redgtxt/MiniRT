/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:45:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/12 18:50:35 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECTS_H
# define EFFECTS_H

# include "../core/types.h"
# include "../objects/cone.h"
# include "../objects/cylinder.h"
# include "../objects/plane.h"
# include "../objects/sphere.h"

/* UV mapping functions */
void	get_uv_sphere(t_hit_record *rec, t_sphere *sphere);
void	get_uv_plane(t_hit_record *rec, t_plane *plane);
void	get_uv_cylinder(t_hit_record *rec, t_cylinder *cylinder);
void	get_uv_cone(t_hit_record *rec, t_cone *cone);

/* Bump mapping functions */
void	apply_bump_map(t_control_panel *cp, t_hit_record *rec);

/* Texture mapping functions */
void	apply_texture_color(t_control_panel *cp, t_hit_record *rec,
			double color[3]);

#endif
