/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/07/16 17:31:56 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool linked_to_array(t_control_panel *control_panel)
{
	if (control_panel->data.light_count)
	{
		if (!linked_list_to_light_array(&control_panel->light, control_panel->data.light_count))
			return (false);
	}
	if (control_panel->data.sphere_count)
	{
		if (!linked_list_to_sphere_array(&control_panel->sphere, control_panel->data.sphere_count))
			return (false);
	}
	if (control_panel->data.plane_count)
	{
		if (!linked_list_to_plane_array(&control_panel->plane, control_panel->data.plane_count))
			return (false);
	}
	if (control_panel->data.cylinder_count)
	{
		if (!linked_list_to_cylinder_array(&control_panel->cylinder, control_panel->data.cylinder_count))
			return (false);
	}
	if (control_panel->data.cone_count)
	{
		if (!linked_list_to_cone_array(&control_panel->cone, control_panel->data.cone_count))
			return (false);
	}
	return (true);
}


