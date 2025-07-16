#include "../../includes/miniRT.h"

static void draw_slider_bar(t_control_panel *cp, t_slider slider)
{
    int i;
    int j;

    i = 0;
    // desenha a barra do slider
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

    sprintf(min_str, "%.1f", slider.min_value);
    sprintf(max_str, "%.1f", slider.max_value);
    sprintf(current_str, "%.1f", slider.current_value);

    mlx_string_put(cp->config_win->mlx, cp->config_win->win,
                   slider.x - 20, slider.y + slider.height + 15,
                   0xFFFFFF, min_str);

    mlx_string_put(cp->config_win->mlx, cp->config_win->win,
                   slider.x + slider.width + 5, slider.y + slider.height + 15,
                   0xFFFFFF, max_str);

    // Desenhar valor atual no centro
    mlx_string_put(cp->config_win->mlx, cp->config_win->win,
                   slider.x + slider.width / 2 - 10, slider.y - 20,
                   0x00FF00, current_str);
}

void create_rgb_sliders(t_control_panel *cp)
{
    if (!cp || !cp->config_win)
        return;

    int red_dragging = cp->config_win->red_slider.is_dragging;
    int green_dragging = cp->config_win->green_slider.is_dragging;
    int blue_dragging = cp->config_win->blue_slider.is_dragging;
    double r = 0, g = 0, b = 0;

    // Get RGB values based on object type
    if (cp->data.obj_type == 0 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count && cp->sphere)
    {
        r = cp->sphere[cp->data.idx_obj].rgb[0];
        g = cp->sphere[cp->data.idx_obj].rgb[1];
        b = cp->sphere[cp->data.idx_obj].rgb[2];
    }
    else if (cp->data.obj_type == 1 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.plane_count && cp->plane)
    {
        r = cp->plane[cp->data.idx_obj].rgb[0];
        g = cp->plane[cp->data.idx_obj].rgb[1];
        b = cp->plane[cp->data.idx_obj].rgb[2];
    }
    else if (cp->data.obj_type == 2 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cylinder_count && cp->cylinder)
    {
        r = cp->cylinder[cp->data.idx_obj].rgb[0];
        g = cp->cylinder[cp->data.idx_obj].rgb[1];
        b = cp->cylinder[cp->data.idx_obj].rgb[2];
    }
    else if (cp->data.obj_type == 3 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cone_count && cp->cone)
    {
        r = cp->cone[cp->data.idx_obj].rgb[0];
        g = cp->cone[cp->data.idx_obj].rgb[1];
        b = cp->cone[cp->data.idx_obj].rgb[2];
    }
    else
    {
        return; // No valid object selected
    }

    // Configure RGB sliders with the current object values
    cp->config_win->red_slider = (t_slider){60, 250, 300, 10, 20, 30, 0.0, 1.0, r, 0x808080, 0xFF0000, red_dragging};
    cp->config_win->green_slider = (t_slider){60, 280, 300, 10, 20, 30, 0.0, 1.0, g, 0x808080, 0x00FF00, green_dragging};
    cp->config_win->blue_slider = (t_slider){60, 310, 300, 10, 20, 30, 0.0, 1.0, b, 0x808080, 0x0000FF, blue_dragging};

    // Draw the sliders
    draw_slider(cp, cp->config_win->red_slider);
    draw_slider(cp, cp->config_win->green_slider);
    draw_slider(cp, cp->config_win->blue_slider);

    // Labels for the sliders
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 30, 265, 0xFF0000, "Red:");
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 20, 285, 0x00FF00, "Green:");
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 20, 315, 0x0000FF, "Blue:");

    // Show current values
    draw_slider_values(cp, cp->config_win->red_slider);
    draw_slider_values(cp, cp->config_win->green_slider);
    draw_slider_values(cp, cp->config_win->blue_slider);
}

void draw_slider(t_control_panel *cp, t_slider slider)
{
    int i;
    int j;
    int handle_x;
    float value_ratio;

    draw_slider_bar(cp, slider);
    // Calcular posição do handle baseado no valor atual
    value_ratio = (slider.current_value - slider.min_value) / (slider.max_value - slider.min_value);
    handle_x = slider.x + (int)((slider.width - slider.handle_width) * value_ratio);
    i = 0;
    // desenha o handler
    while (i < slider.handle_height)
    {
        j = 0;
        while (j < slider.handle_width)
        {
            pixel_put_win_control(cp, handle_x + j, slider.y - (slider.handle_height - slider.height) / 2 + i, slider.color_handle);
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

    slider_limits = interval_create(slider->x, slider->x + slider->width - slider->handle_width);

    // clamp para limitar a posição do mouse dentro dos limites do slider
    clamped_mouse_x = (int)clamp(mouse_x, slider_limits);

    // Calcular nova ratio e valor
    ratio = (float)(clamped_mouse_x - slider->x) / (slider->width - slider->handle_width);
    slider->current_value = slider->min_value + ratio * (slider->max_value - slider->min_value);
}
