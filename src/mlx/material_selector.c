/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:35:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:27:31 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void init_material_selector(t_material_selector *selector)
{
    if (!selector)
        return;
    selector->x = 50;
    selector->y = 375;
    selector->width = 150;
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
}

static void draw_selector_button(t_control_panel *cp, t_material_selector *selector)
{
    draw_filled_rectangle(cp, selector->x, selector->y, selector->width,
                          selector->height, 0x404040);
    draw_border(cp, selector->x, selector->y, selector->width, selector->height, 0xFFFFFF);
    draw_text_at_position(cp, selector->x + 10, selector->y + 20,
                          selector->material_names[selector->selected_material]);
    draw_arrow_down(cp, selector->x + selector->width - 20, selector->y + 10);
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
    while (i < 4)
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

int is_mouse_on_selector_button(t_material_selector *selector, int x, int y)
{
    if (!selector)
        return (0);
    return (x >= selector->x && x <= selector->x + selector->width && y >= selector->y && y <= selector->y + selector->height);
}

int is_mouse_on_dropdown_area(t_material_selector *selector, int x, int y)
{
    int dropdown_y;

    if (!selector || !selector->is_open)
        return (0);
    dropdown_y = selector->y + selector->height;
    return (x >= selector->x && x <= selector->x + selector->width && y >= dropdown_y && y <= dropdown_y + selector->dropdown_height);
}

int is_mouse_on_material_selector(t_material_selector *selector, int x, int y)
{
    if (!selector)
        return (0);
    if (is_mouse_on_selector_button(selector, x, y))
        return (1);
    return (is_mouse_on_dropdown_area(selector, x, y));
}

int get_dropdown_item_index(t_material_selector *selector, int x, int y)
{
    int dropdown_y;
    int relative_y;
    int index;

    if (!selector || !selector->is_open)
        return (-1);
    dropdown_y = selector->y + selector->height;
    if (x >= selector->x && x <= selector->x + selector->width && y >= dropdown_y && y <= dropdown_y + selector->dropdown_height)
    {
        relative_y = y - dropdown_y;
        index = relative_y / selector->item_height;
        if (index >= 0 && index < 5)
            return (index);
    }
    return (-1);
}

void handle_selector_button_click(t_material_selector *selector)
{
    if (!selector)
        return;
    selector->is_open = !selector->is_open;
    selector->hover_index = -1;
}

void handle_dropdown_item_click(t_material_selector *selector, int item_index)
{
    if (!selector || item_index < 0)
        return;
    selector->selected_material = item_index;
    selector->is_open = 0;
    selector->hover_index = -1;
}

void handle_material_selector_click(t_control_panel *cp, int x, int y)
{
    t_material_selector *selector;
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
    t_material_selector *selector;

    if (!cp || !cp->config_win)
        return;
    selector = &cp->config_win->material_selector;
    if (selector->is_open)
        selector->hover_index = get_dropdown_item_index(selector, x, y);
}
