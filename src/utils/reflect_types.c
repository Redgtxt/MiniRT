/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:24:20 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/02 15:28:45 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/// @brief Reflect a vector v around a normal n
/// @param v vector to be reflected
/// @param n normal vector to reflect around
/// @param out output vector to store the reflected result
/// @details The reflection formula is: reflected = v - 2 * dot(v, n) * n
/// where dot(v, n) is the dot product of v and n.
/// This function assumes that n is a unit normal vector.
/// If n is not unit length, the result will not be correct.
/// @note This function modifies the out vector directly.
void	reflect(const double v[3], const double n[3], double out[3])
{
    double dot_product;
    double scaled_normal[3];
    
	dot_product = vec3_dot(v, n);
    vec3_scale(scaled_normal, n, 2.0 * dot_product);
    vec3_sub(out, v, scaled_normal);
}

void	refract(const double uv[3], const double n[3],
			double etai_over_etat, double out[3])
{
	t_refract_data data;
	double r_out_parallel[3];

	vec3_negate(data.uv_negated, uv);
	data.cos_theta = vec3_dot(data.uv_negated, n);
	if (data.cos_theta > 1.0)
		data.cos_theta = 1.0;
	calc_perpendicular(&data, uv, n, etai_over_etat);
	calc_parallel(r_out_parallel, n, data.r_out_perp);
	vec3_add(out, data.r_out_perp, r_out_parallel);
}

/// @brief Schlick's approximation for reflectance (Fresnel effect)
/// @param cosine cosine of the incident angle
/// @param refraction_index refractive index of the material
/// @return reflectance probability (0.0 to 1.0)
double	schlick_reflectance(double cosine, double refraction_index)
{
    double r0;

	r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
    r0 = r0 * r0;
    return (r0 + (1.0 - r0) * pow((1.0 - cosine), 5));
}

/// @brief Se front_face for 1 significa que o raio bateu na parte de
/// tras da esfera.
///        Se front_face for 0 significa que batemos de frente na esfera
/// @param ray
/// @param
/// @param record
void	set_face_normal(const t_ray *ray, const double outward_normal[3],
			t_hit_record *record)
{
    record->front_face = vec3_dot(ray->direction, outward_normal) < 0;
    if (record->front_face)
        vec3_copy(record->normal, outward_normal);
    else
        vec3_negate(record->normal, outward_normal);
}
