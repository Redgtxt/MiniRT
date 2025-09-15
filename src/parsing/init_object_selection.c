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

void init_object_selection(t_control_panel *control_panel)
{
    // Initialize object type to the first available object type
    if (control_panel->data.sphere_count > 0)
        control_panel->data.obj_type = 0; // Sphere
    else if (control_panel->data.plane_count > 0)
        control_panel->data.obj_type = 1; // Plane
    else if (control_panel->data.cylinder_count > 0)
        control_panel->data.obj_type = 2; // Cylinder
    else if (control_panel->data.cone_count > 0)
        control_panel->data.obj_type = 3; // Cone
    else
        control_panel->data.obj_type = 0; // Default to sphere even if none exist
    control_panel->data.idx_obj = 0; // Initialize to first object
}


