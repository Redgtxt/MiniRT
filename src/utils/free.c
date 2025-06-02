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

static void	free_sphere(t_control_panel *control_panel)
{
	t_sphere	*temp;

	temp = control_panel->sphere;
	while (temp)
	{
		temp = temp ->next;
		free(control_panel->sphere);
		control_panel->sphere = temp;
	}
}

static void	free_plane(t_control_panel *control_panel)
{
	t_plane	*temp;

	temp = control_panel->plane;
	while (temp)
	{
		temp = temp ->next;
		free(control_panel->plane);
		control_panel->plane = temp;
	}
}

static void	free_cylinder(t_control_panel *control_panel)
{
	t_cylinder	*temp;

	temp = control_panel->cylinder;
	while (temp)
	{
		temp = temp ->next;
		free(control_panel->cylinder);
		control_panel->cylinder = temp;
	}
}

void	free_control_panel(t_control_panel *control_panel)
{
	if (control_panel->sphere)
		free_sphere(control_panel);
    if (control_panel->plane)
    	free_plane(control_panel);
    if (control_panel->cylinder)
   		free_cylinder(control_panel);
    free(control_panel);
}
