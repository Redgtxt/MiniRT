/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:45:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:39:22 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void draw_main_interface_elements(t_control_panel *cp)
{
    if (!cp || !cp->config_win)
        return;
    clear_image_slider(cp);
    draw_button(cp, cp->config_win->button);
    draw_slider(cp, cp->config_win->slider);
    mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                            cp->config_win->img, 0, 0);
}

static void display_object_images(t_control_panel *cp)
{
    if (!cp || !cp->config_win)
        return;
    if (cp->data.obj_type == 0 && cp->config_win->image.sphere)
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                                cp->config_win->image.sphere, 10, 10);
    else if (cp->data.obj_type == 1 && cp->config_win->image.plane)
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                                cp->config_win->image.plane, 10, 10);
    else if (cp->data.obj_type == 2 && cp->config_win->image.cylinder)
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                                cp->config_win->image.cylinder, 10, 10);
    else if (cp->data.obj_type == 3 && cp->config_win->image.cone)
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                                cp->config_win->image.cone, 10, 10);
}

static void draw_interface_labels(t_control_panel *cp)
{
    if (!cp || !cp->config_win)
        return;
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 235, 15,
                   0xFFFFFF, "=== MiniRT Control Panel ===");
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 50, 185,
                   0xFFFFFF, "=== Ambient Light: ===");
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 50, 360,
                   0xFFFFFF, "=== Material: ===");
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 175, 130,
                   0xFF4040, "RENDER");
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 50, 235,
                   0xFFFFFF, "== Object Colors ==");
}

static void draw_dynamic_elements(t_control_panel *cp)
{
    if (!cp || !cp->config_win)
        return;
    draw_slider_amb_light(cp, cp->config_win->slider);
    display_object_stats(cp, cp->data.idx_obj);
    create_rgb_sliders(cp);
    draw_material_selector(cp);
}

void redraw_interface(t_control_panel *cp)
{
    if (!cp)
        return;
    draw_main_interface_elements(cp);
    display_object_images(cp);
    draw_interface_labels(cp);
    draw_dynamic_elements(cp);
}
