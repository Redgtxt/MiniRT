/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/09/26 15:47:10 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_lambertian_material(t_material *material, double rgb[3])
{
	material->type = LAMBERTIAN;
	vec3_copy(material->albedo, rgb);
	vec3_set(material->specular, 0.5, 0.5, 0.5);
	material->shininess = 32.0;
	material->refraction_index = 1.0;
}

void	set_metal_material(t_material *material, double rgb[3])
{
	material->type = METAL;
	vec3_copy(material->albedo, rgb);
	vec3_set(material->specular, 1.0, 1.0, 1.0);
	material->shininess = 200.0;
	material->refraction_index = 1.0;
}

void	set_glass_material(t_material *material)
{
	material->type = GLASS;
	vec3_set(material->albedo, 1.0, 1.0, 1.0);
	vec3_set(material->specular, 1.0, 1.0, 1.0);
	material->shininess = 200.0;
	material->refraction_index = 1.5;
}

void	set_checker_material(t_material *material, double rgb[3])
{
	material->type = CHECKERPATTERN;
	vec3_copy(material->albedo, rgb);
	vec3_set(material->specular, 0.5, 0.5, 0.5);
	material->shininess = 32.0;
	material->checker_scale = 0.5;
}
