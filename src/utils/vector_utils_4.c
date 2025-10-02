/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:21:10 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/02 15:21:33 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	vec3_add_dir(vec3 original[3], vec3 dir[3], double dist)
{
    original[0] = original[0] + dir[0] * dist;
    original[1] = original[1] + dir[1] * dist;
    original[2] = original[2] + dir[2] * dist;
}
/// @brief Calcular o produto vetorial (cross product) de dois vetores
/// @param out vetor de saída para armazenar o resultado
/// @param a primeiro vetor
/// @param b segundo vetor
void	vec3_cross(double out[3], const double a[3], const double b[3])
{
    out[0] = a[1] * b[2] - a[2] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
}

double	vec3_length(const double v[3])
{
    return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

void	vec3_add_scaled(double out[3], const double a[3], const double b[3],
		double s)
{
	double	scaled_b[3];

	vec3_scale(scaled_b, b, s);
	vec3_add(out, a, scaled_b);
}
