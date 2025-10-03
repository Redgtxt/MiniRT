/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:01:22 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/03 14:02:43 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math/interval.h"

double	interval_size(t_interval interval)
{
	return (interval.max - interval.min);
}

bool	interval_contains(double x, t_interval interval)
{
	return (interval.min <= x && x <= interval.max);
}

t_interval	interval_create(double min, double max)
{
	t_interval	result;

	result.min = min;
	result.max = max;
	return (result);
}

bool	interval_surrounds(double x, t_interval interval)
{
	return (interval.min < x && x < interval.max);
}

double	clamp(double x, t_interval interval)
{
	if (interval.min > x)
		return (interval.min);
	if (x > interval.max)
		return (interval.max);
	return (x);
}
