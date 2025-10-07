/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:02:04 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/07 17:11:15 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

double	random_double_0_to_1(void)
{
	return ((double)rand() / ((double)RAND_MAX + 1.0));
}

double	random_double(double min, double max)
{
	return (min + (max - min) * random_double_0_to_1());
}
