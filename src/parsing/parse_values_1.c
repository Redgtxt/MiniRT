/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/07/15 18:07:36 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <unistd.h>

bool	get_coord(vec3 *coord, char *info, t_error_log *error_log)
{
	char	**array;
	size_t	i;

	array = NULL;
	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-' && info[i] != ',')
		{
			error_log->error_char_detail = info[i];
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		}
		i++;
	}
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (ft_free_double_array(array), false);
	if (!ft_atofd(array[0], &coord[0], 'd') || !ft_atofd(array[1], &coord[1], 'd')
			|| !ft_atofd(array[2], &coord[2], 'd'))
		return (ft_free_double_array(array), false);
	ft_free_double_array(array);
	return (true);
}

//	NOTE: Melhorar precisao > 1.0
bool	get_vector(vec3 *vector, char *info, t_error_log *error_log)
{
	char	**array;
	size_t	i;

	array = NULL;
	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-' && info[i] != ',')
		{
			error_log->error_char_detail = info[i];
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		}
		i++;
	}
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (ft_free_double_array(array), false);
	if (!ft_atofd(array[0], &vector[0], 'd') || !ft_atofd(array[1], &vector[1], 'd')
			|| !ft_atofd(array[2], &vector[2], 'd'))
		return (ft_free_double_array(array), false);
	ft_free_double_array(array);
	if (vector[0] > 1.0 || vector[1] > 1.0 || vector[2] > 1.0
		|| vector[0] < -1.0 || vector[1] < -1.0 || vector[2] < -1.0) //	Melhorar precisao
		return (false);
	return (true);
}

//	RGB //
static bool	parse_rgb_chars(char *info, t_error_log *error_log)
{
	size_t	nbr_len;

	nbr_len = 0;
	while(*info)
	{
		if (ft_isdigit(*info))
			nbr_len++;
		else if (*info == ',')
			nbr_len = 0;
		else
		{
			error_log->error_char_detail = *info;
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		}
		if (nbr_len > 3)
			return (false);
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
		return (ft_free_double_array(array), false);
	if (!ft_atofd(array[0], &rgb[0], 'd') || !ft_atofd(array[1], &rgb[1], 'd')
			|| !ft_atofd(array[2], &rgb[2], 'd'))
		return (ft_free_double_array(array), false);
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
	
	if (!info)
	{
		object_material->type = LAMBERTIAN;
		vec3_copy(object_material->albedo, rgb);
		vec3_set(object_material->specular, 0.5, 0.5, 0.5);
		object_material->shininess = 32.0;
		object_material->refraction_index = 1.0; // Air/vacuum
	}
	else if (info_len == ft_strlen("METAL") && !ft_strncmp(info, "METAL", info_len))
	{
		object_material->type = METAL;
		vec3_copy(object_material->albedo, rgb);
		vec3_set(object_material->specular, 1.0, 1.0, 1.0);
		object_material->shininess = 200.0;
		object_material->refraction_index = 1.0; // Not used for metal
	}
	else if (info_len == ft_strlen("GLASS") && !ft_strncmp(info, "GLASS", info_len))
	{
		object_material->type = GLASS;
		// For glass, use white/clear albedo for transparency
		vec3_set(object_material->albedo, 1.0, 1.0, 1.0);
		vec3_set(object_material->specular, 1.0, 1.0, 1.0);
		object_material->shininess = 200.0;
		object_material->refraction_index = 1.5; // Glass refractive index
	}
	else
		return (false);
	return (true);
}
