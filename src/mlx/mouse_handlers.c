/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:00:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/25 16:57:00 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	mouse_press_handler(int button, int x, int y, void *param)
{
	t_control_panel	*cp;

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

int	mouse_release_handler(int button, int x, int y, void *param)
{
	t_control_panel	*cp;
	t_slider		*slider;

	(void)x;
	(void)y;
	cp = (t_control_panel *)param;
	if (!cp || !cp->config_win)
		return (0);
	slider = &cp->config_win->slider;
	if (button == 1)
	{
		if (slider->is_dragging)
			slider->is_dragging = 0;
		handle_dragging_rgb_slider(cp);
	}
	return (0);
}

int	mouse_move_handler(int x, int y, void *param)
{
	t_control_panel	*cp;
	t_slider		*slider;

	cp = (t_control_panel *)param;
	if (!cp || !cp->config_win)
		return (0);
	slider = &cp->config_win->slider;
	if (slider->is_dragging)
	{
		update_slider_value(slider, x);
		redraw_interface(cp);
	}
	handle_material_selector_hover(cp, x, y);
	slider_rgb(cp, x);
	return (0);
}

int	main_window_mouse_handler(int button, int x, int y, void *param)
{
	t_control_panel	*cp;
	int				clicked_object;
	int				obj_type;

	cp = (t_control_panel *)param;
	obj_type = 0;
	if (button == 1)
	{
		clicked_object = find_clicked_object(cp, x, y, &obj_type);
		if (clicked_object >= 0)
		{
			update_control_interface_with_object(cp, clicked_object, obj_type);
		}
		else
		{
			printf("No object clicked at position (%d, %d)\n", x, y);
		}
	}
	return (0);
}
