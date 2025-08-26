/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_slider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:02:29 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/24 16:51:32 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void init_rgb_sliders(t_control_panel *cp, double *r, double *g, double *b)
{
	int red_dragging;
	int green_dragging;
	int blue_dragging;

	red_dragging = cp->config_win->red_slider.is_dragging;
	green_dragging = cp->config_win->green_slider.is_dragging;
	blue_dragging = cp->config_win->blue_slider.is_dragging;

	// Configure RGB sliders with the current object values
	cp->config_win->red_slider = (t_slider){60, 250, 300, 10, 20, 30, 0.0, 1.0,
											*r, 0x808080, 0xFF0000, red_dragging};
	cp->config_win->green_slider = (t_slider){60, 280, 300, 10, 20, 30, 0.0,
											  1.0, *g, 0x808080, 0x00FF00, green_dragging};
	cp->config_win->blue_slider = (t_slider){60, 310, 300, 10, 20, 30, 0.0, 1.0,
											 *b, 0x808080, 0x0000FF, blue_dragging};
}
static void draw_rgb_sliders(t_control_panel *cp, double *r, double *g, double *b)
{
	init_rgb_sliders(cp, r, g, b);
	char r_str[20], g_str[20], b_str[20];
	// Draw the sliders
	draw_slider(cp, cp->config_win->red_slider);
	draw_slider(cp, cp->config_win->green_slider);
	draw_slider(cp, cp->config_win->blue_slider);
	// Labels for the sliders melhorados
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 25, 265, 0xFF4040,
				   "Red:");
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 15, 295, 0x40FF40,
				   "Green:");
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 20, 325, 0x4040FF,
				   "Blue:");
	sprintf(r_str, "%.2f", *r);
	sprintf(g_str, "%.2f", *g);
	sprintf(b_str, "%.2f", *b);
	// Valores atuais alinhados à direita dos sliders
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 380, 262,
				   COLOR_WHITE, r_str);
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 380, 292,
				   COLOR_WHITE, g_str);
	mlx_string_put(cp->config_win->mlx, cp->config_win->win, 380, 322,
				   COLOR_WHITE, b_str);
}
static void assign_rgb_values(double *rgb, double *r, double *g, double *b)
{
	*r = rgb[0];
	*g = rgb[1];
	*b = rgb[2];
}

int get_rgb_values(t_control_panel *cp, double *r, double *g, double *b)
{
	if (is_valid_sphere(cp) && cp->sphere)
	{
		assign_rgb_values(cp->sphere[cp->data.idx_obj].rgb, r, g, b);
		return 1;
	}
	else if (is_valid_plane(cp) && cp->plane)
	{
		assign_rgb_values(cp->plane[cp->data.idx_obj].rgb, r, g, b);
		return 1;
	}
	else if (is_valid_cylinder(cp) && cp->cylinder)
	{
		assign_rgb_values(cp->cylinder[cp->data.idx_obj].rgb, r, g, b);
		return 1;
	}
	else if (is_valid_cone(cp) && cp->cone)
	{
		assign_rgb_values(cp->cone[cp->data.idx_obj].rgb, r, g, b);
		return 1;
	}
	return 0;
}
void create_rgb_sliders(t_control_panel *cp)
{

	double r;
	double g;
	double b;

	if (!cp || !cp->config_win)
		return;

	r = 0;
	g = 0;
	b = 0;
	get_rgb_values(cp, &r, &g, &b);
	draw_rgb_sliders(cp, &r, &g, &b);
}