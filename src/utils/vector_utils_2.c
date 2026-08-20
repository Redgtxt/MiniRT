/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:15:24 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/02 15:36:13 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// returna o tamanho de um vetor ao quadrado
/*
	esta funcao serve para calcular o valor total de um vetor para depois
	so ter de calcular a raiz quadrada em um valor em ves de ter de fazer
	em varios individuais
*/
double	lenght_squared(const double vector[3])
{
	return (vector[0] * vector[0] + vector[1] * vector[1] + vector[2]
		* vector[2]);
}

/// @brief Calculate the dot product of two vectors
/// @param a First input vector
/// @param b Second input vector
/// @return The dot product of the two vectors
double	vec3_dot(const double a[3], const double b[3])
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

/// @brief Negate a vector (equivalent to operator-)
/// @param out output vector to store the result
/// @param v input vector
void	vec3_negate(double out[3], const double v[3])
{
	out[0] = -v[0];
	out[1] = -v[1];
	out[2] = -v[2];
}

/// @brief Criar um vetor unitário (normalizado) a partir de um vetor
/// @param out vetor de saída onde será armazenado o vetor unitário
/// @param v vetor de entrada a ser normalizado
///
/// Esta função calcula v / |v| onde |v| é o comprimento do vetor
void	vec3_unit_vector(double out[3], const double v[3])
{
	double	len;

	len = vec3_lenght((double *)v);
	if (len == 0.0)
		vec3_zero(out);
	else
		vec3_scale(out, v, 1.0 / len);
}

void	vec3_sub_chain(double out[3], const double a[3], const double b[3],
		const double c[3])
{
	out[0] = a[0] - b[0] - c[0];
	out[1] = a[1] - b[1] - c[1];
	out[2] = a[2] - b[2] - c[2];
}
