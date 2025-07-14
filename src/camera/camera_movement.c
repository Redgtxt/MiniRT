/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:44:43 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/14 14:49:04 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
/**
 * Move the camera in the direction of the camera's basis vectors
 * based on the key pressed (WASD for movement, QE for up/down)
 *
 * @param keycode The key that was pressed
 * @param cp Control panel containing the camera and scene
 */
void move_camera_with_keys(int keycode, t_control_panel *cp)
{
    double move_speed = 0.3; // Movement distance per keypress
    double camera_pos[3];
    double direction[3];
    bool moved = false;

    // Get current camera position
    vec3_copy(camera_pos, cp->camera.cords);

    // Movement based on camera's orthonormal basis (u, v, W)
    if (keycode == KEY_W) // Forward (negative W direction)
    {
        vec3_scale(direction, cp->camera.W, -move_speed);
        vec3_add(camera_pos, camera_pos, direction);
        moved = true;
    }
    else if (keycode == KEY_S) // Backward (positive W direction)
    {
        vec3_scale(direction, cp->camera.W, move_speed);
        vec3_add(camera_pos, camera_pos, direction);
        moved = true;
    }
    else if (keycode == KEY_A) // Left (negative u direction)
    {
        vec3_scale(direction, cp->camera.u, -move_speed);
        vec3_add(camera_pos, camera_pos, direction);
        moved = true;
    }
    else if (keycode == KEY_D) // Right (positive u direction)
    {
        vec3_scale(direction, cp->camera.u, move_speed);
        vec3_add(camera_pos, camera_pos, direction);
        moved = true;
    }
    else if (keycode == KEY_Q) // Up (positive v direction)
    {
        vec3_scale(direction, cp->camera.v, move_speed);
        vec3_add(camera_pos, camera_pos, direction);
        moved = true;
    }
    else if (keycode == KEY_E) // Down (negative v direction)
    {
        vec3_scale(direction, cp->camera.v, -move_speed);
        vec3_add(camera_pos, camera_pos, direction);
        moved = true;
    }
    else if (keycode == KEY_R) // Reset camera position
    {
        vec3_set(camera_pos, 0, 0, 0);
        vec3_set(cp->camera.lookat, 0, 0, -1);
        vec3_set(cp->camera.vup, 0, 1, 0);
        moved = true;
    }

    // Update camera position and re-render if moved
    if (moved)
    {
        // Update camera position
        vec3_copy(cp->camera.cords, camera_pos);

        // Recalculate camera parameters after movement
        get_values_camera(cp);

        // Re-render the scene with new camera position
        clear_image(cp);
        render_scene(cp);

        // Print feedback
        printf("Camera moved to position: (%.2f, %.2f, %.2f)\n",
               camera_pos[0], camera_pos[1], camera_pos[2]);
    }
}
