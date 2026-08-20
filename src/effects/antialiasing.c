/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:45:45 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/08 11:45:48 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	sample_square(double out[3])
{
	out[0] = random_double_0_to_1() - 0.5;
	out[1] = random_double_0_to_1() - 0.5;
	out[2] = 0.0;
}

void	setup_antialiasing(t_control_panel *control_panel, int num_of_samples)
{
	static bool	first_time;

	first_time = true;
	if (control_panel->camera.antialiasing)
	{
		control_panel->camera.samples_per_pixel = num_of_samples;
		printf("\n" HMAG "Antialiasing: APPLYING" RESET "\n");
	}
	else
	{
		if (!first_time)
			printf("\n" HMAG "Antialiasing: REMOVING" RESET "\n");
		else
			first_time = false;
		control_panel->camera.samples_per_pixel = 1;
	}
	control_panel->camera.pixel_samples_scale = 1.0
		/ control_panel->camera.samples_per_pixel;
}
