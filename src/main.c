/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:25 by randrade          #+#    #+#             */
/*   Updated: 2026/08/20 16:31:49 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	mlx_hooks_and_loops(t_control_panel *cp)
{
	mlx_hook(cp->mlx->win, 17, 0, close_window, cp);
	mlx_key_hook(cp->mlx->win, key_hook, cp);
	mlx_hook(cp->mlx->win, 4, 1L << 2, main_window_mouse_handler, cp);
	mlx_loop(cp->mlx->mlx);
}

t_control_panel	*inicialize_cp(int argc, char *argv[])
{
	t_control_panel	*control_panel;

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
	return (control_panel);
}

int	main(int argc, char *argv[])
{
	t_mlx			mlx_data;
	t_control_panel	*cp;

	cp = inicialize_cp(argc, argv);
	if (!cp)
		return (1);
	srand(time(NULL));
	if (init_values_main_win(&mlx_data, cp))
		return (1);
	if (create_control_window(cp))
		return (1);
	render_scene(cp);
	mlx_hooks_and_loops(cp);
	return (0);
}
