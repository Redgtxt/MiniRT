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

void	free_light(t_light *light)
{
	t_light	*temp;

	temp = light;
	while (temp)
	{
		temp = temp->next;
		free(light);
		light = temp;
	}
}

void	free_sphere(t_sphere *sphere)
{
	t_sphere	*temp;

	temp = sphere;
	while (temp)
	{
		temp = temp->next;
		free(sphere);
		sphere = temp;
	}
}

void	free_plane(t_plane *plane)
{
	t_plane	*temp;

	temp = plane;
	while (temp)
	{
		temp = temp->next;
		free(plane);
		plane = temp;
	}
}

void	free_cylinder(t_cylinder *cylinder)
{
	t_cylinder	*temp;

	temp = cylinder;
	while (temp)
	{
		temp = temp->next;
		free(cylinder);
		cylinder = temp;
	}
}

void	free_cone(t_cone *cone)
{
	t_cone	*temp;

	temp = cone;
	while (temp)
	{
		temp = temp->next;
		free(cone);
		cone = temp;
	}
}

void	free_control_panel(t_control_panel *control_panel)
{
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
	if (control_panel->error_log.element)
		free(control_panel->error_log.element);
	free(control_panel);
}