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

bool	parse_numbers(char *info, size_t *nbr_dot, t_error_log *err, bool neg)
{
	if (!ft_isdigit(*info) && *info != '.' && *info != '-')
	{
		err->error_char_detail = *info;
		return (error_code(&err->code_error, ERR_INV_CHAR, 0), false);
	}
	if (*info == '.')
	{
		*nbr_dot += 1;
		if (!*(info + 1))
			return (error_code(&err->code_error, ERR_INV_VALUE, 0), false);
		if (*(info + 1) && (!ft_isdigit(*(info + 1))
				|| !ft_isdigit(*(info - 1))))
			return (error_code(&err->code_error, ERR_INV_VALUE, 0), false);
		if (*nbr_dot > 1)
			return (error_code(&err->code_error, ERR_INV_VALUE, 0), false);
	}
	else if (*info == '-' && neg == true)
	{
		if ((*(info + 1) && !ft_isdigit(*(info + 1))) || *(info - 1) != ',')
			return (error_code(&err->code_error, ERR_INV_VALUE, 0), false);
	}
	return (true);
}

bool	parse_three_octet_values(char *info, t_error_log *err)
{
	size_t	nbr_comma;
	size_t	nbr_dot;

	if (*info == '.' || *info == ',' || (!ft_isdigit(*info) && *info != '-'))
		return (error_code(&err->code_error, ERR_INV_VALUE, 0), false);
	nbr_comma = 0;
	while (*info)
	{
		info++;
		nbr_dot = 0;
		while (*info && *info != ',')
		{
			if (!parse_numbers(info, &nbr_dot, err, true))
				return (false);
			info++;
		}
		if (*info == ',')
			nbr_comma++;
		if (nbr_comma > 2)
			return (error_code(&err->code_error, ERR_INV_VALUE, 0), false);
	}
	return (true);
}

bool	parse_rgb_chars(char *info, t_error_log *error_log)
{
	size_t	nbr_comma;

	nbr_comma = 0;
	while (*info)
	{
		if (!ft_isdigit(*info))
		{
			if (*info == ',')
			{
				nbr_comma++;
				if (nbr_comma > 2)
					return (error_code(&error_log->code_error,
							ERR_INV_VALUE, 0), false);
			}
			else
			{
				error_log->error_char_detail = *info;
				return (error_code(&error_log->code_error,
						ERR_INV_CHAR, 0), false);
			}
		}
		info++;
	}
	return (true);
}

bool	parse_number_elements(t_data data, t_error_log *error_log)
{
	if (data.amb_light_count == 0)
		error_code(&error_log->code_error, ERR_ELEM_A, ERR_NO_ELEMENT);
	else if (data.camera_count == 0)
		error_code(&error_log->code_error, ERR_ELEM_C, ERR_NO_ELEMENT);
	else if (data.light_count == 0)
		error_code(&error_log->code_error, ERR_ELEM_L, ERR_NO_ELEMENT);
	if (error_log->code_error != 0)
	{
		error_log->line_nbr = 0;
		return (false);
	}
	return (true);
}
