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

static bool	parse_numbers(char *info, size_t *nbr_dot, t_error_log *error_log)
{
	if (!ft_isdigit(*info) && *info != '.')
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
	return (true);
}

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
		return (error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	if (*fov > 180)
		return (error_code(&error_log->code_error, ERR_RANGE, 0), false);
	return (true);
}

//	NOTE: Melhorar precisao > 1.0
bool	get_brightness(double *brightness, char *info, t_error_log *error_log)
{
	size_t	nbr_dot;
	size_t	i;

	nbr_dot = 0;
	i = 0;
	if (*info == '.')
		return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), false);
	while(info[i])
	{
		if (!parse_numbers(&info[i], &nbr_dot, error_log))
			return (false);
		i++;
	}
	if (!ft_atod(info, brightness))
		return (error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	if (*brightness > 1.0) //	Melhorar precisao
		return (error_code(&error_log->code_error, ERR_RANGE, 0), false);
	return (true);
}

bool	get_size(double *d, char *info, t_error_log *error_log)
{
	size_t	nbr_dot;
	size_t	i;

	nbr_dot = 0;
	i = 0;
	if (*info == '.')
		return (error_code(&error_log->code_error, ERR_INVALID_VALUE, 0), false);
	while(info[i])
	{
		if (!parse_numbers(&info[i], &nbr_dot, error_log))
			return (false);
		i++;
	}
	if (!ft_atod(info, d))
		return (error_code(&error_log->code_error, ERR_OVERFLOW, 0), false);
	return (true);
}
