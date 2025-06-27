/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:01:36 by hguerrei          #+#    #+#             */
/*   Updated: 2025/06/27 14:05:09 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
/*
    MASOQUISMO.exe
    
    [x]Primeiro criar um hook que vai incrementar ou decrementar uma variavel atraves das setas do teclado se tiver dentro da janela de controlo
        [x]Depois vou fazer funcionar para mudar o idx de um array
    
*/


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

    int img_width, img_height;
    control_data->image.sphere = mlx_xpm_file_to_image(cp->mlx->mlx, "src/images/sphere_small.xpm", &img_width, &img_height);
    return control_data;
}

static void update_sliders_from_selected_object(t_control_panel *cp)
{
    if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count && cp->sphere)
    {
        t_sphere *current_sphere = &cp->sphere[cp->data.idx_obj];
        
        cp->config_win->red_slider.current_value = current_sphere->rgb[0];
        cp->config_win->green_slider.current_value = current_sphere->rgb[1];
        cp->config_win->blue_slider.current_value = current_sphere->rgb[2];
        
        redraw_interface(cp);
        
        printf("🔄 Esfera %d selecionada - RGB: %.2f, %.2f, %.2f\n", 
               cp->data.idx_obj, current_sphere->rgb[0], current_sphere->rgb[1], current_sphere->rgb[2]);
    }
}

static void change_object(int keycode, t_control_panel *cp)
{
    if (cp->data.sphere_count == 0)
        return;
        
    if (keycode == ARROW_RIGHT_KEY)
    {
        cp->data.idx_obj = (cp->data.idx_obj + 1) % cp->data.sphere_count;
        printf("IDX value: %d have increased\n", cp->data.idx_obj);
    }
    if (keycode == ARROW_LEFT_KEY)
    {
        cp->data.idx_obj = (cp->data.idx_obj - 1 + cp->data.sphere_count) % cp->data.sphere_count;
        printf("IDX value: %d have decreased\n", cp->data.idx_obj);
    }
    

    update_sliders_from_selected_object(cp);
}



static int control_win_key_hook(int keycode, t_control_panel *cp)
{
    change_object(keycode,cp);

    return (0);
}

static void control_win_hooks(t_win_config *control_data,t_control_panel *cp)
{
    mlx_key_hook(control_data->win, control_win_key_hook, cp);
    mlx_hook(control_data->win, 4, 1L<<2, mouse_press_handler, cp);   // ButtonPress
    mlx_hook(control_data->win, 5, 1L<<3, mouse_release_handler, cp); // ButtonRelease
    mlx_hook(control_data->win, 6, 1L<<6, mouse_move_handler, cp);    // Motion notify
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
    
    // Inicializar sliders RGB com valores padrão da primeira esfera
    if (cp->sphere && cp->data.sphere_count > 0)
    {
        control_data->red_slider = (t_slider){60, 250, 300, 10, 20, 30, 0.0, 1.0, cp->sphere[0].rgb[0], 0x808080, 0xFF0000, 0};
        control_data->green_slider = (t_slider){60, 280, 300, 10, 20, 30, 0.0, 1.0, cp->sphere[0].rgb[1], 0x808080, 0x00FF00, 0};
        control_data->blue_slider = (t_slider){60, 310, 300, 10, 20, 30, 0.0, 1.0, cp->sphere[0].rgb[2], 0x808080, 0x0000FF, 0};
    }
    
    draw_button(cp, my_button);
    draw_slider(cp, my_slider);
    mlx_put_image_to_window(control_data->mlx, control_data->win, control_data->img, 0, 0);
    
    // Draw sphere image in upper left corner
    if (control_data->image.sphere)
        mlx_put_image_to_window(control_data->mlx, control_data->win, control_data->image.sphere, 10, 10);
    
    mlx_string_put(control_data->mlx, control_data->win, 175, 130, 0xFF0000, "RENDER");
    draw_slider_values(cp, my_slider);
    
    // Mostrar informações e sliders RGB da primeira esfera
    if (cp->sphere && cp->data.sphere_count > 0)
        redraw_interface(cp);
    
    control_win_hooks(control_data, cp);
    
    return (0);
}

