#include "../../includes/miniRT.h"
static void	handle_right_arrow(t_control_panel *cp)
{
	if (cp->data.obj_type == 0)
		cp->data.idx_obj = (cp->data.idx_obj + 1) % cp->data.sphere_count;
	else if (cp->data.obj_type == 1)
		cp->data.idx_obj = (cp->data.idx_obj + 1) % cp->data.plane_count;
	else if (cp->data.obj_type == 2)
		cp->data.idx_obj = (cp->data.idx_obj + 1) % cp->data.cylinder_count;
	else if (cp->data.obj_type == 3)
		cp->data.idx_obj = (cp->data.idx_obj + 1) % cp->data.cone_count;
}

static void	handle_left_arrow(t_control_panel *cp)
{
	if (cp->data.obj_type == 0 && cp->data.sphere_count > 0)
		cp->data.idx_obj = (cp->data.idx_obj - 1 + cp->data.sphere_count)
			% cp->data.sphere_count;
	else if (cp->data.obj_type == 1 && cp->data.plane_count > 0)
		cp->data.idx_obj = (cp->data.idx_obj - 1 + cp->data.plane_count)
			% cp->data.plane_count;
	else if (cp->data.obj_type == 2 && cp->data.cylinder_count > 0)
		cp->data.idx_obj = (cp->data.idx_obj - 1 + cp->data.cylinder_count)
			% cp->data.cylinder_count;
	else if (cp->data.obj_type == 3 && cp->data.cone_count > 0)
		cp->data.idx_obj = (cp->data.idx_obj - 1 + cp->data.cone_count)
			% cp->data.cone_count;
}

static void	handle_vertical_arrows(int keycode, t_control_panel *cp)
{
	if (keycode == ARROW_UP_KEY)
		cp->data.obj_type = (cp->data.obj_type + 1) % 4;
	else
		cp->data.obj_type = (cp->data.obj_type + 3) % 4;
	cp->data.idx_obj = 0;
}

static void	reset_sliders(t_control_panel *cp)
{
	cp->config_win->red_slider.is_dragging = 0;
	cp->config_win->green_slider.is_dragging = 0;
	cp->config_win->blue_slider.is_dragging = 0;
}

void	change_object(int keycode, t_control_panel *cp)
{
	if (keycode == ARROW_RIGHT_KEY)
		handle_right_arrow(cp);
	else if (keycode == ARROW_LEFT_KEY)
		handle_left_arrow(cp);
	else if (keycode == ARROW_UP_KEY || keycode == ARROW_DOWN_KEY)
		handle_vertical_arrows(keycode, cp);
	reset_sliders(cp);
	update_sliders_from_selected_object(cp);
}
