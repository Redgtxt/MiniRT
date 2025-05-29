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

int main(int argc, char *argv[])
{
    t_control_panel *control_panel;

    if (argc != 2)
        return (1);
    control_panel = ft_calloc(1, sizeof(t_control_panel));
    if (!control_panel)
        return (1);
    parsing(control_panel, argv[1]);
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
