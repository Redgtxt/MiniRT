/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:00:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:39:22 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
** This file has been refactored to use centralized utility functions.
** Main functionality moved to:
** - mouse_utils.c: Mouse interaction utilities
** - rgb_handlers.c: RGB slider handling
*/

static void handle_main_slider_drag(t_control_panel *cp, int x)
{
    t_slider *slider;

    if (!cp || !cp->config_win)
        return;
    slider = &cp->config_win->slider;
    if (slider->is_dragging)
    {
        update_slider_value(slider, x);
        redraw_interface(cp);
    }
}

static void handle_rgb_slider_drag(t_control_panel *cp, int x)
{
    if (!cp || !cp->config_win)
        return;
    if (cp->config_win->red_slider.is_dragging)
    {
        update_slider_value(&cp->config_win->red_slider, x);
        update_object_rgb(cp, 0, cp->config_win->red_slider.current_value);
        redraw_interface(cp);
    }
    if (cp->config_win->green_slider.is_dragging)
    {
        update_slider_value(&cp->config_win->green_slider, x);
        update_object_rgb(cp, 1, cp->config_win->green_slider.current_value);
        redraw_interface(cp);
    }
    if (cp->config_win->blue_slider.is_dragging)
    {
        update_slider_value(&cp->config_win->blue_slider, x);
        update_object_rgb(cp, 2, cp->config_win->blue_slider.current_value);
        redraw_interface(cp);
    }
}

int mouse_move_handler(int x, int y, void *param)
{
    t_control_panel *cp;

    (void)y;
    cp = (t_control_panel *)param;
    if (!cp || !cp->config_win)
        return (0);
    handle_main_slider_drag(cp, x);
    handle_rgb_slider_drag(cp, x);
    return (0);
}

void set_slider_value_from_position_legacy(t_slider *slider, int mouse_x)
{
    set_slider_value_from_position(slider, mouse_x);
}

int is_mouse_on_slider_handle_legacy(t_slider slider, int mouse_x, int mouse_y)
{
    return (is_mouse_on_slider_handle(slider, mouse_x, mouse_y));
}
