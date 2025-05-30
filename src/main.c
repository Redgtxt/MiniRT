/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:25 by randrade          #+#    #+#             */
/*   Updated: 2025/05/27 13:43:22 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	print_elements(t_control_panel *control_panel)
{
	if (!control_panel)
	{
		fprintf(stderr, "Error: control_panel is NULL\n");
		return;
	}

	printf("Ambient Light:\n");
	printf("\t light_force = %.2f\n", control_panel->amb_light.light_force);
	printf("\t rgb = r-> %d g-> %d b-> %d\n", control_panel->amb_light.rgb.r, control_panel->amb_light.rgb.g, control_panel->amb_light.rgb.b);

	printf("\nCamera:\n");
	printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->camera.coord.x, control_panel->camera.coord.y, control_panel->camera.coord.z);
	printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->camera.vector.x, control_panel->camera.vector.y, control_panel->camera.vector.z);
	printf("\t fov = %d\n", control_panel->camera.fov);

	printf("\nLight:\n");
	printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->light.coord.x, control_panel->light.coord.y, control_panel->light.coord.z);
	printf("\t brightness = %.2f\n", control_panel->light.brightness);
	printf("\t rgb = r-> %d g-> %d b-> %d\n", control_panel->light.rgb.r, control_panel->light.rgb.g, control_panel->light.rgb.b);

	if (control_panel->sphere)
	{
		printf("\nSphere:\n");
		printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->sphere->coord.x, control_panel->sphere->coord.y, control_panel->sphere->coord.z);
		printf("\t d = %.2f\n", control_panel->sphere->d);
		printf("\t radius = %.2f\n", control_panel->sphere->radius);
		printf("\t rgb = r-> %d g-> %d b-> %d\n", control_panel->sphere->rgb.r, control_panel->sphere->rgb.g, control_panel->sphere->rgb.b);
	}
	else
	{
		fprintf(stderr, "Warning: sphere is NULL\n");
	}

	if (control_panel->plane)
	{
		printf("\nPlane:\n");
		printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->plane->coord.x, control_panel->plane->coord.y, control_panel->plane->coord.z);
		printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->plane->vector.x, control_panel->plane->vector.y, control_panel->plane->vector.z);
		printf("\t rgb = r-> %d g-> %d b-> %d\n", control_panel->plane->rgb.r, control_panel->plane->rgb.g, control_panel->plane->rgb.b);
	}
	else
	{
		fprintf(stderr, "Warning: plane is NULL\n");
	}

	if (control_panel->cylinder)
	{
		printf("\nCylinder:\n");
		printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->cylinder->coord.x, control_panel->cylinder->coord.y, control_panel->cylinder->coord.z);
		printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->cylinder->vector.x, control_panel->cylinder->vector.y, control_panel->cylinder->vector.z);
		printf("\t d = %.2f\n", control_panel->cylinder->d);
		printf("\t radius = %.2f\n", control_panel->cylinder->radius);
		printf("\t height = %.2f\n", control_panel->cylinder->height);
		printf("\t rgb = r-> %d g-> %d b-> %d\n", control_panel->cylinder->rgb.r, control_panel->cylinder->rgb.g, control_panel->cylinder->rgb.b);
	}
	else
	{
		fprintf(stderr, "Warning: cylinder is NULL\n");
	}
}

int main(int argc, char *argv[])
{
    t_control_panel *control_panel;

    if (argc != 2)
        return (1);
    control_panel = ft_calloc(1, sizeof(t_control_panel));
    if (!control_panel)
        return (1);
    if (parsing(control_panel, argv[1]))
    	print_elements(control_panel);
    if (control_panel->sphere)
    	free(control_panel->sphere);
    if (control_panel->plane)
    	free(control_panel->plane);
    if (control_panel->cylinder)
    	free(control_panel->cylinder);
    free(control_panel);
    return (0);
}


    // void *mlx;
    // void *mlx_win;

    // ft_printf("MiniRT Starting...\n");

    // mlx = mlx_init();
    // if (!mlx)
    // {
    //     ft_printf("Error: Could not initialize MLX\n");
    //     return (1);
    // }

    // mlx_win = mlx_new_window(mlx, WINDOW_HEIGHT, WINDOW_WIDTH, "miniRT");
    // if (!mlx_win)
    // {
    //     ft_printf("Error: Could not create window\n");
    //     return (1);
    // }

    // int i = 0;
    // while (WINDOW_HEIGHT >= i)
    // {

    //     int j = 0;

    //     while (WINDOW_WIDTH >= j)
    //     {
    //         mlx_pixel_put(mlx, mlx_win, i,j, 0x0000FF);
    //         mlx_pixel_put(mlx, mlx_win, i,0, 0xFF0000);
    //        j++;
    //     }

    //     i++;
    // }


    // ft_printf("Window created successfully\n");
    // mlx_loop(mlx);
