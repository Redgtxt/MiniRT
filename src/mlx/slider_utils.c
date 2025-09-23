/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:00:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/17 14:13:39 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	is_mouse_on_slider_bar(t_slider slider, int mouse_x, int mouse_y)
{
	t_interval	x_interval;
	t_interval	y_interval;

	x_interval = interval_create(slider.x, slider.x + slider.width);
	y_interval = interval_create(slider.y, slider.y + slider.height);
	return (interval_contains(mouse_x, x_interval) && interval_contains(mouse_y,
			y_interval));
}

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

void	set_slider_value_from_position(t_slider *slider, int mouse_x)
{
	float	ratio;

	if (!slider)
		return ;
	ratio = (float)(mouse_x - slider->x) / slider->width;
	if (ratio < 0.0)
		ratio = 0.0;
	if (ratio > 1.0)
		ratio = 1.0;
	slider->current_value = slider->min_value + ratio * (slider->max_value
			- slider->min_value);
}

void	update_slider_value(t_slider *slider, int mouse_x)
{
	float		ratio;
	t_interval	slider_limits;
	int			clamped_mouse_x;

	slider_limits = interval_create(slider->x, slider->x + slider->width
			- slider->handle_width);
	clamped_mouse_x = (int)clamp(mouse_x, slider_limits);
	ratio = (float)(clamped_mouse_x - slider->x) / (slider->width
			- slider->handle_width);
	slider->current_value = slider->min_value + ratio * (slider->max_value
			- slider->min_value);
}
