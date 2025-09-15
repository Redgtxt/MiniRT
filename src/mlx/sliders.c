/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:04:25 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/23 17:04:38 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void draw_slider(t_control_panel *cp, t_slider slider)
{
	int handle_x;
	float value_ratio;

	draw_slider_bar(cp, slider);
	// Calcular posição do handle baseado no valor atual
	value_ratio = (slider.current_value - slider.min_value) / (slider.max_value - slider.min_value);
	handle_x = slider.x + (int)((slider.width - slider.handle_width) * value_ratio);
	// Desenhar handle melhorado
	draw_slider_handle_improved(cp, handle_x, slider.y - (slider.handle_height - slider.height) / 2, slider.handle_width, slider.handle_height,
								slider.color_handle);
}

void update_slider_value(t_slider *slider, int mouse_x)
{
	float ratio;
	t_interval slider_limits;
	int clamped_mouse_x;

	slider_limits = interval_create(slider->x, slider->x + slider->width - slider->handle_width);
	// clamp para limitar a posição do mouse dentro dos limites do slider
	clamped_mouse_x = (int)clamp(mouse_x, slider_limits);
	// Calcular nova ratio e valor
	ratio = (float)(clamped_mouse_x - slider->x) / (slider->width - slider->handle_width);
	slider->current_value = slider->min_value + ratio * (slider->max_value - slider->min_value);
}

void draw_slider_amb_light(t_control_panel *cp, t_slider slider)
{
	char current_str[20];

	sprintf(current_str, "%.2f", slider.current_value);
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 380, 202,
				   COLOR_WHITE, current_str);
}