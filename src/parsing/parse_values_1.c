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

bool	get_coord(t_coord *coord, char *info, t_error_log *error_log)
{
	char	**array;
	size_t	i;

	array = NULL;
	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-' && info[i] != ',')
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		i++;
	}
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (ft_free_double_array(array), false);
	if (!ft_atofd(array[0], &coord->x, 'd') || !ft_atofd(array[1], &coord->y, 'd')
			|| !ft_atofd(array[2], &coord->z, 'd'))
		return (ft_free_double_array(array), false);
	ft_free_double_array(array);
	return (true);
}

//	NOTE: Melhorar precisao > 1.0
bool	get_vector(t_vector *vector, char *info, t_error_log *error_log)
{
	char	**array;
	size_t	i;

	array = NULL;
	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-' && info[i] != ',')
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		i++;
	}
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (ft_free_double_array(array), false);
	if (!ft_atofd(array[0], &vector->x, 'f') || !ft_atofd(array[1], &vector->y, 'f')
			|| !ft_atofd(array[2], &vector->z, 'f'))
		return (ft_free_double_array(array), false);
	ft_free_double_array(array);
	if (vector->x > 1.0 || vector->y > 1.0 || vector->z > 1.0
		|| vector->x < -1.0 || vector->y < -1.0 || vector->z < -1.0) //	Melhorar precisao
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
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		if (nbr_len > 3)
			return (false);
		info++;
	}
	return (true);
}

bool	get_rgb(t_rgb *rgb, char *info, t_error_log *error_log)
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
	if (!ft_atoc(array[0], &rgb->r) || !ft_atoc(array[1], &rgb->g)
			|| !ft_atoc(array[2], &rgb->b))
		return (ft_free_double_array(array), false);
	ft_free_double_array(array);
	return (true);
}
//	---	//
