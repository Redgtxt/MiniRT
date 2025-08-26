/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:55:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:39:22 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
** This file now contains only legacy compatibility functions.
** Main functionality has been moved to:
** - mouse_utils.c: Mouse interaction utilities
** - interface_display.c: Object statistics display
** - interface_render.c: Complete interface rendering
** - rgb_handlers.c: RGB slider handling
**
** These functions remain for compatibility with existing code.
*/

int is_mouse_on_slider_bar_legacy(t_slider slider, int mouse_x, int mouse_y)
{
    return (is_mouse_on_slider_bar(slider, mouse_x, mouse_y));
}

void draw_stats_legacy(t_control_panel *cp, int obj_index)
{
    display_object_stats(cp, obj_index);
}

void redraw_interface_legacy(t_control_panel *cp)
{
    redraw_interface(cp);
}
