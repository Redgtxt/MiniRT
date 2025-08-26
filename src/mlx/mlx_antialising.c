/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_antialising.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:02:01 by hguerrei          #+#    #+#             */
/*   Updated: 2025/06/18 12:30:25 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#define FAST_ANTIALISNG "FAST Antialiasing: APPLYING with 16 samples"
#define MEDIUM_ANTIALISNG "MEDIUM Antialiasing: APPLYING with 50 samples"
#define SLOW_ANTIALISNG "SLOW Antialiasing: APPLYING with 100 samples"
#define OFF_ANTIALISNG "Antialiasing: DISABLED"

static void mlx_antialising(t_control_panel *control_panel, char *msg, int num_of_samples, bool on)
{
    control_panel->camera.antialiasing = on;
    setup_antialiasing(control_panel, num_of_samples);
    ft_printf("\n" HMAG "%s" reset "\n", msg);
    clear_image(control_panel);
    render_scene(control_panel);
}

void config_antialising_render(int keycode, t_control_panel *control_panel)
{
    if (keycode == '1')
    {
        mlx_antialising(control_panel, FAST_ANTIALISNG, 16, true);
    }
    else if (keycode == '2')
    {
        mlx_antialising(control_panel, MEDIUM_ANTIALISNG, 50, true);
    }
    else if (keycode == '3')
    {
        mlx_antialising(control_panel, SLOW_ANTIALISNG, 100, true);
    }
    else if (keycode == '0')
    {
        mlx_antialising(control_panel, OFF_ANTIALISNG, 1, false);
        ft_printf(BHYEL "\rResetting scene" reset "\n");
    }
}
