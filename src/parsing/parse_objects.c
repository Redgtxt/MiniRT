/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/10/12 16:56:16 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool parse_sphere(t_control_panel *cp, char **element_info, t_error_log *err)
{
	t_sphere *sphere;
	size_t len;

	len = double_array_len(element_info);
	if (len < 4 || len > 6)
		return (error_code(&err->code_error, ERR_ELEM_SP, ERR_NBR_VAL), false);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (error_code(&err->code_error, ERR_ELEM_SP, ERR_MALLOC), false);
	lstadd_last_sphere(cp, sphere);
	if (!get_coord(sphere->cords, element_info[1], err))
		return (error_code(&err->code_error, ERR_ELEM_SP, ERR_COORD), false);
	if (!get_size(&sphere->d, element_info[2], err))
		return (error_code(&err->code_error, ERR_ELEM_SP, ERR_D), false);
	if (!get_rgb(sphere->rgb, element_info[3], err))
		return (error_code(&err->code_error, ERR_ELEM_SP, ERR_RGB), false);
	if (!get_material(&sphere->material, sphere->rgb, element_info[4], err))
		return (error_code(&err->code_error, ERR_ELEM_SP, ERR_MATERIAL), false);
	if (len == 6 && !get_bump_id(&sphere->material, element_info[5], err))
		return (error_code(&err->code_error, ERR_ELEM_SP, ERR_MATERIAL), false);
	cp->data.sphere_count++;
	return (true);
}

bool parse_plane(t_control_panel *cp, char **element_info, t_error_log *err)
{
	t_plane *plane;
	size_t len;

	len = double_array_len(element_info);
	if (len < 4 || len > 6)
		return (error_code(&err->code_error, ERR_ELEM_PL, ERR_NBR_VAL), false);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (error_code(&err->code_error, ERR_ELEM_PL, ERR_MALLOC), false);
	lstadd_last_plane(cp, plane);
	if (!get_coord(plane->cords, element_info[1], err))
		return (error_code(&err->code_error, ERR_ELEM_PL, ERR_COORD), false);
	if (!get_vector(plane->vec3, element_info[2], err))
		return (error_code(&err->code_error, ERR_ELEM_PL, ERR_VECTOR), false);
	if (!get_rgb(plane->rgb, element_info[3], err))
		return (error_code(&err->code_error, ERR_ELEM_PL, ERR_RGB), false);
	if (!get_material(&plane->material, plane->rgb, element_info[4], err))
		return (error_code(&err->code_error, ERR_ELEM_PL, ERR_MATERIAL), false);
	if (len == 6 && !get_bump_id(&plane->material, element_info[5], err))
		return (error_code(&err->code_error, ERR_ELEM_PL, ERR_MATERIAL), false);
	cp->data.plane_count++;
	return (true);
}

bool parse_cylinder(t_control_panel *cp, char **elem_info, t_error_log *err)
{
	t_cylinder *cylinder;
	size_t len;

	len = double_array_len(elem_info);
	if (len < 6 || len > 8)
		return (error_code(&err->code_error, ERR_ELEM_CY, ERR_NBR_VAL), false);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (error_code(&err->code_error, ERR_ELEM_CY, ERR_MALLOC), false);
	lstadd_last_cylinder(cp, cylinder);
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
	if (len == 8 && !get_bump_id(&cylinder->material, elem_info[7], err))
		return (error_code(&err->code_error, ERR_ELEM_CY, ERR_MATERIAL), false);
	cp->data.cylinder_count++;
	return (true);
}

bool parse_cone(t_control_panel *cp, char **element_info, t_error_log *err)
{
	t_cone *cone;
	size_t len;

	len = double_array_len(element_info);
	if (len < 6 || len > 8)
		return (error_code(&err->code_error, ERR_ELEM_CN, ERR_NBR_VAL), false);
	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (error_code(&err->code_error, ERR_ELEM_CN, ERR_MALLOC), false);
	lstadd_last_cone(cp, cone);
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
	if (len == 8 && !get_bump_id(&cone->material, element_info[7], err))
		return (error_code(&err->code_error, ERR_ELEM_CN, ERR_MATERIAL), false);
	cp->data.cone_count++;
	return (true);
}
