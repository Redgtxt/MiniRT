/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:26:52 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/12 18:05:47 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// parse checker
bool	parse_cyl(t_cylinder *cylinder, char **elem_info, t_error_log *err)
{
	if (!get_coord(cylinder->cords, elem_info[1], err))
		return (error_code(&err->code_error, ERR_ELEM_CY, ERR_COORD), false);
	if (!get_vector(cylinder->vec3, elem_info[2], err))
		return (error_code(&err->code_error, ERR_ELEM_CY, ERR_VECTOR), false);
	if (!get_size(&cylinder->d, elem_info[3], err))
		return (error_code(&err->code_error, ERR_ELEM_CY, ERR_D), false);
	if (!get_size(&cylinder->height, elem_info[4], err))
		return (error_code(&err->code_error, ERR_ELEM_CY, ERR_HEIGHT), false);
	if (!get_rgb(cylinder->rgb, elem_info[5], err))
		return (error_code(&err->code_error, ERR_ELEM_CY, ERR_RGB), false);
	if (!get_material(&cylinder->material, cylinder->rgb, elem_info[6], err))
		return (error_code(&err->code_error, ERR_ELEM_CY, ERR_MATERIAL), false);
	return (true);
}

bool	parse_cone_checks(t_cone *cone, char **element_info, t_error_log *err)
{
	if (!get_coord(cone->cords, element_info[1], err))
		return (error_code(&err->code_error, ERR_ELEM_CN, ERR_COORD), false);
	if (!get_vector(cone->vec3, element_info[2], err))
		return (error_code(&err->code_error, ERR_ELEM_CN, ERR_VECTOR), false);
	if (!get_size(&cone->d, element_info[3], err))
		return (error_code(&err->code_error, ERR_ELEM_CN, ERR_D), false);
	if (!get_size(&cone->height, element_info[4], err))
		return (error_code(&err->code_error, ERR_ELEM_CN, ERR_HEIGHT), false);
	if (!get_rgb(cone->rgb, element_info[5], err))
		return (error_code(&err->code_error, ERR_ELEM_CN, ERR_RGB), false);
	if (!get_material(&cone->material, cone->rgb, element_info[6], err))
		return (error_code(&err->code_error, ERR_ELEM_CN, ERR_MATERIAL), false);
	return (true);
}

void	parse_element_2(t_control_panel *control_panel, char **element_info)
{
	control_panel->error_log.element = ft_strdup(element_info[0]);
	error_code(&control_panel->error_log.code_error, INV_ELEM, 0);
}
