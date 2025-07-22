#include "../../includes/miniRT.h"

static void	update_sphere_interface(t_control_panel *cp, int obj_index)
{
	t_sphere	*selected;

	if (obj_index < 0 || obj_index >= (int)cp->data.sphere_count)
		return ;
	selected = &cp->sphere[obj_index];
	cp->config_win->red_slider.current_value = selected->rgb[0];
	cp->config_win->green_slider.current_value = selected->rgb[1];
	cp->config_win->blue_slider.current_value = selected->rgb[2];
	cp->config_win->material_selector.selected_material = selected->material.type;
	printf("Esfera %d selecionada! RGB: %.2f, %.2f, %.2f\n",
		obj_index, selected->rgb[0], selected->rgb[1], selected->rgb[2]);
}

static void	update_plane_interface(t_control_panel *cp, int obj_index)
{
	t_plane	*selected;

	if (obj_index < 0 || obj_index >= (int)cp->data.plane_count)
		return ;
	selected = &cp->plane[obj_index];
	cp->config_win->red_slider.current_value = selected->rgb[0];
	cp->config_win->green_slider.current_value = selected->rgb[1];
	cp->config_win->blue_slider.current_value = selected->rgb[2];
	cp->config_win->material_selector.selected_material = selected->material.type;
	printf("Plano %d selecionado! RGB: %.2f, %.2f, %.2f\n",
		obj_index, selected->rgb[0], selected->rgb[1], selected->rgb[2]);
}

static void	update_cylinder_interface(t_control_panel *cp, int obj_index)
{
	t_cylinder	*selected;

	if (obj_index < 0 || obj_index >= (int)cp->data.cylinder_count)
		return ;
	selected = &cp->cylinder[obj_index];
	cp->config_win->red_slider.current_value = selected->rgb[0];
	cp->config_win->green_slider.current_value = selected->rgb[1];
	cp->config_win->blue_slider.current_value = selected->rgb[2];
	cp->config_win->material_selector.selected_material = selected->material.type;
	printf("Cilindro %d selecionado! RGB: %.2f, %.2f, %.2f\n",
		obj_index, selected->rgb[0], selected->rgb[1], selected->rgb[2]);
}

static void	update_cone_interface(t_control_panel *cp, int obj_index)
{
	t_cone	*selected;

	if (obj_index < 0 || obj_index >= (int)cp->data.cone_count)
		return ;
	selected = &cp->cone[obj_index];
	cp->config_win->red_slider.current_value = selected->rgb[0];
	cp->config_win->green_slider.current_value = selected->rgb[1];
	cp->config_win->blue_slider.current_value = selected->rgb[2];
	cp->config_win->material_selector.selected_material = selected->material.type;
	printf("Cone %d selecionado! RGB: %.2f, %.2f, %.2f\n",
		obj_index, selected->rgb[0], selected->rgb[1], selected->rgb[2]);
}

void	update_control_interface_with_object(t_control_panel *cp,
	int obj_index, int obj_type)
{
	cp->data.idx_obj = obj_index;
	cp->data.obj_type = obj_type;
	if (obj_type == 0)
		update_sphere_interface(cp, obj_index);
	else if (obj_type == 1)
		update_plane_interface(cp, obj_index);
	else if (obj_type == 2)
		update_cylinder_interface(cp, obj_index);
	else if (obj_type == 3)
		update_cone_interface(cp, obj_index);
	redraw_interface(cp);
}