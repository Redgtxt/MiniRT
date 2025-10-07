/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:14:38 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/02 15:14:50 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// vai returnar o tamanho de um vetor
double	vec3_lenght(const double vector[3])
{
	return (sqrt(lenght_squared(vector)));
}

void	vec3_normalize(double out[3], const double v[3])
{
	double	temp_v[3];
	double	len;

	vec3_copy(temp_v, v);
	len = vec3_lenght(temp_v);
	if (len == 0.0)
		vec3_zero(out);
	else
		vec3_scale(out, v, 1.0 / len);
}

/// @brief Calcular um ponto ao longo de um raio
/// @param t parâmetro do raio (distância)
/// @param ray raio que contém origem e direção
/// @param result vetor onde será armazenado o ponto calculado
///
/// Fórmula: P(t) = A + t*B
/// onde A é a origem do raio e B é a direção do raio
void	ray_at(double t, t_ray ray, double result[3])
{
	double	scaled_direction[3];

	vec3_scale(scaled_direction, ray.direction, t);
	vec3_add(result, ray.origin, scaled_direction);
}

/// @brief Change the value of a VECTOR
/// @param v vector that you want to change the value
/// @param x x position
/// @param y y position
/// @param z z position
void	vec3_set(double v[3], double x, double y, double z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

/// @brief Copy the content of a VECTOR to other VECTOR
/// @param dest Vector returned from copied
/// @param src  Vector used to copy
void	vec3_copy(double dest[3], const double src[3])
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}
