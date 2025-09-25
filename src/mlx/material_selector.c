/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:35:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/18 12:46:03 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	draw_dropdown_background(t_control_panel *cp,
		t_mat_select *selector, int dropdown_y)
{
	t_rect	rect;

	rect.x = selector->x;
	rect.y = dropdown_y;
	rect.width = selector->width;
	rect.height = selector->dropdown_height;
	draw_filled_rectangle(cp, rect, 0x404040);
	draw_border(cp, rect, 0xFFFFFF);
}

static void	draw_single_dropdown_item(t_control_panel *cp,
		t_mat_select *selector, int i, int dropdown_y)
{
	int		item_y;
	int		item_color;
	t_rect	rect;

	item_y = dropdown_y + (i * selector->item_height);
	item_color = 0x404040;
	if (i == selector->hover_index)
		item_color = 0x606060;
	if (i == selector->selected_material)
		item_color = 0x808080;
	rect.x = selector->x + 2;
	rect.y = item_y + 1;
	rect.width = selector->width - 4;
	rect.height = selector->item_height - 2;
	draw_filled_rectangle(cp, rect, item_color);
	draw_text_at_position(cp, selector->x + 10, item_y + 20,
		selector->material_names[i]);
}

static void	draw_dropdown_items(t_control_panel *cp, t_mat_select *selector)
{
	int	dropdown_y;
	int	i;

	dropdown_y = selector->y + selector->height;
	draw_dropdown_background(cp, selector, dropdown_y);
	i = 0;
	while (i < 4)
	{
		draw_single_dropdown_item(cp, selector, i, dropdown_y);
		i++;
	}
}

static void	draw_selector_button(t_control_panel *cp, t_mat_select *selector)
{
	t_rect	rect;

	rect.x = selector->x;
	rect.y = selector->y;
	rect.width = selector->width;
	rect.height = selector->height;
	draw_filled_rectangle(cp, rect, 0x404040);
	draw_border(cp, rect, 0xFFFFFF);
	draw_text_at_position(cp, selector->x + 10, selector->y + 20,
		selector->material_names[selector->selected_material]);
	draw_arrow_down(cp, selector->x + selector->width - 15, selector->y + 12);
}

void	draw_material_selector(t_control_panel *cp)
{
	t_mat_select	*selector;

	if (!cp || !cp->config_win)
		return ;
	selector = &cp->config_win->material_selector;
	draw_selector_button(cp, selector);
	if (selector->is_open)
		draw_dropdown_items(cp, selector);
}
