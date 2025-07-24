/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:01:36 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/22 16:37:56 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_win_config *init_control_window(t_control_panel *cp)
{
    t_win_config *control_data;
    int img_width;
    int img_height;

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
    control_data->image.sphere = mlx_xpm_file_to_image(cp->mlx->mlx, "src/images/sphere_small.xpm", &img_width, &img_height);
    control_data->image.plane = mlx_xpm_file_to_image(cp->mlx->mlx, "src/images/plane_resized.xpm", &img_width, &img_height);
    control_data->image.cylinder = mlx_xpm_file_to_image(cp->mlx->mlx, "src/images/cylinder.xpm", &img_width, &img_height);
    control_data->image.cone = mlx_xpm_file_to_image(cp->mlx->mlx, "src/images/cone_resized.xpm", &img_width, &img_height);
    return control_data;
}

static void update_sliders_from_selected_object(t_control_panel *cp)
{
    double r = 0, g = 0, b = 0;
    char *obj_name = "Object";
    int valid_object = 0;

    // Get RGB values based on object type
    if (cp->data.obj_type == 0 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count && cp->sphere)
    {
        r = cp->sphere[cp->data.idx_obj].rgb[0];
        g = cp->sphere[cp->data.idx_obj].rgb[1];
        b = cp->sphere[cp->data.idx_obj].rgb[2];
        obj_name = "Sphere";
        valid_object = 1;
    }
    else if (cp->data.obj_type == 1 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.plane_count && cp->plane)
    {
        r = cp->plane[cp->data.idx_obj].rgb[0];
        g = cp->plane[cp->data.idx_obj].rgb[1];
        b = cp->plane[cp->data.idx_obj].rgb[2];
        obj_name = "Plane";
        valid_object = 1;
    }
    else if (cp->data.obj_type == 2 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cylinder_count && cp->cylinder)
    {
        r = cp->cylinder[cp->data.idx_obj].rgb[0];
        g = cp->cylinder[cp->data.idx_obj].rgb[1];
        b = cp->cylinder[cp->data.idx_obj].rgb[2];
        obj_name = "Cylinder";
        valid_object = 1;
    }
    else if (cp->data.obj_type == 3 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cone_count && cp->cone)
    {
        r = cp->cone[cp->data.idx_obj].rgb[0];
        g = cp->cone[cp->data.idx_obj].rgb[1];
        b = cp->cone[cp->data.idx_obj].rgb[2];
        obj_name = "Cone";
        valid_object = 1;
    }

    if (valid_object)
    {
        cp->config_win->red_slider.current_value = r;
        cp->config_win->green_slider.current_value = g;
        cp->config_win->blue_slider.current_value = b;

        redraw_interface(cp);

        printf("🔄 %s %d selecionado - RGB: %.2f, %.2f, %.2f\n",
               obj_name, cp->data.idx_obj, r, g, b);
    }
}


static int control_win_key_hook(int keycode, t_control_panel *cp)
{
    change_object(keycode, cp);

    return (0);
}

static void control_win_hooks(t_win_config *control_data, t_control_panel *cp)
{
    mlx_key_hook(control_data->win, control_win_key_hook, cp);
    mlx_hook(control_data->win, 4, 1L << 2, mouse_press_handler, cp);   // ButtonPress
    mlx_hook(control_data->win, 5, 1L << 3, mouse_release_handler, cp); // ButtonRelease
    mlx_hook(control_data->win, 6, 1L << 6, mouse_move_handler, cp);    // Motion notify

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
    init_material_selector(&cp->config_win->material_selector);
    // Inicializar sliders RGB com valores padrão da primeira esfera
    if ((cp->data.obj_type == 0 && cp->sphere && cp->data.sphere_count > 0) ||
        (cp->data.obj_type == 1 && cp->plane && cp->data.plane_count > 0) ||
        (cp->data.obj_type == 2 && cp->cylinder && cp->data.cylinder_count > 0) ||
        (cp->data.obj_type == 3 && cp->cone && cp->data.cone_count > 0))
    {
        update_sliders_from_selected_object(cp);
    }

    draw_button(cp, my_button);
    draw_slider(cp, my_slider);
    mlx_put_image_to_window(control_data->mlx, control_data->win, control_data->img, 0, 0);

    // Display the appropriate object image based on selected type
    if (cp->data.obj_type == 0 && control_data->image.sphere)
        mlx_put_image_to_window(control_data->mlx, control_data->win, control_data->image.sphere, 10, 10);
    else if (cp->data.obj_type == 1 && control_data->image.plane)
        mlx_put_image_to_window(control_data->mlx, control_data->win, control_data->image.plane, 10, 10);
    else if (cp->data.obj_type == 2 && control_data->image.cylinder)
        mlx_put_image_to_window(control_data->mlx, control_data->win, control_data->image.cylinder, 10, 10);
    else if (cp->data.obj_type == 3 && control_data->image.cone)
        mlx_put_image_to_window(control_data->mlx, control_data->win, control_data->image.cone, 10, 10);

    mlx_string_put(control_data->mlx, control_data->win, 175, 130, 0xFF0000, "RENDER");
    draw_slider_amb_light(cp, my_slider);

    // Mostrar informações e sliders RGB da primeira esfera
    if (cp->sphere && cp->data.sphere_count > 0)
        redraw_interface(cp);

    control_win_hooks(control_data, cp);

    // Force refresh for cylinder maps
    if (cp->data.obj_type == 2 && cp->data.cylinder_count > 0)
    {
        printf("🔄 Cylinder %d selected - RGB: %.2f, %.2f, %.2f\n",
               cp->data.idx_obj,
               cp->cylinder[cp->data.idx_obj].rgb[0],
               cp->cylinder[cp->data.idx_obj].rgb[1],
               cp->cylinder[cp->data.idx_obj].rgb[2]);
        redraw_interface(cp);
    }

    return (0);
}
