#include "../../includes/miniRT.h"

void clear_image_slider(t_control_panel *cp)
{
    int i;
    int j;

    i = 0;
    while (i < W_HEIGHT)
    {
        j = 0;
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
    char obj_type_str[20];
    double *rgb;
    double pos[3] = {0};

    // Set object type string and check if index is valid
    if (cp->data.obj_type == 0)
    {
        if (obj_index < 0 || obj_index >= (int)cp->data.sphere_count || !cp->sphere)
            return;
        sprintf(obj_type_str, "Sphere");
        rgb = cp->sphere[obj_index].rgb;
        vec3_copy(pos, cp->sphere[obj_index].cords);
    }
    else if (cp->data.obj_type == 1)
    {
        if (obj_index < 0 || obj_index >= (int)cp->data.plane_count || !cp->plane)
            return;
        sprintf(obj_type_str, "Plane");
        rgb = cp->plane[obj_index].rgb;
        vec3_copy(pos, cp->plane[obj_index].cords);
    }
    else if (cp->data.obj_type == 2)
    {
        if (obj_index < 0 || obj_index >= (int)cp->data.cylinder_count || !cp->cylinder)
            return;
        sprintf(obj_type_str, "Cylinder");
        rgb = cp->cylinder[obj_index].rgb;
        vec3_copy(pos, cp->cylinder[obj_index].cords);
    }
    else if (cp->data.obj_type == 3)
    {
        if (obj_index < 0 || obj_index >= (int)cp->data.cone_count || !cp->cone)
            return;
        sprintf(obj_type_str, "Cone");
        rgb = cp->cone[obj_index].rgb;
        vec3_copy(pos, cp->cone[obj_index].cords);
    }
    else
    {
        return;
    }

    // Display object type and index
    sprintf(info_text, "Selected %s: %d", obj_type_str, obj_index);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 30, COLOR_WHITE, info_text);

    // Display position
    sprintf(info_text, "Pos: %.1f,%.1f,%.1f", pos[0], pos[1], pos[2]);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 50, COLOR_WHITE, info_text);

    // Display specific properties based on object type
    if (cp->data.obj_type == 0)
    {
        sprintf(info_text, "Radius: %.2f", cp->sphere[obj_index].radius);
        mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70, COLOR_WHITE, info_text);
    }
    else if (cp->data.obj_type == 1)
    {
        sprintf(info_text, "Normal: %.2f,%.2f,%.2f",
                cp->plane[obj_index].vec3[0],
                cp->plane[obj_index].vec3[1],
                cp->plane[obj_index].vec3[2]);
        mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70, COLOR_WHITE, info_text);
    }
    else if (cp->data.obj_type == 2)
    {
        sprintf(info_text, "Radius: %.2f, Height: %.2f",
                cp->cylinder[obj_index].radius,
                cp->cylinder[obj_index].height);
        mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70, COLOR_WHITE, info_text);
    }
    else if (cp->data.obj_type == 3)
    {
        sprintf(info_text, "Radius: %.2f, Height: %.2f",
                cp->cone[obj_index].radius,
                cp->cone[obj_index].height);
        mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 70, COLOR_WHITE, info_text);
    }
    // Display RGB values
    sprintf(info_text, "RGB: %.2f,%.2f,%.2f", rgb[0], rgb[1], rgb[2]);
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 70, 90, COLOR_WHITE, info_text);
}
// Função para redesenhar toda a interface
void redraw_interface(t_control_panel *cp)
{
    clear_image_slider(cp);

    // Título principal
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 50, 15, COLOR_WHITE, "=== MiniRT Control Panel ===");

    draw_button(cp, cp->config_win->button);
    draw_slider(cp, cp->config_win->slider);

    // Label para ambient light
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 50, 185, COLOR_WHITE, "=== Ambient Light: ===");

    // Label para material
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 50, 335, COLOR_WHITE, "Material:");

    mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                            cp->config_win->img, 0, 0);

    // Display the appropriate object image based on selected type
    if (cp->data.obj_type == 0 && cp->config_win->image.sphere)
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                                cp->config_win->image.sphere, 10, 10);
    else if (cp->data.obj_type == 1 && cp->config_win->image.plane)
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                                cp->config_win->image.plane, 10, 10);
    else if (cp->data.obj_type == 2 && cp->config_win->image.cylinder)
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                                cp->config_win->image.cylinder, 10, 10);
    else if (cp->data.obj_type == 3 && cp->config_win->image.cone)
        mlx_put_image_to_window(cp->config_win->mlx, cp->config_win->win,
                                cp->config_win->image.cone, 10, 10);

    // Redesenhar textos melhorados
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 175, 130, COLOR_HIGHLIGHT, "RENDER");
    draw_slider_amb_light(cp, cp->config_win->slider);

    draw_stats(cp, cp->data.idx_obj);

    // Labels para sliders RGB melhorados
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, 50, 235, COLOR_WHITE, "== Object Colors ==");

    // Desenhar sliders RGB se um objeto estiver selecionado
    create_rgb_sliders(cp);
    draw_material_selector(cp);
}
