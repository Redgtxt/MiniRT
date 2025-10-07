/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:45:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/03 15:41:52 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	configure_material_properties(t_material *material,
		t_material_type type)
{
	if (!material)
		return ;
	if (type == LAMBERTIAN)
		set_lambertian_material(material, material->albedo);
	else if (type == METAL)
		set_metal_material(material, material->albedo);
	else if (type == CHECKERPATTERN)
		set_checker_material(material, material->albedo);
	else if (type == GLASS)
		set_glass_material(material);
	else if (type == SOLID)
		set_solid_material(material, material->albedo);
}
