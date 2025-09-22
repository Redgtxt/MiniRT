/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/07/11 17:18:12 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//	Parses the sphere values
bool	parse_sphere(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	t_sphere	*sphere;
	size_t		len;

	len = double_array_len(element_info);
	if (len != 4 && len != 5)
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_NBR_VALUES), false);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_MALLOC), false);
	lstadd_last_sphere(control_panel, sphere);
	if (!get_coord(sphere->cords, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_COORD), false);
	if (!get_d(&sphere->d, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_D), false);
	if (!get_rgb(sphere->rgb, element_info[3], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_RGB), false);
	if (!get_material(&sphere->material, sphere->rgb, element_info[4], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_MATERIAL), false);
	control_panel->data.sphere_count++;
	return (true);
}

//	Parses the plane values
bool	parse_plane(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	t_plane	*plane;
	size_t	len;

	len = double_array_len(element_info);
	if (len != 4 && len != 5)
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_NBR_VALUES), false);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_MALLOC), false);
	lstadd_last_plane(control_panel, plane);
	if (!get_coord(plane->cords, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_COORD), false);
	if (!get_vector(plane->vec3, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_VECTOR), false);
	if (!get_rgb(plane->rgb, element_info[3], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_RGB), false);
	if (!get_material(&plane->material, plane->rgb, element_info[4], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_MATERIAL), false);
	control_panel->data.plane_count++;
	return (true);
}

//	Parses the cylinder values
bool	parse_cylinder(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	t_cylinder	*cylinder;
	size_t	len;

	len = double_array_len(element_info);
	if (len != 6 && len != 7)
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_NBR_VALUES), false);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_MALLOC), false);
	lstadd_last_cylinder(control_panel, cylinder);
	if (!get_coord(cylinder->cords, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_COORD), false);
	if (!get_vector(cylinder->vec3, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_VECTOR), false);
	if (!get_d(&cylinder->d, element_info[3], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_D), false);
	if (!get_height(&cylinder->height, element_info[4], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_HEIGHT), false);
	if (!get_rgb(cylinder->rgb, element_info[5], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_RGB), false);
	if (!get_material(&cylinder->material, cylinder->rgb, element_info[6], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_MATERIAL), false);
	control_panel->data.cylinder_count++;
	return (true);
}
//	Parses the cone values
bool	parse_cone(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	t_cone	*cone;
	size_t	len;

	len = double_array_len(element_info);
	if (len != 6 && len != 7)
		return (error_code(&error_log->code_error, ERR_ELEMENT_CN, ERR_NBR_VALUES), false);
	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (error_code(&error_log->code_error, ERR_ELEMENT_CN, ERR_MALLOC), false);
	lstadd_last_cone(control_panel, cone);
	if (!get_coord(cone->cords, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CN, ERR_COORD), false);
	if (!get_vector(cone->vec3, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CN, ERR_VECTOR), false);
	if (!get_d(&cone->d, element_info[3], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CN, ERR_D), false);
	if (!get_height(&cone->height, element_info[4], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CN, ERR_HEIGHT), false);
	if (!get_rgb(cone->rgb, element_info[5], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CN, ERR_RGB), false);
	if (!get_material(&cone->material, cone->rgb, element_info[6], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CN, ERR_MATERIAL), false);
	control_panel->data.cone_count++;
	return (true);
}
