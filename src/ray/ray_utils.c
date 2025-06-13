/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:01:17 by hguerrei          #+#    #+#             */
/*   Updated: 2025/06/13 18:24:28 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/miniRT.h"

double degrees_to_radians(double degrees)
{
    return degrees * PI / 180.0;
}

double random_double_0_to_1()
{
    // Retorna um número real aleatório no intervalo [0, 1)
    return (double)rand() / ((double)RAND_MAX + 1.0);
}



double random_double(double min, double max) 
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double_0_to_1();
}

