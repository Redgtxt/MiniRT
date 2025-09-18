/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dropdown_interactions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:26:36 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/18 12:46:03 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void handle_selector_button_click(t_mat_select *selector)
{
	if (!selector)
		return;
	selector->is_open = !selector->is_open;
	selector->hover_index = -1;
}

void handle_dropdown_item_click(t_mat_select *selector,
								int item_index)
{
	if (!selector || item_index < 0)
		return;
	selector->selected_material = item_index;
	selector->is_open = 0;
	selector->hover_index = -1;
}

void handle_material_selector_click(t_control_panel *cp, int x, int y)
{
	t_mat_select *selector;
	int item_index;

	if (!cp || !cp->config_win)
		return;
	selector = &cp->config_win->material_selector;
	if (is_mouse_on_selector_button(selector, x, y))
	{
		handle_selector_button_click(selector);
		return;
	}
	if (selector->is_open)
	{
		item_index = get_dropdown_item_index(selector, x, y);
		if (item_index >= 0)
			handle_dropdown_item_click(selector, item_index);
		else
		{
			selector->is_open = 0;
			selector->hover_index = -1;
		}
	}
}

void handle_material_selector_hover(t_control_panel *cp, int x, int y)
{
	t_mat_select *selector;

	if (!cp || !cp->config_win)
		return;
	selector = &cp->config_win->material_selector;
	if (selector->is_open)
		selector->hover_index = get_dropdown_item_index(selector, x, y);
}
