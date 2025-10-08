/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "../core/types.h"
# include "../math/vec3.h"

/* Camera structure */
typedef struct s_camera
{
	t_vec3		cords[3];
	t_vec3		vec3[3];
	t_mini_int	fov;
	int			image_height;
	int			image_width;
	double		aspect_ratio;
	double		pixel00_loc[3];
	double		pixel_delta_u[3];
	double		pixel_delta_v[3];
	int			samples_per_pixel;
	double		pixel_samples_scale;
	double		lookat[3];
	double		vup[3];
	double		u[3];
	double		v[3];
	double		w[3];
	double		max_bounces;
	bool		antialiasing;
}				t_camera;

/* Camera function prototypes */
void			get_values_camera(t_control_panel *control_panel);
void			move_camera_with_keys(int keycode, t_control_panel *cp);
void			setup_camera_dimensions(t_control_panel *control_panel);
double			calculate_focal_length(t_control_panel *cp);
void			apply_movement(double camera_pos[3], double axis[3],
					double speed, bool *moved);
void			calculate_pixel00_location(t_control_panel *cp,
					double focal_length, double vp_u[3], double vp_v[3]);

#endif