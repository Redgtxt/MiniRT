/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/10/10 15:54:45 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_lambertian_material(t_material *material, double rgb[3])
{
	double	specular;

	specular = LAMBERTIAN_SPECULAR;
	material->type = LAMBERTIAN;
	vec3_copy(material->albedo, rgb);
	vec3_set(material->specular, specular, specular, specular);
	material->shininess = LAMBERTIAN_SHININESS;
	material->refraction_index = LAMBERTIAN_REFRACTION_INDEX;
}

void	set_metal_material(t_material *material, double rgb[3])
{
	double	specular;

	specular = METAL_SPECULAR;
	material->type = METAL;
	vec3_copy(material->albedo, rgb);
	vec3_set(material->specular, specular, specular, specular);
	material->shininess = METAL_SHININESS;
	material->refraction_index = METAL_REFRACTION_INDEX;
}

void	set_glass_material(t_material *material)
{
	double	specular;

	specular = GLASS_SPECULAR;
	material->type = GLASS;
	vec3_set(material->albedo, 1.0, 1.0, 1.0);
	vec3_set(material->specular, specular, specular, specular);
	material->shininess = GLASS_SHININESS;
	material->refraction_index = GLASS_REFRACTION_INDEX;
}

void	set_checker_material(t_material *material, double rgb[3])
{
	double	specular;

	specular = CHECKER_SPECULAR;
	material->type = CHECKERPATTERN;
	vec3_copy(material->albedo, rgb);
	vec3_set(material->specular, specular, specular, specular);
	material->shininess = CHECKER_SHININESS;
	material->checker_scale = CHECKER_SCALE;
}

void	set_solid_material(t_material *material, double rgb[3])
{
	double	specular;

	specular = SOLID_SPECULAR;
	material->type = SOLID;
	vec3_copy(material->albedo, rgb);
	vec3_set(material->specular, specular, specular, specular);
	material->shininess = SOLID_SHININESS;
	material->refraction_index = SOLID_REFRACTION_INDEX;
}
