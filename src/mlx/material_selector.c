/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:35:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/15 14:30:00 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void draw_slider_handle_improved(t_control_panel *cp, t_rect rect, int color)
{
    draw_filled_rectangle(cp, rect, color);
    draw_border(cp, rect, 0xFFFFFF);
    draw_handle_highlight(cp, rect.x, rect.y, rect.width);
}

static void draw_dropdown_items(t_control_panel *cp, t_material_selector *selector)
{
    int dropdown_y;
    int i;
    int item_y;
    int item_color;

    dropdown_y = selector->y + selector->height;
    draw_filled_rectangle(cp, selector->x, dropdown_y, selector->width,
                          selector->dropdown_height, 0x404040);
    draw_border(cp, selector->x, dropdown_y, selector->width,
                selector->dropdown_height, 0xFFFFFF);
    i = 0;
    while (i < 5)
    {
        item_y = dropdown_y + (i * selector->item_height);
        item_color = 0x404040;
        if (i == selector->hover_index)
            item_color = 0x606060;
        if (i == selector->selected_material)
            item_color = 0x808080;
        draw_filled_rectangle(cp, selector->x + 2, item_y + 1,
                              selector->width - 4, selector->item_height - 2, item_color);
        draw_text_at_position(cp, selector->x + 10, item_y + 20,
                              selector->material_names[i]);
        i++;
    }
}

void draw_material_selector(t_control_panel *cp)
{
    t_material_selector *selector;

    if (!cp || !cp->config_win)
        return;
    selector = &cp->config_win->material_selector;
    draw_selector_button(cp, selector);
    if (selector->is_open)
        draw_dropdown_items(cp, selector);
}
