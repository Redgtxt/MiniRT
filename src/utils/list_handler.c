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

void	lstadd_last_light(t_control_panel *control_panel, t_light *new_light)
{
	t_light	*temp;
	t_light	*last;

	last = NULL;
	temp = control_panel->light;
	if (control_panel == NULL || new_light == NULL)
		return ;
	if (control_panel->light)
	{
		while (temp)
		{
			last = temp;
			temp = temp->next;
		}
		last->next = new_light;
		new_light->prev = last;
	}
	else
	{
		control_panel->light = new_light;
		new_light->prev = NULL;
	}
	new_light->next = NULL;
}

void	lstadd_last_sphere(t_control_panel *control_panel, t_sphere *new_sphere)
{
	t_sphere	*temp;
	t_sphere	*last;

	last = NULL;
	temp = control_panel->sphere;
	if (control_panel == NULL || new_sphere == NULL)
		return ;
	if (control_panel->sphere)
	{
		while (temp)
		{
			last = temp;
			temp = temp->next;
		}
		last->next = new_sphere;
		new_sphere->prev = last;
	}
	else
	{
		control_panel->sphere = new_sphere;
		new_sphere->prev = NULL;
	}
	new_sphere->next = NULL;
}

void	lstadd_last_plane(t_control_panel *control_panel, t_plane *new_plane)
{
	t_plane	*temp;
	t_plane	*last;

	last = NULL;
	temp = control_panel->plane;
	if (control_panel == NULL || new_plane== NULL)
		return ;
	if (control_panel->plane)
	{
		while (temp)
		{
			last = temp;
			temp = temp->next;
		}
		last->next = new_plane;
		new_plane->prev = last;
	}
	else
	{
		control_panel->plane = new_plane;
		new_plane->prev = NULL;
	}
	new_plane->next = NULL;
}

void	lstadd_last_cylinder(t_control_panel *control_panel, t_cylinder *new_cylinder)
{
	t_cylinder	*temp;
	t_cylinder	*last;

	last = NULL;
	temp = control_panel->cylinder;
	if (control_panel == NULL || new_cylinder== NULL)
		return ;
	if (control_panel->cylinder)
	{
		while (temp)
		{
			last = temp;
			temp = temp->next;
		}
		last->next = new_cylinder;
		new_cylinder->prev = last;
	}
	else
	{
		control_panel->cylinder = new_cylinder;
		new_cylinder->prev = NULL;
	}
	new_cylinder->next = NULL;
}

void	lstadd_last_cone(t_control_panel *control_panel, t_cone *new_cone)
{
	t_cone *temp;
	t_cone *last;

	last = NULL;
	temp = control_panel->cone;
	if (control_panel == NULL || new_cone== NULL)
		return ;
	if (control_panel->cone)
	{
		while (temp)
		{
			last = temp;
			temp = temp->next;
		}
		last->next = new_cone;
		new_cone->prev = last;
	}
	else
	{
		control_panel->cone = new_cone;
		new_cone->prev = NULL;
	}
	new_cone->next = NULL;
}
