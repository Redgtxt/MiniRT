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

static void test_color_change(t_control_panel *cp)
{
    if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count && cp->sphere)
    {
        // Mudar para cor completamente diferente (azul puro)
        cp->sphere[cp->data.idx_obj].rgb[0] = 0.0;  // Red = 0
        cp->sphere[cp->data.idx_obj].rgb[1] = 0.0;  // Green = 0  
        cp->sphere[cp->data.idx_obj].rgb[2] = 1.0;  // Blue = 1
        
        printf("TESTE: Esfera %d agora é AZUL PURO (0,0,1)\n", cp->data.idx_obj);
        
        clear_image(cp);
        render_scene(cp);
    }
}

int key_hook(int keycode, t_control_panel *control_panel)
{
    printf("Keycode (%d)\n",keycode);
    if (keycode == KEY_ESC)
    {
        close_window(control_panel);
    }
    
    // NOVO: Adicionar teste com tecla 't'
    if (keycode == 't')
    {
        test_color_change(control_panel);
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
