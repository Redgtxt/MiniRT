/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_drawing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:50:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:27:31 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void draw_slider_bar(t_control_panel *cp, t_slider slider)
{
    float value_ratio;
    int filled_width;

    draw_filled_rectangle(cp, slider.x, slider.y, slider.width,
                          slider.height, 0x202020);
    draw_border(cp, slider.x, slider.y, slider.width, slider.height, 0xFFFFFF);
    value_ratio = (slider.current_value - slider.min_value) / (slider.max_value - slider.min_value);
    filled_width = (int)(slider.width * value_ratio);
    if (filled_width > 2)
        draw_filled_rectangle(cp, slider.x + 1, slider.y + 1,
                              filled_width - 2, slider.height - 2, slider.color_handle);
}

static void draw_handle_highlight(t_control_panel *cp, int x, int y, int width)
{
    int i;

    i = 1;
    while (i < width - 1)
    {
        pixel_put_win_control(cp, x + i, y + 1, 0xFFFFFF);
        i++;
    }
}

void draw_slider_handle_improved(t_control_panel *cp, t_rect rect, int color)
{
    draw_filled_rectangle(cp, rect, color);
    draw_border(cp, rect, 0xFFFFFF);
    draw_handle_highlight(cp, rect.x, rect.y, rect.width);
}

void draw_button(t_control_panel *cp, t_button button)
{
    int i;

    draw_filled_rectangle(cp, button.x, button.y, button.width,
                          button.height, 0x20A020);
    i = 0;
    while (i < button.width)
    {
        pixel_put_win_control(cp, button.x + i, button.y, 0x40FF40);
        pixel_put_win_control(cp, button.x + i, button.y + button.height - 1,
                              0x106010);
        i++;
    }
    i = 0;
    while (i < button.height)
    {
        pixel_put_win_control(cp, button.x, button.y + i, 0x40FF40);
        pixel_put_win_control(cp, button.x + button.width - 1, button.y + i,
                              0x106010);
        i++;
    }
}


