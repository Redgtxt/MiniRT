/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/09/18 15:15:16 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	parse_amb_light(t_control_panel *cp, char **elem_info, t_error_log *err)
{
	if (double_array_len(elem_info) != 3)
		return (error_code(&err->code_error, ERR_ELEM_A, ERR_NBR_VAL), false);
	if (!get_brightness(&cp->amb_light.light_force, elem_info[1], err))
		return (error_code(&err->code_error, ERR_ELEM_A, ERR_BRIGHT), false);
	if (!get_rgb(cp->amb_light.rgb, elem_info[2], err))
		return (error_code(&err->code_error, ERR_ELEM_A, ERR_RGB), false);
	vec3_normalize(cp->amb_light.rgb, cp->amb_light.rgb);
	cp->data.amb_light_count++;
	if (cp->data.amb_light_count > 1)
		return (error_code(&err->code_error, ERR_ELEM_A, ERR_NBR_ELEM), false);
	return (true);
}

bool	parse_camera(t_control_panel *cp, char **element_info, t_error_log *err)
{
	if (double_array_len(element_info) != 4)
		return (error_code(&err->code_error, ERR_ELEM_C, ERR_NBR_VAL), false);
	if (!get_coord(cp->camera.cords, element_info[1], err))
		return (error_code(&err->code_error, ERR_ELEM_C, ERR_COORD), false);
	if (!get_vector(cp->camera.vec3, element_info[2], err))
		return (error_code(&err->code_error, ERR_ELEM_C, ERR_VECTOR), false);
	if (!get_fov(&cp->camera.fov, element_info[3], err))
		return (error_code(&err->code_error, ERR_ELEM_C, ERR_FOV), false);
	cp->data.camera_count++;
	if (cp->data.camera_count > 1)
		return (error_code(&err->code_error, ERR_ELEM_C, ERR_NBR_ELEM), false);
	return (true);
}

bool	parse_light(t_control_panel *cp, char **element_info, t_error_log *err)
{
	t_light	*light;
	size_t	len;

	len = double_array_len(element_info);
	if (len != 3 && len != 4)
		return (error_code(&err->code_error, ERR_ELEM_L, ERR_NBR_VAL), false);
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (error_code(&err->code_error, ERR_ELEM_L, ERR_MALLOC), false);
	lstadd_last_light(cp, light);
	if (!get_coord(light->cords, element_info[1], err))
		return (error_code(&err->code_error, ERR_ELEM_L, ERR_COORD), false);
	if (!get_brightness(&light->brightness, element_info[2], err))
		return (error_code(&err->code_error, ERR_ELEM_L, ERR_BRIGHT), false);
	if (len == 4)
	{
		if (!get_rgb(light->rgb, element_info[3], err))
			return (error_code(&err->code_error, ERR_ELEM_L, ERR_RGB), false);
	}
	cp->data.light_count++;
	return (true);
}
