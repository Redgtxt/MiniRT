#include "../../includes/miniRT.h"

int	is_mouse_on_slider_handle(t_slider slider, int mouse_x, int mouse_y)
{
	float		value_ratio;
	int			handle_x;
	int			handle_y;
	t_interval	x_interval;
	t_interval	y_interval;

	value_ratio = (slider.current_value - slider.min_value) / (slider.max_value
			- slider.min_value);
	handle_x = slider.x + (int)((slider.width - slider.handle_width)
			* value_ratio);
	handle_y = slider.y - (slider.handle_height - slider.height) / 2;
	x_interval = interval_create(handle_x, handle_x + slider.handle_width);
	y_interval = interval_create(handle_y, handle_y + slider.handle_height);
	return (interval_contains(mouse_x, x_interval) && interval_contains(mouse_y,
			y_interval));
}
static void	slider_sphere_rgb(t_control_panel *cp, int x)
{
	if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count)
	{
		if (cp->config_win->red_slider.is_dragging)
		{
			update_slider_value(&cp->config_win->red_slider, x);
			cp->sphere[cp->data.idx_obj].rgb[0] = cp->config_win->red_slider.current_value;
			cp->sphere[cp->data.idx_obj].material.albedo[0] = cp->config_win->red_slider.current_value;
			redraw_interface(cp);
		}
		if (cp->config_win->green_slider.is_dragging)
		{
			update_slider_value(&cp->config_win->green_slider, x);
			cp->sphere[cp->data.idx_obj].rgb[1] = cp->config_win->green_slider.current_value;
			cp->sphere[cp->data.idx_obj].material.albedo[1] = cp->config_win->red_slider.current_value;
			redraw_interface(cp);
		}
		if (cp->config_win->blue_slider.is_dragging)
		{
			update_slider_value(&cp->config_win->blue_slider, x);
			cp->sphere[cp->data.idx_obj].rgb[2] = cp->config_win->blue_slider.current_value;
			cp->sphere[cp->data.idx_obj].material.albedo[2] = cp->config_win->red_slider.current_value;
			redraw_interface(cp);
		}
	}
}

int	mouse_move_handler(int x, int y, void *param)
{
	t_control_panel	*cp;
	t_slider		*slider;

	(void)y;
	cp = (t_control_panel *)param;
	if (!cp || !cp->config_win)
		return (0);
	slider = &cp->config_win->slider;
	if (slider->is_dragging)
	{
		update_slider_value(slider, x);
		redraw_interface(cp);
	}
	// dropdown
	handle_material_selector_hover(cp, x, y);
	// Sliders RGB da esfera
	slider_sphere_rgb(cp, x);
	return (0);
}

void	set_slider_value_from_position(t_slider *slider, int mouse_x)
{
	float	ratio;

	ratio = (float)(mouse_x - slider->x) / slider->width;
	// Limitar entre 0 e 1
	if (ratio < 0.0)
		ratio = 0.0;
	if (ratio > 1.0)
		ratio = 1.0;
	// Calcular o novo valor
	slider->current_value = slider->min_value + ratio * (slider->max_value
			- slider->min_value);
}
