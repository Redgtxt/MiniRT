/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:59:33 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/02 14:52:59 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return (sqrt(linear_component));
	return (0);
}

int	write_color(double r, double g, double b)
{
	int			ir;
	int			ig;
	int			ib;
	t_interval	intensity;

	ir = linear_to_gamma(r);
	ig = linear_to_gamma(g);
	ib = linear_to_gamma(b);
	intensity = interval_create(0.000, 0.999);
	ir = (int)(256 * clamp(r, intensity));
	ig = (int)(256 * clamp(g, intensity));
	ib = (int)(256 * clamp(b, intensity));
	return ((ir << 16) | (ig << 8) | ib);
}
