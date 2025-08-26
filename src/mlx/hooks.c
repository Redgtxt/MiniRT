/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:01:56 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/24 16:55:51 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*  TECLAS
    1 - antialising com 16 samples rapido
    2 - antialising com 50 samples moderado 
    3 - antialising com 100 samples lento
    0 - desliga o antialising mas mantem configuracoes
    Arrow keys para aumentar ou diminuir o brilho
*/


int key_hook(int keycode, t_control_panel *cp)
{
    printf("Keycode (%d)\n",keycode);
    if (keycode == KEY_ESC)
    {
        close_window(cp);
    }
    
    move_camera_with_keys(keycode,cp);
    config_antialising_render(keycode, cp);
    change_amb_light_brightness(keycode, cp);
    return (0);
}

void game_hooks(t_control_panel *cp)
{
    t_mlx *mlx_data;

    mlx_data = cp->mlx;
    mlx_hook(mlx_data->win, 17, 0, close_window, cp);
    mlx_key_hook(mlx_data->win, key_hook, cp);
}

static int control_win_key_hook(int keycode, t_control_panel *cp)
{
    change_object(keycode, cp);
    return (0);
}

void control_win_hooks(t_win_config *control_data, t_control_panel *cp)
{
    mlx_key_hook(control_data->win, control_win_key_hook, cp);
    mlx_hook(control_data->win, 4, 1L << 2, mouse_press_handler, cp);   // ButtonPress
    mlx_hook(control_data->win, 5, 1L << 3, mouse_release_handler, cp); // ButtonRelease
    mlx_hook(control_data->win, 6, 1L << 6, mouse_move_handler, cp);    // Motion notify
}