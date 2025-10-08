/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:44:43 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/08 11:59:50 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	process_wasd_keys(int keycode, t_control_panel *cp,
		double camera_pos[3], bool *moved)
{
	double	move_speed;

	move_speed = 0.3;
	if (keycode == KEY_W)
		apply_movement(camera_pos, cp->camera.W, -move_speed, moved);
	else if (keycode == KEY_S)
		apply_movement(camera_pos, cp->camera.W, move_speed, moved);
	else if (keycode == KEY_A)
		apply_movement(camera_pos, cp->camera.u, -move_speed, moved);
	else if (keycode == KEY_D)
		apply_movement(camera_pos, cp->camera.u, move_speed, moved);
}

static void	process_qe_keys(int keycode, t_control_panel *cp,
		double camera_pos[3], bool *moved)
{
	double	move_speed;

	move_speed = 0.3;
	if (keycode == KEY_Q)
		apply_movement(camera_pos, cp->camera.v, move_speed, moved);
	else if (keycode == KEY_E)
		apply_movement(camera_pos, cp->camera.v, -move_speed, moved);
}

static void	process_reset_key(int keycode, t_control_panel *cp,
		double camera_pos[3], bool *moved)
{
	if (keycode == KEY_R)
	{
		vec3_set(camera_pos, 0, 0, 0);
		vec3_set(cp->camera.lookat, 0, 0, -1);
		vec3_set(cp->camera.vup, 0, 1, 0);
		*moved = true;
	}
}

static void	update_camera(t_control_panel *cp, double camera_pos[3])
{
	vec3_copy(cp->camera.cords, camera_pos);
	get_values_camera(cp);
	clear_image(cp);
	render_scene(cp);
}

void	move_camera_with_keys(int keycode, t_control_panel *cp)
{
	double	camera_pos[3];
	bool	moved;

	moved = false;
	vec3_copy(camera_pos, cp->camera.cords);
	process_wasd_keys(keycode, cp, camera_pos, &moved);
	process_qe_keys(keycode, cp, camera_pos, &moved);
	process_reset_key(keycode, cp, camera_pos, &moved);
	if (moved)
		update_camera(cp, camera_pos);
}
