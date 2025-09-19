/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/09/18 16:37:56 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <unistd.h>

static bool	parse_numbers(char *info, size_t *nbr_dot, t_error_log *error_log)
{
	if (!ft_isdigit(*info) && *info != '.' && *info != '-')
	{
		error_log->error_char_detail = *info;
		return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
	}
	if (*info == '.')
	{
		*nbr_dot += 1;
		if (!*(info + 1))
			return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), false);
		if (*(info + 1) && (!ft_isdigit(*(info + 1)) || !ft_isdigit(*(info - 1))))
			return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), false);
		if (*nbr_dot > 1)
			return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), false);
	}
	else if (*info == '-')
	{
		if ((*(info + 1) && !ft_isdigit(*(info + 1))) || *(info - 1) != ',')
			return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), false);
	}
	return (true);
}

static bool	parse_three_octet_values(char *info, t_error_log *error_log)
{
	size_t	nbr_comma;
	size_t	nbr_dot;

	if (*info == '.' || *info == ',' || (!ft_isdigit(*info) && *info != '-'))
		return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), false);
	nbr_comma = 0;
	while(*info)
	{
		info++;
		nbr_dot = 0;
		while (*info && *info != ',')
		{
			if (!parse_numbers(info, &nbr_dot, error_log))
				return (false);
			info++;
		}
		if (*info == ',')
			nbr_comma++;
		if (nbr_comma > 2)
				return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), false);
	}
	return (true);
}

//	COORDS //
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
		return (ft_free_double_array(array), error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	ft_free_double_array(array);
	return (true);
}

// VECTOR //
//	NOTE: Melhorar precisao > 1.0
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
		return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), ft_free_double_array(array), false);
	if (!ft_atod(array[0], &vector[0]) || !ft_atod(array[1], &vector[1])
			|| !ft_atod(array[2], &vector[2]))
		return (ft_free_double_array(array), error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	ft_free_double_array(array);
	if (vector[0] > 1.0 || vector[1] > 1.0 || vector[2] > 1.0
		|| vector[0] < -1.0 || vector[1] < -1.0 || vector[2] < -1.0) //	Melhorar precisao
		return (error_code(&error_log->code_error, ERR_RANGE, 0), false);
	return (true);
}

//	RGB //
static bool	parse_rgb_chars(char *info, t_error_log *error_log)
{
	size_t	nbr_comma;

	nbr_comma = 0;
	while(*info)
	{
		if (!ft_isdigit(*info))
		{
			if (*info == ',')
			{
				nbr_comma++;
				if (nbr_comma > 2)
					return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), false);
			}
			else
			{
				error_log->error_char_detail = *info;
				return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
			}
		}
		info++;
	}
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
		return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), ft_free_double_array(array), false);
	if (!ft_atod(array[0], &rgb[0]) || !ft_atod(array[1], &rgb[1])
			|| !ft_atod(array[2], &rgb[2]))
		return (ft_free_double_array(array), error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	if (rgb[0] < 0.0 || rgb[0] > 255.0 || rgb[1] < 0.0 || rgb[1] > 255.0
		|| rgb[2] < 0.0 || rgb[2] > 255.0)
		return (ft_free_double_array(array), error_code(&error_log->code_error, ERR_RANGE, 0), false);
	vec3_normalize(rgb, rgb);
	ft_free_double_array(array);
	return (true);
}
//	---	//

bool	get_material(t_material *object_material, double rgb[3], char *info, t_error_log *error_log)
{
	size_t	info_len;

	(void)error_log;
	info_len = ft_strlen(info);
	if (!info || (info_len == ft_strlen("LAMBERTIAN") && !ft_strncmp(info, "LAMBERTIAN", info_len)))
	{
		object_material->type = LAMBERTIAN;
		vec3_copy(object_material->albedo, rgb);
		set_lambertian_material(object_material);
	}
	else if (info_len == ft_strlen("METAL") && !ft_strncmp(info, "METAL", info_len))
	{
		object_material->type = METAL;
		vec3_copy(object_material->albedo, rgb);
		set_metal_material(object_material);
	}
	else if (info_len == ft_strlen("GLASS") && !ft_strncmp(info, "GLASS", info_len))
	{
		object_material->type = GLASS;
		// For glass, use white/clear albedo for transparency
		vec3_set(object_material->albedo, 1.0, 1.0, 1.0);
		set_glass_material(object_material);
	}
	else
		return (false);
	return (true);
}