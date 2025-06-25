#include "../../includes/miniRT.h"


// Atualizar valor do slider baseado na posição do mouse
void update_slider_value(t_slider *slider, int mouse_x)
{
    double ratio;
    
    if (mouse_x < slider->x)
        mouse_x = slider->x;
    if (mouse_x > slider->x + slider->width)
        mouse_x = slider->x + slider->width;
    
    ratio = (double)(mouse_x - slider->x) / slider->width;
    slider->current_value = slider->min_value + ratio * (slider->max_value - slider->min_value);
}

// Handler para mouse press na janela de controle
int control_mouse_press(int button, int x, int y, void *param)
{
    t_control_panel *control_panel = (t_control_panel *)param;
    t_win_config *config_win = control_panel->config_win;
    
    if (button == 1) // botão esquerdo
    {
        if (mouse_over_slider(&config_win->slider, x, y))
        {
            config_win->slider.is_dragging = 1;
            update_slider_value(&config_win->slider, x);
            // Re-renderizar a cena principal com o novo valor
            render_scene(control_panel);
        }
    }
    return (0);
}

// Handler para mouse release na janela de controle
int control_mouse_release(int button, void *param)
{
    t_control_panel *control_panel = (t_control_panel *)param;
    t_win_config *config_win = control_panel->config_win;
    
    if (button == 1) // botão esquerdo
    {
        config_win->slider.is_dragging = 0;
    }
    return (0);
}
static void update_camera_from_sliders(t_control_panel *control_panel, double fov_value, 
                              double samples_value, double bounces_value)
{
    control_panel->camera.fov = (mini_int)fov_value;
    control_panel->camera.samples_per_pixel = (int)samples_value;
    control_panel->camera.max_bounces = bounces_value;
    
    // Recalculate camera parameters if needed
    get_values_camera(control_panel);
}
// Handler para movimento do mouse na janela de controle
int control_mouse_move(int x, int y, void *param)
{
    t_control_panel *control_panel = (t_control_panel *)param;
    t_win_config *config_win = control_panel->config_win;
    (void)y;   
    
    if (config_win->slider.is_dragging)
    {
        update_slider_value(&config_win->slider, x);
        
        // Update camera with slider values (simplified for now)
        control_panel->camera.fov = (mini_int)config_win->slider.current_value;
        
        // Re-render the scene
        render_scene(control_panel);
    }
    return (0);
}
