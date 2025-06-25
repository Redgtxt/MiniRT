#include "../../includes/miniRT.h"

void clear_image_slider(t_control_panel *cp)
{
    int i;
    int j;

    i =0;
    while(i < W_HEIGHT)
    {
        j =0;
        while (j < W_WIDTH)
        {
            pixel_put_win_control(cp, j, i, 0x000000); // Cor preta para limpar
            j++;
        }
        i++;
    }
}

int is_mouse_on_slider_bar(t_slider slider, int mouse_x, int mouse_y)
{
    t_interval x_interval;
    t_interval y_interval;
    
    x_interval = interval_create(slider.x, slider.x + slider.width);
    y_interval = interval_create(slider.y, slider.y + slider.height);
    
    return (interval_contains(mouse_x, x_interval) && 
            interval_contains(mouse_y, y_interval));
}

// Função para redesenhar toda a interface
void redraw_interface(t_control_panel *cp)
{
    clear_image_slider(cp);
    
    draw_button(cp, cp->config_win->button);
    draw_slider(cp, cp->config_win->slider);
    
    mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                           cp->config_win->img, 0, 0);
    
    // Redesenhar textos
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 175, 130, 0xFF0000, "RENDER");
    draw_slider_values(cp, cp->config_win->slider);
}