/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_selection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/09/25 17:15:42 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	init_object_selection(t_control_panel *control_panel)
{
	if (control_panel->data.sphere_count > 0)
		control_panel->data.obj_type = 0;
	else if (control_panel->data.plane_count > 0)
		control_panel->data.obj_type = 1;
	else if (control_panel->data.cylinder_count > 0)
		control_panel->data.obj_type = 2;
	else if (control_panel->data.cone_count > 0)
		control_panel->data.obj_type = 3;
	else
		control_panel->data.obj_type = 0;
	control_panel->data.idx_obj = 0;
}
