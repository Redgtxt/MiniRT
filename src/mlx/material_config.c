/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:45:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/17 16:37:11 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	configure_lambertian_material(t_material *material)
{
	if (!material)
		return ;
	material->shininess = 0.0;
}

static void	configure_metal_material(t_material *material)
{
	if (!material)
		return ;
	material->shininess = 50.0;
	material->specular[0] = 0.8;
	material->specular[1] = 0.8;
	material->specular[2] = 0.8;
}

static void	configure_checker_material(t_material *material)
{
	if (!material)
		return ;
	material->shininess = 0.0;
	material->checker_scale = 0.5;
}

static void	configure_glass_material(t_material *material)
{
	if (!material)
		return ;
	material->shininess = 200.0;
	material->refraction_index = 1.5;
	material->specular[0] = 1.0;
	material->specular[1] = 1.0;
	material->specular[2] = 1.0;
}

void	configure_material_properties(t_material *material,
		t_material_type type)
{
	if (!material)
		return ;
	if (type == LAMBERTIAN)
		configure_lambertian_material(material);
	else if (type == METAL)
		configure_metal_material(material);
	else if (type == CHECKERPATTERN)
		configure_checker_material(material);
	else if (type == GLASS)
		configure_glass_material(material);
}
