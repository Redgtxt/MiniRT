/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:01:36 by hguerrei          #+#    #+#             */
/*   Updated: 2025/06/24 17:13:11 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_win_config    *init_control_window(t_control_panel *cp)
{
    t_win_config *control_data;

      control_data = malloc(sizeof(t_win_config));
    if (!control_data)
        return (NULL);

    control_data->mlx = cp->mlx->mlx;
    if (!control_data->mlx)
    {
        ft_printf("Error: Could not initialize MLX\n");
        free(control_data);
        return (NULL);
    }

    control_data->win = mlx_new_window(control_data->mlx, W_WIDTH, W_HEIGHT, "miniRT Control");
    if (!control_data->win)
    {
        ft_printf("Error: Could not create window\n");
        free(control_data);
        return (NULL);
    }

    control_data->img = mlx_new_image(control_data->mlx, W_WIDTH, W_HEIGHT);
    control_data->addr = mlx_get_data_addr(control_data->img, &control_data->bits_per_pixel,
                                           &control_data->line_length, &control_data->endian);


    return control_data;
}

int create_control_window(t_control_panel *cp)
{
    t_win_config *control_data;
    t_button my_button = {100, 100, 200, 50, 0x00FF00};
    t_slider my_slider = {50, 200, 300, 10, 20, 30, 0.0, 1.0, cp->amb_light.light_force, 0x808080, 0xFF0000, 0};
    
    control_data = init_control_window(cp);
    cp->config_win = control_data;
    control_data->button = my_button;
    control_data->slider = my_slider;
    
    draw_button(cp, my_button);
    draw_slider(cp, my_slider);
    mlx_put_image_to_window(control_data->mlx, control_data->win, control_data->img, 0, 0);
    mlx_string_put(control_data->mlx, control_data->win, 175, 130, 0xFF0000, "RENDER");
    draw_slider_values(cp, my_slider);
    
    // Usar mlx_hook em vez de mlx_mouse_hook para ter controle total
    mlx_hook(control_data->win, 4, 1L<<2, mouse_press_handler, cp);   // ButtonPress
    mlx_hook(control_data->win, 5, 1L<<3, mouse_release_handler, cp); // ButtonRelease
    mlx_hook(control_data->win, 6, 1L<<6, mouse_move_handler, cp);    // Motion notify
    
    return (0);
}

