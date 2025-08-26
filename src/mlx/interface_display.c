/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:35:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:39:22 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void get_object_info(t_control_panel *cp, int obj_index, char *obj_type,
                            double **rgb, double *pos)
{
    if (cp->data.obj_type == 0)
    {
        if (obj_index < 0 || obj_index >= (int)cp->data.sphere_count || !cp->sphere)
            return;
        ft_strlcpy(obj_type, "Sphere", 20);
        *rgb = cp->sphere[obj_index].rgb;
        vec3_copy(pos, cp->sphere[obj_index].cords);
    }
    else if (cp->data.obj_type == 1)
    {
        if (obj_index < 0 || obj_index >= (int)cp->data.plane_count || !cp->plane)
            return;
        ft_strlcpy(obj_type, "Plane", 20);
        *rgb = cp->plane[obj_index].rgb;
        vec3_copy(pos, cp->plane[obj_index].cords);
    }
}

static void get_cylinder_cone_info(t_control_panel *cp, int obj_index,
                                   char *obj_type, double **rgb, double *pos)
{
    if (cp->data.obj_type == 2)
    {
        if (obj_index < 0 || obj_index >= (int)cp->data.cylinder_count || !cp->cylinder)
            return;
        ft_strlcpy(obj_type, "Cylinder", 20);
        *rgb = cp->cylinder[obj_index].rgb;
        vec3_copy(pos, cp->cylinder[obj_index].cords);
    }
    else if (cp->data.obj_type == 3)
    {
        if (obj_index < 0 || obj_index >= (int)cp->data.cone_count || !cp->cone)
            return;
        ft_strlcpy(obj_type, "Cone", 20);
        *rgb = cp->cone[obj_index].rgb;
        vec3_copy(pos, cp->cone[obj_index].cords);
    }
}

static void display_object_properties(t_control_panel *cp, int obj_index)
{
    char info_text[256];

    if (cp->data.obj_type == 0)
    {
        sprintf(info_text, "Radius: %.2f", cp->sphere[obj_index].radius);
        mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70,
                       0xFFFFFF, info_text);
    }
    else if (cp->data.obj_type == 1)
    {
        sprintf(info_text, "Normal: %.2f,%.2f,%.2f",
                cp->plane[obj_index].vec3[0], cp->plane[obj_index].vec3[1],
                cp->plane[obj_index].vec3[2]);
        mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70,
                       0xFFFFFF, info_text);
    }
    else if (cp->data.obj_type == 2)
    {
        sprintf(info_text, "Radius: %.2f, Height: %.2f",
                cp->cylinder[obj_index].radius, cp->cylinder[obj_index].height);
        mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70,
                       0xFFFFFF, info_text);
    }
    else if (cp->data.obj_type == 3)
    {
        sprintf(info_text, "Radius: %.2f, Height: %.2f",
                cp->cone[obj_index].radius, cp->cone[obj_index].height);
        mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70,
                       0xFFFFFF, info_text);
    }
}

void display_object_stats(t_control_panel *cp, int obj_index)
{
    char info_text[256];
    char obj_type_str[20];
    double *rgb;
    double pos[3];

    rgb = NULL;
    ft_bzero(pos, sizeof(pos));
    ft_bzero(obj_type_str, sizeof(obj_type_str));
    get_object_info(cp, obj_index, obj_type_str, &rgb, pos);
    get_cylinder_cone_info(cp, obj_index, obj_type_str, &rgb, pos);
    if (!rgb)
        return;
    sprintf(info_text, "Selected %s: %d", obj_type_str, obj_index);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 30,
                   0xFFFFFF, info_text);
    sprintf(info_text, "Pos: %.1f,%.1f,%.1f", pos[0], pos[1], pos[2]);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 50,
                   0xFFFFFF, info_text);
    display_object_properties(cp, obj_index);
    sprintf(info_text, "RGB: %.2f,%.2f,%.2f", rgb[0], rgb[1], rgb[2]);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 90,
                   0xFFFFFF, info_text);
}
