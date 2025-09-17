/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_click_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:00:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/17 14:22:44 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	handle_render_button_click(t_control_panel *cp, int x, int y)
{
	t_slider	*slider;

	if (!cp || !cp->config_win)
		return (0);
	slider = &cp->config_win->slider;
	return (render_button(cp, slider, x, y));
}

int	handle_material_selector_click_event(t_control_panel *cp, int x, int y)
{
	if (!cp || !cp->config_win)
		return (0);
	if (is_mouse_on_material_selector(&cp->config_win->material_selector, x, y))
	{
		handle_material_selector_click(cp, x, y);
		redraw_interface(cp);
		return (1);
	}
	return (0);
}

void	handle_ambient_light_slider(t_control_panel *cp, int x, int y)
{
	t_slider	*slider;

	if (!cp || !cp->config_win)
		return ;
	slider = &cp->config_win->slider;
	if (is_mouse_on_slider_bar(*slider, x, y))
	{
		if (is_mouse_on_slider_handle(*slider, x, y))
			slider->is_dragging = 1;
		else
		{
			set_slider_value_from_position(slider, x);
			slider->is_dragging = 1;
		}
		redraw_interface(cp);
	}
}

void	handle_rgb_sliders_group(t_control_panel *cp, int x, int y)
{
	int	valid_object;

	if (!cp || !cp->config_win)
		return ;
	valid_object = (is_valid_sphere(cp) || is_valid_plane(cp)
			|| is_valid_cylinder(cp) || is_valid_cone(cp));
	if (valid_object)
	{
		handle_rgb_slider_interaction(cp, &cp->config_win->red_slider, x, y);
		handle_rgb_slider_interaction(cp, &cp->config_win->green_slider, x, y);
		handle_rgb_slider_interaction(cp, &cp->config_win->blue_slider, x, y);
	}
}

void	handle_dragging_rgb_slider(t_control_panel *cp)
{
	int	valid_object;

	valid_object = ((cp->data.obj_type == 0 && cp->data.idx_obj >= 0
				&& cp->data.idx_obj < (int)cp->data.sphere_count)
			|| (cp->data.obj_type == 1 && cp->data.idx_obj >= 0
				&& cp->data.idx_obj < (int)cp->data.plane_count)
			|| (cp->data.obj_type == 2 && cp->data.idx_obj >= 0
				&& cp->data.idx_obj < (int)cp->data.cylinder_count)
			|| (cp->data.obj_type == 3 && cp->data.idx_obj >= 0
				&& cp->data.idx_obj < (int)cp->data.cone_count));
	if (valid_object)
	{
		if (cp->config_win->red_slider.is_dragging)
			cp->config_win->red_slider.is_dragging = 0;
		if (cp->config_win->green_slider.is_dragging)
			cp->config_win->green_slider.is_dragging = 0;
		if (cp->config_win->blue_slider.is_dragging)
			cp->config_win->blue_slider.is_dragging = 0;
	}
}
