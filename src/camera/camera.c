#include "../../includes/miniRT.h"



static void setup_camera_dimensions(t_control_panel *control_panel)
{
	control_panel->camera.aspect_ratio = 16.0 / 9.0;
	setup_antialiasing(control_panel,100);
	control_panel->camera.image_width = WINDOW_WIDTH;
	control_panel->camera.image_height = (int)control_panel->camera.image_width / control_panel->camera.aspect_ratio;
	if (control_panel->camera.image_height < 1)
	{
		control_panel->camera.image_height = 1;
	}
}

static void setup_camera_viewport(t_control_panel *control_panel)
{
	double focal_lenght = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double)control_panel->camera.image_width / (double)control_panel->camera.image_height);
	double viewport_horizontal[3], viewport_vertical[3];
	double focal_offset[3], viewport_h_half[3], viewport_v_half[3];
	double viewport_upper_left[3], pixel_delta_sum[3], half_delta[3], temp[3];

	vec3_set(viewport_horizontal, viewport_width, 0, 0);
	vec3_set(viewport_vertical, 0, -viewport_height, 0);
	vec3_divide(control_panel->camera.pixel_delta_u, viewport_horizontal, (double)control_panel->camera.image_width);
	vec3_divide(control_panel->camera.pixel_delta_v, viewport_vertical, (double)control_panel->camera.image_height);
	vec3_set(focal_offset, 0, 0, focal_lenght);
	vec3_divide(viewport_h_half, viewport_horizontal, 2.0);
	vec3_divide(viewport_v_half, viewport_vertical, 2.0);
	vec3_sub_chain(temp, control_panel->camera.cords, focal_offset, viewport_h_half);
	vec3_sub(viewport_upper_left, temp, viewport_v_half);
	vec3_add(pixel_delta_sum, control_panel->camera.pixel_delta_u, control_panel->camera.pixel_delta_v);
	vec3_scale(half_delta, pixel_delta_sum, 0.5);
	vec3_add(control_panel->camera.pixel00_loc, viewport_upper_left, half_delta);
}

void get_values_camera(t_control_panel *control_panel)
{
	setup_camera_dimensions(control_panel);
	setup_camera_viewport(control_panel);
	control_panel->camera.max_bounces = 50;
}