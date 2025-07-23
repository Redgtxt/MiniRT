/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:20:50 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/23 15:20:52 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	is_valid_sphere(t_control_panel *cp)
{
	return (cp->data.obj_type == 0 && cp->data.idx_obj >= 0
		&& cp->data.idx_obj < (int)cp->data.sphere_count);
}

int	is_valid_plane(t_control_panel *cp)
{
	return (cp->data.obj_type == 1 && cp->data.idx_obj >= 0
		&& cp->data.idx_obj < (int)cp->data.plane_count);
}

int	is_valid_cylinder(t_control_panel *cp)
{
	return (cp->data.obj_type == 2 && cp->data.idx_obj >= 0
		&& cp->data.idx_obj < (int)cp->data.cylinder_count);
}

int	is_valid_cone(t_control_panel *cp)
{
	return (cp->data.obj_type == 3 && cp->data.idx_obj >= 0
		&& cp->data.idx_obj < (int)cp->data.cone_count);
}
