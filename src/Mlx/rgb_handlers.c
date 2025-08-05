/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:40:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:39:22 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int get_rgb_component_index(t_control_panel *cp, t_slider *slider)
{
    if (slider == &cp->config_win->red_slider)
        return (0);
    else if (slider == &cp->config_win->green_slider)
        return (1);
    else if (slider == &cp->config_win->blue_slider)
        return (2);
    return (-1);
}

static void update_sphere_rgb(t_control_panel *cp, int rgb_index, float value)
{
    if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count)
    {
        cp->sphere[cp->data.idx_obj].rgb[rgb_index] = value;
        cp->sphere[cp->data.idx_obj].material.albedo[rgb_index] = value;
    }
}

static void update_plane_rgb(t_control_panel *cp, int rgb_index, float value)
{
    if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.plane_count)
    {
        cp->plane[cp->data.idx_obj].rgb[rgb_index] = value;
        cp->plane[cp->data.idx_obj].material.albedo[rgb_index] = value;
    }
}

static void update_cylinder_rgb(t_control_panel *cp, int rgb_index, float value)
{
    if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cylinder_count)
    {
        cp->cylinder[cp->data.idx_obj].rgb[rgb_index] = value;
        cp->cylinder[cp->data.idx_obj].material.albedo[rgb_index] = value;
    }
}

static void update_cone_rgb(t_control_panel *cp, int rgb_index, float value)
{
    if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cone_count)
    {
        cp->cone[cp->data.idx_obj].rgb[rgb_index] = value;
        cp->cone[cp->data.idx_obj].material.albedo[rgb_index] = value;
    }
}

void update_object_rgb(t_control_panel *cp, int rgb_index, float value)
{
    if (!cp || rgb_index < 0 || rgb_index > 2)
        return;
    if (cp->data.obj_type == 0)
        update_sphere_rgb(cp, rgb_index, value);
    else if (cp->data.obj_type == 1)
        update_plane_rgb(cp, rgb_index, value);
    else if (cp->data.obj_type == 2)
        update_cylinder_rgb(cp, rgb_index, value);
    else if (cp->data.obj_type == 3)
        update_cone_rgb(cp, rgb_index, value);
}

void handle_rgb_slider_interaction(t_control_panel *cp, t_slider *slider,
                                   int x, int y)
{
    int rgb_index;
    int interaction_result;

    if (!cp || !slider)
        return;
    rgb_index = get_rgb_component_index(cp, slider);
    if (rgb_index == -1)
        return;
    interaction_result = handle_slider_interaction(slider, x, y);
    if (interaction_result > 0)
    {
        update_object_rgb(cp, rgb_index, slider->current_value);
        redraw_interface(cp);
    }
}
