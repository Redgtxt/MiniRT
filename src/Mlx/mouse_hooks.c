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


int mouse_release_handler(int button, int x, int y, void *param)  // Adicionar x e y
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
        // Slider principal
        if (slider->is_dragging)
        {
            slider->is_dragging = 0;
            printf("Slider principal solto!\n");
        }
        
        // Sliders RGB
        if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count)
        {
            if (cp->config_win->red_slider.is_dragging)
            {
                cp->config_win->red_slider.is_dragging = 0;
                // Renderizar a cena com a nova cor
                render_scene(cp);
                printf("Slider RED solto! Renderizando...\n");
            }
            
            if (cp->config_win->green_slider.is_dragging)
            {
                cp->config_win->green_slider.is_dragging = 0;
                // Renderizar a cena com a nova cor
                render_scene(cp);
                printf("Slider GREEN solto! Renderizando...\n");
            }
            
            if (cp->config_win->blue_slider.is_dragging)
            {
                cp->config_win->blue_slider.is_dragging = 0;
                // Renderizar a cena com a nova cor
                render_scene(cp);
                printf("Slider BLUE solto! Renderizando...\n");
            }
        }
    }
    
    return (0);
}


int mouse_move_handler(int x, int y, void *param)  // Corrigir: adicionar parâmetro y
{
    (void)y;
    t_control_panel *cp = (t_control_panel *)param;
    t_slider *slider;
    
    if (!cp || !cp->config_win)
        return (0);
        
    slider = &cp->config_win->slider;
    
    // Slider principal
    if (slider->is_dragging)
    {
        update_slider_value(slider, x);
        redraw_interface(cp);
        printf("Valor do slider principal: %.2f\n", slider->current_value);
    }
    
    // Sliders RGB
    if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count)
    {
        if (cp->config_win->red_slider.is_dragging)
        {
            update_slider_value(&cp->config_win->red_slider, x);
            // Atualizar valor na esfera
            cp->sphere[cp->data.idx_obj].rgb[0] = cp->config_win->red_slider.current_value;
            redraw_interface(cp);
            printf("RED em movimento: %.2f\n", cp->config_win->red_slider.current_value);
        }
        
        if (cp->config_win->green_slider.is_dragging)
        {
            update_slider_value(&cp->config_win->green_slider, x);
            // Atualizar valor na esfera
            cp->sphere[cp->data.idx_obj].rgb[1] = cp->config_win->green_slider.current_value;
            redraw_interface(cp);
            printf("GREEN em movimento: %.2f\n", cp->config_win->green_slider.current_value);
        }
        
        if (cp->config_win->blue_slider.is_dragging)
        {
            update_slider_value(&cp->config_win->blue_slider, x);
            // Atualizar valor na esfera
            cp->sphere[cp->data.idx_obj].rgb[2] = cp->config_win->blue_slider.current_value;
            redraw_interface(cp);
            printf("BLUE em movimento: %.2f\n", cp->config_win->blue_slider.current_value);
        }
    }
    
    return (0);
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
        // Verificar clique no botão
        x_interval = interval_create(btn.x, btn.x + btn.width);
        y_interval = interval_create(btn.y, btn.y + btn.height);
        if (interval_contains(x, x_interval) && interval_contains(y, y_interval))
        {
            printf("Botão clicado!\n");
            clear_image(cp);
            cp->amb_light.light_force = slider->current_value;
              if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count && cp->sphere)
            {
                cp->sphere[cp->data.idx_obj].rgb[0] = cp->config_win->red_slider.current_value;
                cp->sphere[cp->data.idx_obj].rgb[1] = cp->config_win->green_slider.current_value;
                cp->sphere[cp->data.idx_obj].rgb[2] = cp->config_win->blue_slider.current_value;
                
                printf("Aplicando RGB à esfera %d: R=%.2f, G=%.2f, B=%.2f\n", 
                       cp->data.idx_obj,
                       cp->sphere[cp->data.idx_obj].rgb[0],
                       cp->sphere[cp->data.idx_obj].rgb[1],
                       cp->sphere[cp->data.idx_obj].rgb[2]);
            }
            clear_image(cp);
            render_scene(cp);
            return (0);
        }
        
        // Verificar clique no slider principal (ambient light)
        if (is_mouse_on_slider_bar(*slider, x, y))
        {
            if (is_mouse_on_slider_handle(*slider, x, y))
            {
                slider->is_dragging = 1;
                printf("Slider principal sendo arrastado!\n");
            }
            else
            {
                set_slider_value_from_position(slider, x);
                slider->is_dragging = 1;
                redraw_interface(cp);
                printf("Slider principal saltou para posição! Valor: %.2f\n", slider->current_value);
            }
        }
        
        // Verificar clique nos sliders RGB (apenas se um objeto estiver selecionado)
        if (cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count)
        {
            // Slider RED
            if (is_mouse_on_slider_bar(cp->config_win->red_slider, x, y))
            {
                if (is_mouse_on_slider_handle(cp->config_win->red_slider, x, y))
                {
                    cp->config_win->red_slider.is_dragging = 1;
                    printf("Slider RED sendo arrastado!\n");
                }
                else
                {
                    set_slider_value_from_position(&cp->config_win->red_slider, x);
                    cp->config_win->red_slider.is_dragging = 1;
                    // Atualizar valor na esfera
                    cp->sphere[cp->data.idx_obj].rgb[0] = cp->config_win->red_slider.current_value;
                    redraw_interface(cp);
                    printf("RED: %.2f\n", cp->config_win->red_slider.current_value);
                }
            }
            
            // Slider GREEN
            if (is_mouse_on_slider_bar(cp->config_win->green_slider, x, y))
            {
                if (is_mouse_on_slider_handle(cp->config_win->green_slider, x, y))
                {
                    cp->config_win->green_slider.is_dragging = 1;
                    printf("Slider GREEN sendo arrastado!\n");
                }
                else
                {
                    set_slider_value_from_position(&cp->config_win->green_slider, x);
                    cp->config_win->green_slider.is_dragging = 1;
                    // Atualizar valor na esfera
                    cp->sphere[cp->data.idx_obj].rgb[1] = cp->config_win->green_slider.current_value;
                    redraw_interface(cp);
                    printf("GREEN: %.2f\n", cp->config_win->green_slider.current_value);
                }
            }
            
            // Slider BLUE
            if (is_mouse_on_slider_bar(cp->config_win->blue_slider, x, y))
            {
                if (is_mouse_on_slider_handle(cp->config_win->blue_slider, x, y))
                {
                    cp->config_win->blue_slider.is_dragging = 1;
                    printf("Slider BLUE sendo arrastado!\n");
                }
                else
                {
                    set_slider_value_from_position(&cp->config_win->blue_slider, x);
                    cp->config_win->blue_slider.is_dragging = 1;
                    // Atualizar valor na esfera
                    cp->sphere[cp->data.idx_obj].rgb[2] = cp->config_win->blue_slider.current_value;
                    redraw_interface(cp);
                    printf("BLUE: %.2f\n", cp->config_win->blue_slider.current_value);
                }
            }
        }
    }
    
    return (0);
}
