/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/05/27 16:00:08 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//	Parses the sphere values
bool	parse_sphere(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	t_sphere	*sphere;

	if (double_array_len(element_info) != 4)
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_NBR_VALUES), false);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_MALLOC), false);
	lstadd_last_sphere(control_panel, sphere);
	if (!get_coord(&sphere->coord, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_COORD), false);
	if (!get_d(&sphere->d, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_D), false);
	//	RADIUS
	if (!get_rgb(&sphere->rgb, element_info[3], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_RGB), false);
	control_panel->data.sphere++;
	return (true);
}

//	Parses the plane values
bool	parse_plane(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	t_plane	*plane;

	if (double_array_len(element_info) != 4)
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_NBR_VALUES), false);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_MALLOC), false);
	lstadd_last_plane(control_panel, plane);
	if (!get_coord(&plane->coord, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_COORD), false);
	if (!get_vector(&plane->vector, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_VECTOR), false);
	if (!get_rgb(&plane->rgb, element_info[3], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_RGB), false);
	control_panel->data.plane++;
	return (true);
}

//	Parses the cylinder values
bool	parse_cylinder(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	t_cylinder	*cylinder;

	if (double_array_len(element_info) != 6)
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_NBR_VALUES), false);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_MALLOC), false);
	lstadd_last_cylinder(control_panel, cylinder);
	if (!get_coord(&cylinder->coord, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_COORD), false);
	if (!get_vector(&cylinder->vector, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_VECTOR), false);
	if (!get_d(&cylinder->d, element_info[3], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_D), false);
	//	Radius
	if (!get_height(&cylinder->height, element_info[4], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_HEIGHT), false);
	if (!get_rgb(&cylinder->rgb, element_info[5], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_RGB), false);
	control_panel->data.cylinder++;
	return (true);
}
