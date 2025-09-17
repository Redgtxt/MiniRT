/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:11:27 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/23 15:11:29 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	update_sphere_properties(t_control_panel *cp,
		t_material_type material)
{
	int	idx;

	idx = cp->data.idx_obj;
	cp->sphere[idx].rgb[0] = cp->config_win->red_slider.current_value;
	cp->sphere[idx].rgb[1] = cp->config_win->green_slider.current_value;
	cp->sphere[idx].rgb[2] = cp->config_win->blue_slider.current_value;
	cp->sphere[idx].material.albedo[0] = cp->config_win->red_slider.current_value;
	cp->sphere[idx].material.albedo[1] = cp->config_win->green_slider.current_value;
	cp->sphere[idx].material.albedo[2] = cp->config_win->blue_slider.current_value;
	cp->sphere[idx].material.type = material;
	configure_material_properties(&cp->sphere[idx].material, material);
}

static void	update_plane_properties(t_control_panel *cp,
		t_material_type material)
{
	int	idx;

	idx = cp->data.idx_obj;
	cp->plane[idx].rgb[0] = cp->config_win->red_slider.current_value;
	cp->plane[idx].rgb[1] = cp->config_win->green_slider.current_value;
	cp->plane[idx].rgb[2] = cp->config_win->blue_slider.current_value;
	cp->plane[idx].material.albedo[0] = cp->config_win->red_slider.current_value;
	cp->plane[idx].material.albedo[1] = cp->config_win->green_slider.current_value;
	cp->plane[idx].material.albedo[2] = cp->config_win->blue_slider.current_value;
	cp->plane[idx].material.type = material;
	configure_material_properties(&cp->plane[idx].material, material);
}

static void	update_cylinder_properties(t_control_panel *cp,
		t_material_type material)
{
	int	idx;

	idx = cp->data.idx_obj;
	cp->cylinder[idx].rgb[0] = cp->config_win->red_slider.current_value;
	cp->cylinder[idx].rgb[1] = cp->config_win->green_slider.current_value;
	cp->cylinder[idx].rgb[2] = cp->config_win->blue_slider.current_value;
	cp->cylinder[idx].material.albedo[0] = cp->config_win->red_slider.current_value;
	cp->cylinder[idx].material.albedo[1] = cp->config_win->green_slider.current_value;
	cp->cylinder[idx].material.albedo[2] = cp->config_win->blue_slider.current_value;
	cp->cylinder[idx].material.type = material;
	configure_material_properties(&cp->cylinder[idx].material, material);
}

static void	update_cone_properties(t_control_panel *cp,
		t_material_type material)
{
	int	idx;

	idx = cp->data.idx_obj;
	cp->cone[idx].rgb[0] = cp->config_win->red_slider.current_value;
	cp->cone[idx].rgb[1] = cp->config_win->green_slider.current_value;
	cp->cone[idx].rgb[2] = cp->config_win->blue_slider.current_value;
	cp->cone[idx].material.albedo[0] = cp->config_win->red_slider.current_value;
	cp->cone[idx].material.albedo[1] = cp->config_win->green_slider.current_value;
	cp->cone[idx].material.albedo[2] = cp->config_win->blue_slider.current_value;
	cp->cone[idx].material.type = material;
	configure_material_properties(&cp->cone[idx].material, material);
}

void	update_objects_properties(t_control_panel *cp, t_slider *slider)
{
	t_material_type	selected_material;

	cp->amb_light.light_force = slider->current_value;
	selected_material = cp->config_win->material_selector.selected_material;
	if (cp->data.obj_type == 0 && cp->data.idx_obj >= 0
		&& cp->data.idx_obj < (int)cp->data.sphere_count)
		update_sphere_properties(cp, selected_material);
	else if (cp->data.obj_type == 1 && cp->data.idx_obj >= 0
		&& cp->data.idx_obj < (int)cp->data.plane_count)
		update_plane_properties(cp, selected_material);
	else if (cp->data.obj_type == 2 && cp->data.idx_obj >= 0
		&& cp->data.idx_obj < (int)cp->data.cylinder_count)
		update_cylinder_properties(cp, selected_material);
	else if (cp->data.obj_type == 3 && cp->data.idx_obj >= 0
		&& cp->data.idx_obj < (int)cp->data.cone_count)
		update_cone_properties(cp, selected_material);
	apply_material_to_selected_object(cp, selected_material);
	clear_image(cp);
	render_scene(cp);
}
