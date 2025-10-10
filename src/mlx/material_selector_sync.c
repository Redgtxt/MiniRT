/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_selector_sync.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:26:46 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/10 00:27:41 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	get_current_material_type(t_control_panel *cp)
{
	if (!cp || !cp->config_win)
		return (-1);
	if (is_valid_sphere(cp) && cp->sphere)
		return (cp->sphere[cp->data.idx_obj].material.type);
	if (is_valid_plane(cp) && cp->plane)
		return (cp->plane[cp->data.idx_obj].material.type);
	if (is_valid_cylinder(cp) && cp->cylinder)
		return (cp->cylinder[cp->data.idx_obj].material.type);
	if (is_valid_cone(cp) && cp->cone)
		return (cp->cone[cp->data.idx_obj].material.type);
	return (-1);
}

void	update_material_selector_from_selected_object(t_control_panel *cp)
{
	int				type;
	t_mat_select	*sel;

	if (!cp || !cp->config_win)
		return ;
	sel = &cp->config_win->material_selector;
	type = get_current_material_type(cp);
	if (type >= 0 && type < 5)
		sel->selected_material = type;
}
