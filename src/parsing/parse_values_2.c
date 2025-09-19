/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/09/17 16:51:26 by randrade         ###   ########.fr       */
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
	if (!ft_atoc(info, fov))
		return (false);
	if (*fov > 180)
		return (error_code(&error_log->code_error, ERR_RANGE, 0), false);
	return (true);
}

bool	get_light_force(double *light_force, char *info, t_error_log *error_log)
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
	if (!ft_atod(info, light_force))
		return (error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	if (*light_force < 0.0 || *light_force > 1.0)
		return (error_code(&error_log->code_error, ERR_RANGE, 0), false);
	return (true);
}

//	NOTE: Melhorar precisao > 1.0
bool	get_brightness(double *brightness, char *info, t_error_log *error_log)
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
	if (!ft_atod(info, brightness))
		return (error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	if (*brightness < 0.0 || *brightness > 1.0) //	Melhorar precisao
		return (error_code(&error_log->code_error, ERR_RANGE, 0), false);
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
	if (!ft_atod(info, d))
		return (error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	return (true);
}

bool	get_height(double *height, char *info, t_error_log *error_log)
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
	if (!ft_atod(info, height))
		return (error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	return (true);
}
