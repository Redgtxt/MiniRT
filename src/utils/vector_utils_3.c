/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:17:47 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/02 15:19:52 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/// @brief Criar um vetor zero (0,0,0)
/// @param v vetor que vai ser definido como zero
void	vec3_zero(double v[3])
{
	v[0] = 0.0;
	v[1] = 0.0;
	v[2] = 0.0;
}

/**
 * @brief Gera um vetor com valores aleatórios no intervalo [0,1)
 * @param out Vetor de saída para armazenar os valores gerados
 */
void	vec3_random(double out[3])
{
	out[0] = random_double_0_to_1();
	out[1] = random_double_0_to_1();
	out[2] = random_double_0_to_1();
}

/**
 * @brief Gera um vetor com valores aleatórios no intervalo [min,max)
 * @param out Vetor de saída para armazenar os valores gerados
 * @param min Valor mínimo do intervalo
 * @param max Valor máximo do intervalo
 */
void	vec3_random_range(double out[3], double min, double max)
{
	out[0] = random_double(min, max);
	out[1] = random_double(min, max);
	out[2] = random_double(min, max);
}

void	vec3_random_utit_vector(double good_point[3])
{
	double	p[3];
	double	lensq;

	vec3_zero(p);
	vec3_zero(good_point);
	while (true)
	{
		vec3_random_range(p, -1, 1);
		lensq = lenght_squared(p);
		if (1e-160 < lensq && lensq <= 1)
		{
			vec3_divide(good_point, p, sqrt(lensq));
			break ;
		}
	}
}

bool	vec3_near_zero(double out[3])
{
	double	s;

	s = 1e-8;
	return (fabs(out[0]) < s && fabs(out[1]) < s && fabs(out[2]) < s);
}
