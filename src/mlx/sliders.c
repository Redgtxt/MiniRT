/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:04:25 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/18 12:28:18 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	draw_slider(t_control_panel *cp, t_slider slider)
{
	int		handle_x;
	float	value_ratio;
	t_rect	handle_rect;

	draw_slider_bar(cp, slider);
	value_ratio = (slider.current_value - slider.min_value) / (slider.max_value
			- slider.min_value);
	handle_x = slider.x + (int)((slider.width - slider.handle_width)
			* value_ratio);
	handle_rect.x = handle_x;
	handle_rect.y = slider.y - (slider.handle_height - slider.height) / 2;
	handle_rect.width = slider.handle_width;
	handle_rect.height = slider.handle_height;
	draw_slider_handle_improved(cp, handle_rect, slider.color_handle);
}

void	draw_slider_amb_light(t_control_panel *cp, t_slider slider)
{
	char	current_str[20];

	sprintf(current_str, "%.2f", slider.current_value);
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 380, 202,
		COLOR_WHITE, current_str);
}
