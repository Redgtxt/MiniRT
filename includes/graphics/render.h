/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../core/types.h"

/* Render utility structures */
typedef struct s_pixel_color
{
	int		sample;
	double	pixel_color[3];
	double	sample_color[3];
	double	pixel_samples_scale;
}	t_pixel_color;

typedef struct s_refract_data
{
	double	uv_negated[3];
	double	cos_theta;
	double	cos_theta_n[3];
	double	temp[3];
	double	r_out_perp[3];
}	t_refract_data;

/* Render function prototypes */
void	render_scene(t_control_panel *cp);
void	switch_antialiasing_message(t_control_panel *control_panel);
void	print_current_rendering_process(t_control_panel *control_panel,
			t_coord *coord);
void	color_pixel(t_control_panel *control_panel, t_ray *ray, t_coord *coord,
			t_pixel_color *pixel_color);
void	apply_pixel_color(t_control_panel *control_panel, t_coord *coord,
			t_pixel_color *pixel_color);

/* Antialiasing functions */
void	setup_antialiasing(t_control_panel *control_panel, int num_of_samples);
void	sample_square(double out[3]);

/* Utility functions */
double	lenght_squared(const double vector[3]);
double	degrees_to_radians(double degrees);
double	random_double_0_to_1(void);
double	random_double(double min, double max);
int		write_color(double r, double g, double b);
void	calc_perpendicular(t_refract_data *data, const double uv[3],
			const double n[3], double etai_over_etat);
void	calc_parallel(double r_out_parallel[3], const double n[3],
			double r_out_perp[3]);

#endif