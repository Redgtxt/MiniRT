/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:22:13 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/02 15:22:14 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/// @brief Add the value of a complet vector example a[0] + b[0]
/// @param out // Vector with the final result
/// @param a //Vector used to calculat
/// @param b //Vector used to calculat
void	vec3_add(double out[3], const double a[3], const double b[3])
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}

/// @brief Subtract the value of a complet vector example a[0] - b[0]
/// @param out // Vector with the final result
/// @param a //Vector used to calculat
/// @param b //Vector used to calculat
void	vec3_sub(double out[3], const double a[3], const double b[3])
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

/// @brief Element-wise multiplication of two vectors
/// @param out output vector to store the result
/// @param a first input vector
/// @param b second input vector
void	vec3_multiply(double out[3], const double a[3], const double b[3])
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}

/// @brief Divide a vector by a scalar
/// @param out output vector to store the result
/// @param v input vector
/// @param t scalar divisor
void	vec3_divide(double out[3], const double v[3], double t)
{
    vec3_scale(out, v, 1.0 / t);
}

/// @brief Scale a VECTOR by a scalar value
/// @param out vector to store the result
/// @param v input vector
/// @param s scalar value
void	vec3_scale(double out[3], const double v[3], double scaleFactor)
{
	out[0] = v[0] * scaleFactor;
	out[1] = v[1] * scaleFactor;
	out[2] = v[2] * scaleFactor;
}
