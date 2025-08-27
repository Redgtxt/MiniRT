/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/07/16 17:47:37 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <unistd.h>

void	set_solid_material(t_material *material)
{
	material->type = SOLID;
	vec3_set(material->specular, 0.5, 0.5, 0.5);
	material->shininess = 32.0;
	material->refraction_index = 1.0; // Air/vacuum
}

void	set_lambertian_material(t_material *material)
{
	material->type = LAMBERTIAN;
	vec3_set(material->specular, 0.5, 0.5, 0.5);
	material->shininess = 32.0;
	material->refraction_index = 1.0; // Air/vacuum
}

void	set_metal_material(t_material *material)
{
	material->type = METAL;
	vec3_set(material->specular, 1.0, 1.0, 1.0);
	material->shininess = 200.0;
	material->refraction_index = 1.0; // Not used for metal
}

void	set_glass_material(t_material *material)
{
	material->type = GLASS;
	vec3_set(material->specular, 1.0, 1.0, 1.0);
	material->shininess = 200.0;
	material->refraction_index = 1.5; // Glass refractive index
}

void	set_checker_material(t_material *material)
{
	material->type = CHECKERPATTERN;
	vec3_set(material->specular, 0.5, 0.5, 0.5);
	material->shininess = 32.0;
	material->checker_scale = 0.5; // Default scale
}
