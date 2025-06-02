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

//	Parses the ambient_light values
bool	parse_amb_light(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	if (double_array_len(element_info) != 3)
		return (error_code(&error_log->code_error, ERR_ELEMENT_A, ERR_NBR_VALUES), false);
	if (!get_light_force(&control_panel->amb_light.light_force, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_A, ERR_LIGHT_FORCE), false);
	if (!get_rgb(&control_panel->amb_light.rgb, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_A, ERR_RGB), false);
	control_panel->data.amb_light++;
	return (true);
}

//	Parses the camera values
bool	parse_camera(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	if (double_array_len(element_info) != 4)
		return (error_code(&error_log->code_error, ERR_ELEMENT_C, ERR_NBR_VALUES), false);
	if (!get_coord(&control_panel->camera.coord, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_C, ERR_COORD), false);
	if (!get_vector(&control_panel->camera.vector, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_C, ERR_VECTOR), false);
	if (!get_fov(&control_panel->camera.fov, element_info[3], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_C, ERR_FOV), false);
	control_panel->data.camera++;
	return (true);
}

//	Parses the light values
bool	parse_light(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	size_t	len;

	len = double_array_len(element_info);
	if (len != 3 && len != 4)
		return (error_code(&error_log->code_error, ERR_ELEMENT_L, ERR_NBR_VALUES), false);
	if (!get_coord(&control_panel->light.coord, element_info[1], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_L, ERR_COORD), false);
	if (!get_brightness(&control_panel->light.brightness, element_info[2], error_log))
		return (error_code(&error_log->code_error, ERR_ELEMENT_L, ERR_BRIGHTNESS), false);
	if (len == 4)
	{
		if (!get_rgb(&control_panel->light.rgb, element_info[3], error_log))
			return (error_code(&error_log->code_error, ERR_ELEMENT_L, ERR_RGB), false);
	}
	control_panel->data.light++;
	return (true);
}
