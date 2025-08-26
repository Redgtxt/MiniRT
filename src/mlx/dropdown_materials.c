/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dropdown_materials.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:55:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:27:31 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
** This file contains ONLY legacy compatibility functions.
** Main functionality has been moved to:
** - material_selector.c: Material dropdown interface
** - material_config.c: Material property configuration
** - draw_utils.c: Basic drawing utilities
** - slider_drawing.c: Advanced drawing functions
**
** These functions remain for compatibility with existing code.
*/

void init_material_selector_legacy(t_material_selector *selector)
{
    init_material_selector(selector);
}

void draw_material_selector_legacy(t_control_panel *cp)
{
    draw_material_selector(cp);
}

int is_mouse_on_material_selector_legacy(t_material_selector *selector,
                                         int mouse_x, int mouse_y)
{
    return (is_mouse_on_material_selector(selector, mouse_x, mouse_y));
}

void handle_material_selector_click_legacy(t_control_panel *cp,
                                           int mouse_x, int mouse_y)
{
    handle_material_selector_click(cp, mouse_x, mouse_y);
}

void handle_material_selector_hover_legacy(t_control_panel *cp,
                                           int mouse_x, int mouse_y)
{
    handle_material_selector_hover(cp, mouse_x, mouse_y);
}
