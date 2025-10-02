/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:25 by randrade          #+#    #+#             */
/*   Updated: 2025/10/02 16:32:43 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	switch_antialiasing_message(t_control_panel *control_panel)
{
    if (control_panel->camera.antialiasing)
        printf("\n" GRNHB BBLK "Antialiasing: ON" RESET "\n");
    else
        printf("\n" REDHB BBLK "Antialiasing: OFF" RESET "\n");
}

void	print_current_rendering_process(t_control_panel *control_panel,
								t_coord *coord)
{
    if (coord->y % 10 == 0)
        ft_printf(BHYEL "\rScanlines remaining: %d " RESET,
			(control_panel->camera.image_height - coord->y));
}

void	color_pixel(t_control_panel *control_panel, t_ray *ray,
				t_coord *coord, t_pixel_color *pixel_color)
{
	*ray = get_ray(*coord, control_panel);
	ray_color(control_panel, control_panel->camera.max_bounces, ray,
		pixel_color->pixel_color);
}

void	apply_pixel_color(t_control_panel *control_panel, t_coord *coord,
				t_pixel_color *pixel_color)
{
	int rgb;

	rgb = write_color(pixel_color->pixel_color[0],
			pixel_color->pixel_color[1], pixel_color->pixel_color[2]);
	my_mlx_pixel_put(control_panel, coord->x, coord->y, rgb);
}
