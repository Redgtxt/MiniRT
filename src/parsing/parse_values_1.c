/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/10/03 15:49:49 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	get_coord(vec3 *coord, char *info, t_error_log *error_log)
{
	char	**array;

	array = NULL;
	if (parse_three_octet_values(info, error_log) == false)
		return (false);
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (ft_free_double_array(array), false);
	if (!ft_atod(array[0], &coord[0]) || !ft_atod(array[1], &coord[1])
		|| !ft_atod(array[2], &coord[2]))
		return (ft_free_double_array(array),
			error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	ft_free_double_array(array);
	return (true);
}

bool	get_vector(vec3 *vector, char *info, t_error_log *error_log)
{
	char	**array;

	array = NULL;
	if (parse_three_octet_values(info, error_log) == false)
		return (false);
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (error_code(&error_log->code_error, ERR_INV_VALUE, 0),
			ft_free_double_array(array), false);
	if (!ft_atod(array[0], &vector[0]) || !ft_atod(array[1], &vector[1])
		|| !ft_atod(array[2], &vector[2]))
		return (ft_free_double_array(array), error_code(&error_log->code_error,
				ERR_OVERFLOW, 0), false);
	ft_free_double_array(array);
	if (vector[0] > 1.0 || vector[1] > 1.0 || vector[2] > 1.0
		|| vector[0] < -1.0 || vector[1] < -1.0 || vector[2] < -1.0)
		return (error_code(&error_log->code_error, ERR_RANGE, 0), false);
	return (true);
}

bool	get_rgb(double rgb[3], char *info, t_error_log *error_log)
{
	char	**array;

	array = NULL;
	if (parse_rgb_chars(info, error_log) == false)
		return (false);
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (error_code(&error_log->code_error, ERR_INV_VALUE, 0),
			ft_free_double_array(array), false);
	if (!ft_atod(array[0], &rgb[0]) || !ft_atod(array[1], &rgb[1])
		|| !ft_atod(array[2], &rgb[2]))
		return (ft_free_double_array(array), error_code(&error_log->code_error,
				ERR_OVERFLOW, 0), false);
	if (rgb[0] < 0.0 || rgb[0] > 255.0 || rgb[1] < 0.0 || rgb[1] > 255.0
		|| rgb[2] < 0.0 || rgb[2] > 255.0)
		return (ft_free_double_array(array), error_code(&error_log->code_error,
				ERR_RANGE, 0), false);
	vec3_normalize(rgb, rgb);
	ft_free_double_array(array);
	return (true);
}

bool	get_material(t_material *object_material, double rgb[3],
	char *info, t_error_log *error_log)
{
	size_t	info_len;

	info_len = ft_strlen(info);
	if (!info || (info_len == ft_strlen("LAMBERTIAN")
			&& !ft_strncmp(info, "LAMBERTIAN", info_len)))
		set_lambertian_material(object_material, rgb);
	else if (info_len == ft_strlen("METAL")
		&& !ft_strncmp(info, "METAL", info_len))
		set_metal_material(object_material, rgb);
	else if (info_len == ft_strlen("GLASS")
		&& !ft_strncmp(info, "GLASS", info_len))
		set_glass_material(object_material);
	else if (info_len == ft_strlen("CHECKERPATTERN")
		&& !ft_strncmp(info, "CHECKERPATTERN", info_len))
		set_checker_material(object_material, rgb);
	else if (info_len == ft_strlen("SOLID")
		&& !ft_strncmp(info, "SOLID", info_len))
		set_solid_material(object_material, rgb);
	else
	{
		error_log->error_str_detail = ft_strdup(info);
		return (error_code(&error_log->code_error, ERR_INV_MATERIAL, 0), false);
	}
	return (true);
}
