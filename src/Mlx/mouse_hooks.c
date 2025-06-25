#include "../../includes/miniRT.h"

static int is_mouse_on_slider_handle(t_slider slider, int mouse_x, int mouse_y)
{
    float value_ratio;
    int handle_x;
    int handle_y;
    t_interval x_interval;
    t_interval y_interval;
    
    // Calcular posição do handle
    value_ratio = (slider.current_value - slider.min_value) / (slider.max_value - slider.min_value);
    handle_x = slider.x + (int)((slider.width - slider.handle_width) * value_ratio);
    handle_y = slider.y - (slider.handle_height - slider.height) / 2;
    

    x_interval = interval_create(handle_x, handle_x + slider.handle_width);
    y_interval = interval_create(handle_y, handle_y + slider.handle_height);
    
    return (interval_contains(mouse_x, x_interval) && 
            interval_contains(mouse_y, y_interval));
}
static void clear_image_slider(t_control_panel *cp)
{
    int i, j;

    for (i = 0; i < W_HEIGHT; i++)
    {
        for (j = 0; j < W_WIDTH; j++)
        {
            pixel_put_win_control(cp, j, i, 0x000000); // Cor preta para limpar
        }
    }
}

int mouse_release_handler(int button, int x, int y, void *param)
{
    (void)x;
    (void)y;
    t_control_panel *cp = (t_control_panel *)param;
    t_slider *slider;
    
    if (!cp || !cp->config_win)
        return (0);
        
    slider = &cp->config_win->slider;
    
    if (button == 1) // Botão esquerdo solto
    {
        if (slider->is_dragging)
        {
            slider->is_dragging = 0;
            printf("Slider solto!\n");
        }
    }
    
    return (0);
}

int mouse_move_handler(int x, int y, void *param)
{
    (void) y;
    t_control_panel *cp = (t_control_panel *)param;
    t_slider *slider;
    
    if (!cp || !cp->config_win)
        return (0);
        
    slider = &cp->config_win->slider;
    
    if (slider->is_dragging)
    {
        update_slider_value(slider, x);
        
        // Redesenhar a janela
        clear_image_slider(cp);
        draw_button(cp, cp->config_win->button);
        draw_slider(cp, *slider);
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                               cp->config_win->img, 0, 0);
        
        // Redesenhar textos
        mlx_string_put(cp->config_win->mlx, cp->config_win->win, 175, 130, 0xFF0000, "RENDER");
        draw_slider_values(cp, *slider);
        
        printf("Valor do slider: %.2f\n", slider->current_value);
    }
    
    return (0);
}

static int is_mouse_on_slider_bar(t_slider slider, int mouse_x, int mouse_y)
{
    t_interval x_interval;
    t_interval y_interval;
    
    x_interval = interval_create(slider.x, slider.x + slider.width);
    y_interval = interval_create(slider.y, slider.y + slider.height);
    
    return (interval_contains(mouse_x, x_interval) && 
            interval_contains(mouse_y, y_interval));
}

static void set_slider_value_from_position(t_slider *slider, int mouse_x)
{
    float ratio;
    
    ratio = (float)(mouse_x - slider->x) / slider->width;
    
    // Limitar entre 0 e 1
    if (ratio < 0.0) ratio = 0.0;
    if (ratio > 1.0) ratio = 1.0;
    
    // Calcular o novo valor
    slider->current_value = slider->min_value + ratio * (slider->max_value - slider->min_value);
}

// Função para redesenhar toda a interface
static void redraw_interface(t_control_panel *cp)
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
int mouse_press_handler(int button, int x, int y, void *param)
{
    t_control_panel *cp = (t_control_panel *)param;
    t_button btn;
    t_interval x_interval;
    t_interval y_interval;
    t_slider *slider;
    
    if (!cp || !cp->config_win)
        return (0);
        
    btn = cp->config_win->button;
    slider = &cp->config_win->slider;
    
    if (button == 1) // Botão esquerdo
    {
        // Verificar click no botão
        x_interval = interval_create(btn.x, btn.x + btn.width);
        y_interval = interval_create(btn.y, btn.y + btn.height);
        if (interval_contains(x, x_interval) && interval_contains(y, y_interval))
        {
            printf("Botão clicado!\n");
            clear_image(cp);
            cp->amb_light.light_force = slider->current_value;
            render_scene(cp);
            return (0);
        }
        
        // Verificar se clicou na barra do slider
        if (is_mouse_on_slider_bar(*slider, x, y))
        {
            // Se clicou no handle, apenas inicia o drag
            if (is_mouse_on_slider_handle(*slider, x, y))
            {
                slider->is_dragging = 1;
                printf("Slider sendo arrastado!\n");
            }
            else
            {
                // Se clicou na barra (mas não no handle), pula para a posição
                set_slider_value_from_position(slider, x);
                slider->is_dragging = 1; // Permite continuar arrastando
                
                // Redesenhar imediatamente
                redraw_interface(cp);
                
                printf("Slider saltou para posição! Valor: %.2f\n", slider->current_value);
            }
        }
    }
    
    return (0);
}

//            cp->amb_light.light_force = slider->current_value;