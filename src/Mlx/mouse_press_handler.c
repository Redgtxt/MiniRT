/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:22:42 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/14 11:43:45 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int render_button(t_control_panel *cp, t_slider *slider, int x, int y)
{
	t_interval x_interval;
	t_interval y_interval;
	t_button btn;
	t_material_type selected_material;

	btn = cp->config_win->button;
	x_interval = interval_create(btn.x, btn.x + btn.width);
	y_interval = interval_create(btn.y, btn.y + btn.height);
	if (interval_contains(x, x_interval) && interval_contains(y, y_interval))
	{
		cp->amb_light.light_force = slider->current_value;
		// Get the currently selected material from the dropdown
		selected_material = cp->config_win->material_selector.selected_material;

		if (cp->data.obj_type == 0 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count)
		{
			// Update sphere RGB values
			cp->sphere[cp->data.idx_obj].rgb[0] = cp->config_win->red_slider.current_value;
			cp->sphere[cp->data.idx_obj].rgb[1] = cp->config_win->green_slider.current_value;
			cp->sphere[cp->data.idx_obj].rgb[2] = cp->config_win->blue_slider.current_value;
			cp->sphere[cp->data.idx_obj].material.albedo[0] = cp->config_win->red_slider.current_value;
			cp->sphere[cp->data.idx_obj].material.albedo[1] = cp->config_win->green_slider.current_value;
			cp->sphere[cp->data.idx_obj].material.albedo[2] = cp->config_win->blue_slider.current_value;

			// Update material type and properties
			cp->sphere[cp->data.idx_obj].material.type = selected_material;
			configure_material_properties(&cp->sphere[cp->data.idx_obj].material, selected_material);

			printf("✅ RENDER aplicado à esfera %d: R=%.2f, G=%.2f, B=%.2f, Material=%s\n",
				   cp->data.idx_obj,
				   cp->sphere[cp->data.idx_obj].rgb[0],
				   cp->sphere[cp->data.idx_obj].rgb[1],
				   cp->sphere[cp->data.idx_obj].rgb[2],
				   cp->config_win->material_selector.material_names[selected_material]);
		}
		else if (cp->data.obj_type == 1 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.plane_count)
		{
			// Update plane RGB values
			cp->plane[cp->data.idx_obj].rgb[0] = cp->config_win->red_slider.current_value;
			cp->plane[cp->data.idx_obj].rgb[1] = cp->config_win->green_slider.current_value;
			cp->plane[cp->data.idx_obj].rgb[2] = cp->config_win->blue_slider.current_value;
			cp->plane[cp->data.idx_obj].material.albedo[0] = cp->config_win->red_slider.current_value;
			cp->plane[cp->data.idx_obj].material.albedo[1] = cp->config_win->green_slider.current_value;
			cp->plane[cp->data.idx_obj].material.albedo[2] = cp->config_win->blue_slider.current_value;

			// Update material type and properties
			cp->plane[cp->data.idx_obj].material.type = selected_material;
			configure_material_properties(&cp->plane[cp->data.idx_obj].material, selected_material);

			printf("✅ RENDER aplicado ao plano %d: R=%.2f, G=%.2f, B=%.2f, Material=%s\n",
				   cp->data.idx_obj,
				   cp->plane[cp->data.idx_obj].rgb[0],
				   cp->plane[cp->data.idx_obj].rgb[1],
				   cp->plane[cp->data.idx_obj].rgb[2],
				   cp->config_win->material_selector.material_names[selected_material]);
		}
		else if (cp->data.obj_type == 2 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cylinder_count)
		{
			// Update cylinder RGB values
			cp->cylinder[cp->data.idx_obj].rgb[0] = cp->config_win->red_slider.current_value;
			cp->cylinder[cp->data.idx_obj].rgb[1] = cp->config_win->green_slider.current_value;
			cp->cylinder[cp->data.idx_obj].rgb[2] = cp->config_win->blue_slider.current_value;
			cp->cylinder[cp->data.idx_obj].material.albedo[0] = cp->config_win->red_slider.current_value;
			cp->cylinder[cp->data.idx_obj].material.albedo[1] = cp->config_win->green_slider.current_value;
			cp->cylinder[cp->data.idx_obj].material.albedo[2] = cp->config_win->blue_slider.current_value;

			// Update material type and properties
			cp->cylinder[cp->data.idx_obj].material.type = selected_material;
			configure_material_properties(&cp->cylinder[cp->data.idx_obj].material, selected_material);

			printf("✅ RENDER aplicado ao cilindro %d: R=%.2f, G=%.2f, B=%.2f, Material=%s\n",
				   cp->data.idx_obj,
				   cp->cylinder[cp->data.idx_obj].rgb[0],
				   cp->cylinder[cp->data.idx_obj].rgb[1],
				   cp->cylinder[cp->data.idx_obj].rgb[2],
				   cp->config_win->material_selector.material_names[selected_material]);
		}
		clear_image(cp);
		render_scene(cp);
		return (1);
	}
	return (0);
}

