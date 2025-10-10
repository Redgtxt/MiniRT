/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:24:53 by randrade          #+#    #+#             */
/*   Updated: 2025/01/15 12:52:36 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void free_control_panel(t_control_panel *control_panel)
{
	size_t i;

	if (control_panel->light)
		free_light(control_panel->light);
	if (control_panel->sphere)
		free_sphere(control_panel->sphere);
	if (control_panel->plane)
		free_plane(control_panel->plane);
	if (control_panel->cylinder)
		free_cylinder(control_panel->cylinder);
	if (control_panel->cone)
		free_cone(control_panel->cone);
	if (control_panel->textures)
	{
		i = 0;
		while (i < control_panel->data.texture_count)
		{
			if (control_panel->textures[i].filepath)
				free(control_panel->textures[i].filepath);
			i++;
		}
		free(control_panel->textures);
	}
	if (control_panel->error_log.element)
		free(control_panel->error_log.element);
	if (control_panel->error_log.error_str_detail)
		free(control_panel->error_log.error_str_detail);
	free(control_panel);
}
