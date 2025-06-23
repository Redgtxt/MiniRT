/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:01:56 by hguerrei          #+#    #+#             */
/*   Updated: 2025/06/23 14:48:45 by hguerrei         ###   ########.fr       */
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

int key_hook(int keycode, t_control_panel *control_panel)
{
    printf("Keycode (%d)\n",keycode);
    if (keycode == KEY_ESC)
    {
        close_window(control_panel);
    }
    config_antialising_render(keycode, control_panel);
    change_object_brightness(keycode, control_panel);
    change_amb_light_brightness(keycode, control_panel);
    return (0);
}

void game_hooks(t_control_panel *control_panel)
{
    t_mlx *mlx_data;

    mlx_data = control_panel->mlx;
    mlx_hook(mlx_data->win, 17, 0, close_window, control_panel);
    mlx_key_hook(mlx_data->win, key_hook, control_panel);
}
