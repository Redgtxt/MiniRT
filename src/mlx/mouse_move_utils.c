/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:00:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/25 16:57:00 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	update_red_slider(t_control_panel *cp, int x)
{
	update_slider_value(&cp->config_win->red_slider, x);
	update_object_rgb(cp, 0, cp->config_win->red_slider.current_value);
	redraw_interface(cp);
}

static void	update_green_slider(t_control_panel *cp, int x)
{
	update_slider_value(&cp->config_win->green_slider, x);
	update_object_rgb(cp, 1, cp->config_win->green_slider.current_value);
	redraw_interface(cp);
}

static void	update_blue_slider(t_control_panel *cp, int x)
{
	update_slider_value(&cp->config_win->blue_slider, x);
	update_object_rgb(cp, 2, cp->config_win->blue_slider.current_value);
	redraw_interface(cp);
}

static void	process_rgb_sliders(t_control_panel *cp, int x)
{
	if (cp->config_win->red_slider.is_dragging)
		update_red_slider(cp, x);
	if (cp->config_win->green_slider.is_dragging)
		update_green_slider(cp, x);
	if (cp->config_win->blue_slider.is_dragging)
		update_blue_slider(cp, x);
}

void	slider_rgb(t_control_panel *cp, int x)
{
	int	valid_object;

	valid_object = (is_valid_sphere(cp) || is_valid_plane(cp)
			|| is_valid_cylinder(cp) || is_valid_cone(cp));
	if (valid_object)
		process_rgb_sliders(cp, x);
}
