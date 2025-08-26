/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:50:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:39:22 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
** This file has been refactored to use centralized utility functions.
** Main functionality moved to:
** - mouse_utils.c: Mouse interaction utilities
** - rgb_handlers.c: RGB slider handling
** - interface_render.c: Interface rendering
*/

static int handle_render_button_click(t_control_panel *cp, int x, int y)
{
	t_slider *slider;

	if (!cp || !cp->config_win)
		return (0);
	slider = &cp->config_win->slider;
	return (render_button(cp, slider, x, y));
}

static int handle_material_selector_click_event(t_control_panel *cp,
												int x, int y)
{
	if (!cp || !cp->config_win)
		return (0);
	if (is_mouse_on_material_selector(&cp->config_win->material_selector,
									  x, y))
	{
		handle_material_selector_click(cp, x, y);
		redraw_interface(cp);
		return (1);
	}
	return (0);
}

static void handle_ambient_light_slider(t_control_panel *cp, int x, int y)
{
	t_slider *slider;
	int interaction_result;

	if (!cp || !cp->config_win)
		return;
	slider = &cp->config_win->slider;
	interaction_result = handle_slider_interaction(slider, x, y);
	if (interaction_result > 0)
		redraw_interface(cp);
}

static void handle_rgb_sliders_group(t_control_panel *cp, int x, int y)
{
	int valid_object;

	if (!cp || !cp->config_win)
		return;
	valid_object = (is_valid_sphere(cp) || is_valid_plane(cp) || is_valid_cylinder(cp) || is_valid_cone(cp));
	if (valid_object)
	{
		handle_rgb_slider_interaction(cp, &cp->config_win->red_slider, x, y);
		handle_rgb_slider_interaction(cp, &cp->config_win->green_slider, x, y);
		handle_rgb_slider_interaction(cp, &cp->config_win->blue_slider, x, y);
	}
}

int mouse_press_handler(int button, int x, int y, void *param)
{
	t_control_panel *cp;

	cp = (t_control_panel *)param;
	if (!cp || !cp->config_win || button != 1)
		return (0);
	if (handle_render_button_click(cp, x, y))
		return (0);
	if (handle_material_selector_click_event(cp, x, y))
		return (0);
	handle_ambient_light_slider(cp, x, y);
	handle_rgb_sliders_group(cp, x, y);
	return (0);
}
