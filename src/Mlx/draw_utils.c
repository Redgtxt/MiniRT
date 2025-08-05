/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:30:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:27:31 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void draw_rectangle(t_control_panel *cp, int x, int y, int width, int height, int color)
{
    int i;
    int j;

    i = 0;
    while (i < width)
    {
        j = 0;
        while (j < height)
        {
            pixel_put_win_control(cp, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_filled_rectangle(t_control_panel *cp, int x, int y, int width, int height, int color)
{
    int i;
    int j;

    i = 0;
    while (i < width)
    {
        j = 0;
        while (j < height)
        {
            pixel_put_win_control(cp, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_border(t_control_panel *cp, int x, int y, int width, int height, int color)
{
    int i;

    i = 0;
    while (i < width)
    {
        pixel_put_win_control(cp, x + i, y, color);
        pixel_put_win_control(cp, x + i, y + height - 1, color);
        i++;
    }
    i = 0;
    while (i < height)
    {
        pixel_put_win_control(cp, x, y + i, color);
        pixel_put_win_control(cp, x + width - 1, y + i, color);
        i++;
    }
}

void draw_text_at_position(t_control_panel *cp, int x, int y, char *text)
{
    if (!cp || !cp->config_win || !text)
        return;
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, x, y, 0xFFFFFF, text);
}

void draw_arrow_down(t_control_panel *cp, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i < 6)
    {
        j = 0;
        while (j <= 6 - i)
        {
            pixel_put_win_control(cp, x + 3 + j, y + i, 0xFFFFFF);
            pixel_put_win_control(cp, x + 3 - j, y + i, 0xFFFFFF);
            j++;
        }
        i++;
    }
}
