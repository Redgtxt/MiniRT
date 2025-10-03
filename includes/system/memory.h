/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "../core/types.h"

/* Memory management function prototypes */
void	free_light(t_light *light);
void	free_sphere(t_sphere *sphere);
void	free_plane(t_plane *plane);
void	free_cylinder(t_cylinder *cylinder);
void	free_cone(t_cone *cone);
void	free_control_panel(t_control_panel *control_panel);

/* List management functions */
void	lstadd_last_light(t_control_panel *control_panel, t_light *new_light);

#endif