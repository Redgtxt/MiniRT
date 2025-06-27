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


static void draw_stats(t_control_panel *cp, int obj_index)
{
    char info_text[256];
    
    // Verificar se o índice é válido
    if (obj_index < 0 || obj_index >= (int)cp->data.sphere_count || !cp->sphere)
        return;
        
    cp->data.idx_obj = obj_index;
    t_sphere *selected_sphere = &cp->sphere[obj_index];

    sprintf(info_text, "Selected Sphere: %d", obj_index);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 30, COLOR_WHITE, info_text);
    
    sprintf(info_text, "Pos: %.1f,%.1f,%.1f", 
            selected_sphere->cords[0], selected_sphere->cords[1], selected_sphere->cords[2]);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 50, COLOR_WHITE, info_text);
    
    sprintf(info_text, "Radius: %.2f", selected_sphere->radius);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70, COLOR_WHITE, info_text);
    
    // Mostrar valores RGB atuais
    sprintf(info_text, "RGB: %.2f,%.2f,%.2f", 
            selected_sphere->rgb[0], selected_sphere->rgb[1], selected_sphere->rgb[2]);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 90, COLOR_WHITE, info_text);
}
// Função para redesenhar toda a interface
void redraw_interface(t_control_panel *cp)
{
    clear_image_slider(cp);
    
    draw_button(cp, cp->config_win->button);
    draw_slider(cp, cp->config_win->slider);
    
    mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                           cp->config_win->img, 0, 0);
    
    // Draw sphere image in upper left corner
    if (cp->config_win->image.sphere)
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win, 
                               cp->config_win->image.sphere, 10, 10);
    
    // Redesenhar textos
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 175, 130, 0xFF0000, "RENDER");
    draw_slider_values(cp, cp->config_win->slider);
    
    draw_stats(cp,cp->data.idx_obj);

    // Desenhar sliders RGB se um objeto estiver selecionado
    create_rgb_sliders(cp);
}
