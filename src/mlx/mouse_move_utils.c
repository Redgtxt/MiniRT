/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:00:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/17 16:54:01 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	update_sphere_red_slider(t_control_panel *cp, int x)
{
	float	current_value;

	current_value = cp->config_win->red_slider.current_value;
	update_slider_value(&cp->config_win->red_slider, x);
	cp->sphere[cp->data.idx_obj].rgb[0] = current_value;
	cp->sphere[cp->data.idx_obj].material.albedo[0] = current_value;
	redraw_interface(cp);
}

static void	update_sphere_green_slider(t_control_panel *cp, int x)
{
	float	current_value;

	current_value = cp->config_win->green_slider.current_value;
	update_slider_value(&cp->config_win->green_slider, x);
	cp->sphere[cp->data.idx_obj].rgb[1] = current_value;
	cp->sphere[cp->data.idx_obj].material.albedo[1] = current_value;
	redraw_interface(cp);
}

static void	update_sphere_blue_slider(t_control_panel *cp, int x)
{
	float	current_value;

	current_value = cp->config_win->blue_slider.current_value;
	update_slider_value(&cp->config_win->blue_slider, x);
	cp->sphere[cp->data.idx_obj].rgb[2] = current_value;
	cp->sphere[cp->data.idx_obj].material.albedo[2] = current_value;
	redraw_interface(cp);
}

static void	process_rgb_sliders(t_control_panel *cp, int x)
{
	if (cp->config_win->red_slider.is_dragging)
		update_sphere_red_slider(cp, x);
	if (cp->config_win->green_slider.is_dragging)
		update_sphere_green_slider(cp, x);
	if (cp->config_win->blue_slider.is_dragging)
		update_sphere_blue_slider(cp, x);
}

void	slider_sphere_rgb(t_control_panel *cp, int x)
{
	if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count)
		process_rgb_sliders(cp, x);
}
