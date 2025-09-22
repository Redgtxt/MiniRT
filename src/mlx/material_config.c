/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:45:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/08/05 16:27:31 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void configure_material_properties(t_material *material, t_material_type type)
{
    if (!material)
        return;
    if (type == LAMBERTIAN)
        set_lambertian_material(material, material->albedo);
    else if (type == METAL)
        set_metal_material(material, material->albedo);
    else if (type == CHECKERPATTERN)
        set_checker_material(material, material->albedo);
    else if (type == GLASS)
        set_glass_material(material);
}

static void apply_material_to_sphere(t_control_panel *cp, t_material_type type)
{
    t_data *data;

    data = &cp->data;
    if (data->idx_obj >= 0 && data->idx_obj < (int)data->sphere_count)
    {
        cp->sphere[data->idx_obj].material.type = type;
        configure_material_properties(&cp->sphere[data->idx_obj].material, type);
    }
}

static void apply_material_to_plane(t_control_panel *cp, t_material_type type)
{
    t_data *data;

    data = &cp->data;
    if (data->idx_obj >= 0 && data->idx_obj < (int)data->plane_count)
    {
        cp->plane[data->idx_obj].material.type = type;
        configure_material_properties(&cp->plane[data->idx_obj].material, type);
    }
}

static void apply_material_to_cylinder(t_control_panel *cp, t_material_type type)
{
    t_data *data;

    data = &cp->data;
    if (data->idx_obj >= 0 && data->idx_obj < (int)data->cylinder_count)
    {
        cp->cylinder[data->idx_obj].material.type = type;
        configure_material_properties(&cp->cylinder[data->idx_obj].material, type);
    }
}

static void apply_material_to_cone(t_control_panel *cp, t_material_type type)
{
    t_data *data;

    data = &cp->data;
    if (data->idx_obj >= 0 && data->idx_obj < (int)data->cone_count)
    {
        cp->cone[data->idx_obj].material.type = type;
        configure_material_properties(&cp->cone[data->idx_obj].material, type);
    }
}

void apply_material_to_selected_object(t_control_panel *cp, t_material_type type)
{
    t_data *data;

    if (!cp)
        return;
    data = &cp->data;
    if (data->obj_type == 0)
        apply_material_to_sphere(cp, type);
    else if (data->obj_type == 1)
        apply_material_to_plane(cp, type);
    else if (data->obj_type == 2)
        apply_material_to_cylinder(cp, type);
    else if (data->obj_type == 3)
        apply_material_to_cone(cp, type);
}
