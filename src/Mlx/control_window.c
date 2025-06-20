#include "../../includes/miniRT.h"

// Desenhar um retângulo preenchido
void draw_filled_rect(t_control_window *control_win, int x, int y, int width, int height, int color)
{
    int i;
    int j;
    i = 0;

    while (i < control_win->height)
    {
        j = 0;
        while (j < control_win->width)
        {
            control_mlx_pixel_put(control_win, x + j, y + i, color);
        }
        i++;
    }
}

// Desenhar texto simples (você pode melhorar isso usando mlx_string_put)
void draw_text(t_control_window *control_win, int x, int y, char *text, int color)
{
    // Para simplicidade, usar mlx_string_put diretamente na janela
    mlx_string_put(control_win->mlx, control_win->win, x, y, color, text);
}

// Desenhar um slider
void draw_slider(t_control_window *control_win, t_slider *slider)
{
    int slider_pos;
    double ratio;
    char value_str[50];

    // Calcular posição do cursor baseado no valor
    ratio = (*(slider->value) - slider->min_val) / (slider->max_val - slider->min_val);
    slider_pos = slider->x + (int)(ratio * slider->width);

    // Desenhar trilha do slider
    draw_filled_rect(control_win, slider->x, slider->y + slider->height / 2 - 2,
                     slider->width, 4, COLOR_GRAY);

    // Desenhar cursor do slider
    draw_filled_rect(control_win, slider_pos - 5, slider->y, 10, slider->height, COLOR_BLUE);

    // Desenhar label e valor
    draw_text(control_win, slider->x, slider->y - 15, slider->label, COLOR_WHITE);
    snprintf(value_str, sizeof(value_str), "%.2f", *(slider->value));
    draw_text(control_win, slider->x + slider->width + 10, slider->y + 5, value_str, COLOR_WHITE);
}
