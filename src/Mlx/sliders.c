#include "../../includes/miniRT.h"

static void draw_slider_bar(t_control_panel *cp,t_slider slider)
{
    int i;
    int j;

    i = 0;
     //desenha a barra do slider
    while (i < slider.height)
    {
        j = 0;
        while (j < slider.width)
        {
            pixel_put_win_control(cp, slider.x + j, slider.y + i, slider.color_bar);
            j++;
        }
        i++;
    }
}

// Função para desenhar os valores do slider
void draw_slider_values(t_control_panel *cp, t_slider slider)
{
    char min_str[20], max_str[20], current_str[20];
    
    // Converter valores para strings
    sprintf(min_str, "%.1f", slider.min_value);
    sprintf(max_str, "%.1f", slider.max_value);
    sprintf(current_str, "%.1f", slider.current_value);
    
    // Desenhar valor mínimo à esquerda
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 
                   slider.x - 20, slider.y + slider.height + 15, 
                   0xFFFFFF, min_str);
    
    // Desenhar valor máximo à direita
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 
                   slider.x + slider.width + 5, slider.y + slider.height + 15, 
                   0xFFFFFF, max_str);
    
    // Desenhar valor atual no centro
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 
                   slider.x + slider.width/2 - 10, slider.y - 20, 
                   0x00FF00, current_str);
}

void draw_slider(t_control_panel *cp,t_slider slider)
{
    int i;
    int j;
    int handle_x;
    float value_ratio;

    
   draw_slider_bar(cp,slider);
    // Calcular posição do handle baseado no valor atual
    value_ratio = (slider.current_value - slider.min_value) / (slider.max_value - slider.min_value);
    handle_x = slider.x + (int)((slider.width - slider.handle_width) * value_ratio);
    i = 0;
    //desenha o handler
    while (i < slider.handle_height)
    {
        j =0;
        while (j < slider.handle_width)
        {
            pixel_put_win_control(cp,handle_x + j,slider.y - (slider.handle_height - slider.height) / 2 + i,slider.color_handle);
            j++;
        }
        i++;
    }
}
void update_slider_value(t_slider *slider, int mouse_x)
{
    float ratio;
    t_interval slider_limits;
    int clamped_mouse_x;
    
    // Criar intervalo para os limites do slider
    slider_limits = interval_create(slider->x, slider->x + slider->width - slider->handle_width);
    
    // clamp para limitar a posição do mouse dentro dos limites do slider
    clamped_mouse_x = (int)clamp(mouse_x, slider_limits);
    
    // Calcular nova ratio e valor
    ratio = (float)(clamped_mouse_x - slider->x) / (slider->width - slider->handle_width);
    slider->current_value = slider->min_value + ratio * (slider->max_value - slider->min_value);
}