static int handle_slider_base(t_slider *slider, int x, int y)
{
	if (is_mouse_on_slider_bar(*slider, x, y))
	{
		if (is_mouse_on_slider_handle(*slider, x, y))
		{
			slider->is_dragging = 1;
			return (1);
		}
		else
		{
			set_slider_value_from_position(slider, x);
			slider->is_dragging = 1;
			return (2);
		}
	}
	return (0);
}

static void handle_rgb_slider(t_control_panel *cp, t_slider *slider, int x,
							  int y)
{
	int rgb_num;
	int result;

	if (slider == &cp->config_win->red_slider)
		rgb_num = 0;
	else if (slider == &cp->config_win->green_slider)
		rgb_num = 1;
	else if (slider == &cp->config_win->blue_slider)
		rgb_num = 2;
	else
		return;

	result = handle_slider_base(slider, x, y);
	if (result > 0)
	{

		// WITH THIS - Updates the correct object based on type
		if (cp->data.obj_type == 0 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count)
		{
			cp->sphere[cp->data.idx_obj].rgb[rgb_num] = slider->current_value;
			cp->sphere[cp->data.idx_obj].material.albedo[rgb_num] = slider->current_value;
		}
		else if (cp->data.obj_type == 1 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.plane_count)
		{
			cp->plane[cp->data.idx_obj].rgb[rgb_num] = slider->current_value;
			cp->plane[cp->data.idx_obj].material.albedo[rgb_num] = slider->current_value;
		}
		else if (cp->data.obj_type == 2 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cylinder_count)
		{
			cp->cylinder[cp->data.idx_obj].rgb[rgb_num] = slider->current_value;
			cp->cylinder[cp->data.idx_obj].material.albedo[rgb_num] = slider->current_value;
		}

		redraw_interface(cp);
	}
}

int mouse_press_handler(int button, int x, int y, void *param)
{
	t_control_panel *cp;
	t_slider *slider;
	t_slider *red_slider;
	t_slider *blue_slider;
	t_slider *green_slider;
	int ambient_result;

	cp = (t_control_panel *)param;
	if (!cp || !cp->config_win)
		return (0);
	slider = &cp->config_win->slider;
	red_slider = &cp->config_win->red_slider;
	blue_slider = &cp->config_win->blue_slider;
	green_slider = &cp->config_win->green_slider;
	if (button == 1) // Botão esquerdo
	{
		if (render_button(cp, slider, x, y))
			return (0);

		if (is_mouse_on_material_selector(&cp->config_win->material_selector, x, y))
		{
			handle_material_selector_click(cp, x, y);
			redraw_interface(cp);
			return 0;
		}

		// Verificar clique no slider principal (ambient light) usando a função base
		ambient_result = handle_slider_base(slider, x, y);
		if (ambient_result > 0)
		{
			redraw_interface(cp);
			if (ambient_result == 1)
				printf("Slider principal sendo arrastado!\n");
			else if (ambient_result == 2)
				printf("Slider principal saltou para posição! Valor: %.2f\n",
					   slider->current_value);
		}

		// REPLACE THIS CONDITION - Currently only works for spheres
		// if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count)

		// WITH THIS - Now checks for all object types
		bool valid_object = (cp->data.obj_type == 0 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count) ||
							(cp->data.obj_type == 1 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.plane_count) ||
							(cp->data.obj_type == 2 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cylinder_count);

		if (valid_object)
		{
			handle_rgb_slider(cp, red_slider, x, y);
			handle_rgb_slider(cp, green_slider, x, y);
			handle_rgb_slider(cp, blue_slider, x, y);
		}
	}
	return (0);
}
