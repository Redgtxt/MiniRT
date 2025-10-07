/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:25 by randrade          #+#    #+#             */
/*   Updated: 2025/10/03 15:56:30 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	antialiasing(t_pixel_color *pixel, t_coord *coord,
				t_control_panel *control_panel, t_ray *ray)
{
    t_pixel_color	sample_pixel;
    
    pixel->sample = 0;
    while (control_panel->camera.samples_per_pixel > pixel->sample)
    {
        vec3_zero(sample_pixel.pixel_color);
        color_pixel(control_panel, ray, coord, &sample_pixel);
		vec3_add(pixel->pixel_color, pixel->pixel_color,
			sample_pixel.pixel_color);
        pixel->sample++;
    }
    pixel->pixel_samples_scale = 1.0 /
									control_panel->camera.samples_per_pixel;
    vec3_scale(pixel->pixel_color, pixel->pixel_color,
			pixel->pixel_samples_scale);
}

void	render_scene(t_control_panel *control_panel)
{
	t_coord coord;
    t_ray ray;
	t_pixel_color pixel;

    coord.y = 0;
    while (coord.y < control_panel->camera.image_height)
    {
        coord.x = 0;
        while (coord.x < control_panel->camera.image_width)
        {
            vec3_zero(pixel.pixel_color);
            if (!control_panel->camera.antialiasing)
				color_pixel(control_panel, &ray, &coord, &pixel);
            else
				antialiasing(&pixel, &coord, control_panel, &ray);
			apply_pixel_color(control_panel, &coord, &pixel);
            coord.x++;
        }
		print_current_rendering_process(control_panel, &coord);
        coord.y++;
    }
    ft_printf(BHGRN "\rScanlines remaining: DONE!" RESET "\n");
    mlx_put_image_to_window(control_panel->mlx->mlx, control_panel->mlx->win,
			control_panel->mlx->img, 0, 0);
	switch_antialiasing_message(control_panel);
}
