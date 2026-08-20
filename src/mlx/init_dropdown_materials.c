/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dropdown_materials.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:55:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/03 15:49:49 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	init_mat_select(t_mat_select *selector)
{
	if (!selector)
		return ;
	selector->x = 50;
	selector->y = 375;
	selector->width = 125;
	selector->height = 30;
	selector->dropdown_height = 150;
	selector->is_open = 0;
	selector->selected_material = LAMBERTIAN;
	selector->hover_index = -1;
	selector->item_height = 30;
	selector->material_names[0] = "LAMBERTIAN";
	selector->material_names[1] = "METAL";
	selector->material_names[2] = "CHECKER";
	selector->material_names[3] = "GLASS";
	selector->material_names[4] = "SOLID";
}

int	is_mouse_on_selector_button(t_mat_select *selector, int x, int y)
{
	if (!selector)
		return (0);
	return (x >= selector->x && x <= selector->x + selector->width
		&& y >= selector->y && y <= selector->y + selector->height);
}

int	is_mouse_on_dropdown_area(t_mat_select *selector, int x, int y)
{
	int	dropdown_y;

	if (!selector || !selector->is_open)
		return (0);
	dropdown_y = selector->y + selector->height;
	return (x >= selector->x && x <= selector->x + selector->width
		&& y >= dropdown_y && y <= dropdown_y + selector->dropdown_height);
}

int	is_mouse_on_material_selector(t_mat_select *selector, int x, int y)
{
	if (!selector)
		return (0);
	if (is_mouse_on_selector_button(selector, x, y))
		return (1);
	return (is_mouse_on_dropdown_area(selector, x, y));
}

int	get_dropdown_item_index(t_mat_select *selector, int x, int y)
{
	int	dropdown_y;
	int	relative_y;
	int	index;

	if (!selector || !selector->is_open)
		return (-1);
	dropdown_y = selector->y + selector->height;
	if (x >= selector->x && x <= selector->x + selector->width
		&& y >= dropdown_y && y <= dropdown_y + selector->dropdown_height)
	{
		relative_y = y - dropdown_y;
		index = relative_y / selector->item_height;
		if (index >= 0 && index < 5)
			return (index);
	}
	return (-1);
}
