/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:25 by randrade          #+#    #+#             */
/*   Updated: 2025/10/02 16:26:07 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
void print_elements(t_control_panel *control_panel)
{
    if (!control_panel)
    {
        fprintf(stderr, "Error: control_panel is NULL\n");
        return;
    }

    printf("Ambient Light:\n");
    printf("\t light_force = %.2f\n", control_panel->amb_light.light_force);
    printf("\t rgb = r-> %f g-> %f b-> %f\n", control_panel->amb_light.rgb[0], control_panel->amb_light.rgb[1], control_panel->amb_light.rgb[2]);

    printf("\nCamera:\n");
    printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->camera.cords[0], control_panel->camera.cords[1], control_panel->camera.cords[2]);
    printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->camera.vec3[0], control_panel->camera.vec3[1], control_panel->camera.vec3[2]);
    printf("\t fov = %d\n", control_panel->camera.fov);

    if (control_panel->light && control_panel->data.light_count > 0)
    {
        printf("\nLIGHT AFTER ARRAY CONVERSION:\n");
        for (size_t i = 0; i < control_panel->data.light_count; i++)
        {
            printf("\nLight %zu:\n", i + 1);
            printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n",
                   control_panel->light[i].cords[0],
                   control_panel->light[i].cords[1],
                   control_panel->light[i].cords[2]);
            printf("\t brightness = %.2f\n", control_panel->light[i].brightness);
            printf("\t rgb = r-> %f g-> %f b-> %f\n",
                   control_panel->light[i].rgb[0],
                   control_panel->light[i].rgb[1],
                   control_panel->light[i].rgb[2]);
        }
    }
    else
    {
        printf("\nNo light found or light array is NULL\n");
    }

    if (control_panel->sphere && control_panel->data.sphere_count > 0)
    {
        printf("\nSPHERES AFTER ARRAY CONVERSION:\n");
        for (size_t i = 0; i < control_panel->data.sphere_count; i++)
        {
            printf("\nSphere %zu:\n", i + 1);
            printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n",
                   control_panel->sphere[i].cords[0],
                   control_panel->sphere[i].cords[1],
                   control_panel->sphere[i].cords[2]);
            printf("\t d = %.2f (diameter)\n", control_panel->sphere[i].d);
            printf("\t radius = %.2f\n", control_panel->sphere[i].radius);
            printf("\t rgb = r-> %f g-> %f b-> %f\n",
                   control_panel->sphere[i].rgb[0],
                   control_panel->sphere[i].rgb[1],
                   control_panel->sphere[i].rgb[2]);
        }
    }
    else
    {
        printf("\nNo spheres found or sphere array is NULL\n");
    }

    if (control_panel->plane && control_panel->data.plane_count > 0)
    {
        printf("\nPLANES AFTER ARRAY CONVERSION:\n");
        for (size_t i = 0; i < control_panel->data.plane_count; i++)
        {
            printf("\nPlane %zu:\n", i + 1);
            printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n",
                   control_panel->plane[i].cords[0],
                   control_panel->plane[i].cords[1],
                   control_panel->plane[i].cords[2]);
            printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n",
                   control_panel->plane[i].vec3[0],
                   control_panel->plane[i].vec3[1],
                   control_panel->plane[i].vec3[2]);
            printf("\t rgb = r-> %f g-> %f b-> %f\n",
                   control_panel->plane[i].rgb[0],
                   control_panel->plane[i].rgb[1],
                   control_panel->plane[i].rgb[2]);
        }
    }
    else
    {
        printf("\nNo planes found or plane list is NULL\n");
    }

    if (control_panel->cylinder && control_panel->data.cylinder_count > 0)
    {
        printf("\nCYLINDER AFTER ARRAY CONVERSION:\n");
        for (size_t i = 0; i < control_panel->data.cylinder_count; i++)
        {
            printf("\nCylinder %zu:\n", i + 1);
            printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->cylinder[i].cords[0], control_panel->cylinder[i].cords[1], control_panel->cylinder[i].cords[2]);
            printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->cylinder[i].vec3[0], control_panel->cylinder[i].vec3[1], control_panel->cylinder[i].vec3[2]);
            printf("\t d = %.2f\n", control_panel->cylinder[i].d);
            printf("\t radius = %.2f\n", control_panel->cylinder[i].radius);
            printf("\t height = %.2f\n", control_panel->cylinder[i].height);
            printf("\t rgb = r-> %f g-> %f b-> %f\n", control_panel->cylinder[i].rgb[0], control_panel->cylinder[i].rgb[1], control_panel->cylinder[i].rgb[2]);
        }
    }
    else
    {
        printf("\nNo cylinders found or cylinder list is NULL\n");
    }

    if (control_panel->cone && control_panel->data.cone_count > 0)
    {
        printf("\nCONE AFTER ARRAY CONVERSION:\n");
        for (size_t i = 0; i < control_panel->data.cone_count; i++)
        {
            printf("\nCone %zu:\n", i + 1);
            printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->cone[i].cords[0], control_panel->cone[i].cords[1], control_panel->cone[i].cords[2]);
            printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->cone[i].vec3[0], control_panel->cone[i].vec3[1], control_panel->cone[i].vec3[2]);
            printf("\t d = %.2f\n", control_panel->cone[i].d);
            printf("\t radius = %.2f\n", control_panel->cone[i].radius);
            printf("\t height = %.2f\n", control_panel->cone[i].height);
            printf("\t rgb = r-> %f g-> %f b-> %f\n", control_panel->cone[i].rgb[0], control_panel->cone[i].rgb[1], control_panel->cone[i].rgb[2]);
        }
    }
    else
    {
        printf("\nNo cones found or cone list is NULL\n");
    }
    ft_printf("MiniRT Starting...\n");
}
*/

void	mlx_hooks_and_loops(t_control_panel *cp)
{
    mlx_hook(cp->mlx->win, 17, 0, close_window, cp);
    mlx_key_hook(cp->mlx->win, key_hook, cp);
    mlx_hook(cp->mlx->win, 4, 1L << 2, main_window_mouse_handler, cp);
    mlx_loop(cp->mlx->mlx);
}

t_control_panel *inicialize_cp(int argc, char *argv[])
{
    t_control_panel *control_panel;

    if (argc != 2)
        return (NULL);
    control_panel = ft_calloc(1, sizeof(t_control_panel));
    if (!control_panel)
		return (NULL);
    if (!parsing(control_panel, argv[1]))
    {
        print_parsing_error(&control_panel->error_log);
        return (free_control_panel(control_panel), NULL);
    }
    if (!linked_to_array(control_panel))
        return (perror("Error"), free_control_panel(control_panel), NULL);
    get_values_camera(control_panel);
    init_object_selection(control_panel);
    return control_panel;
}

int main(int argc, char *argv[])
{
    t_mlx mlx_data;
    t_control_panel *cp;

    cp = inicialize_cp(argc, argv);
    if (!cp)
        return 1;
    srand(time(NULL));
    if (init_values_main_win(&mlx_data, cp))
        return 1;
    if (create_control_window(cp))
        return 1;
    // print_elements(cp);
    render_scene(cp);
	mlx_hooks_and_loops(cp);
    return (0);
}
