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

bool	get_fov(mini_int *fov, char *info, t_error_log *error_log)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]))
		{
			error_log->error_char_detail = info[i];
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		}
		i++;
	}
	if (!ft_atoc(info, fov) || *fov > 180)
		return (false);
	return (true);
}

bool	get_light_force(float *light_force, char *info, t_error_log *error_log)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-')
		{
			error_log->error_char_detail = info[i];
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		}
		i++;
	}
	if (!ft_atofd(info, light_force, 'f'))
		return (false);
	return (true);
}

//	NOTE: Melhorar precisao > 1.0
bool	get_brightness(float *brightness, char *info, t_error_log *error_log)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.')
		{
			error_log->error_char_detail = info[i];
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		}
		i++;
	}
	if (!ft_atofd(info, brightness, 'f'))
		return (false);
	if (*brightness > 1.0) //	Melhorar precisao
		return (false);
	return (true);
}

bool	get_d(double *d, char *info, t_error_log *error_log)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.')
		{
			error_log->error_char_detail = info[i];
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		}
		i++;
	}
	if (!ft_atofd(info, d, 'd'))
		return (false);
	return (true);
}

bool	get_height(double *height, char *info, t_error_log *error_log)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-')
		{
			error_log->error_char_detail = info[i];
			return (error_code(&error_log->code_error, ERR_INVALID_CHAR, 0), false);
		}
		i++;
	}
	if (!ft_atofd(info, height, 'd'))
		return (false);
	return (true);
}
