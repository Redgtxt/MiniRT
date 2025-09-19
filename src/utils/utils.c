/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:10:48 by hguerrei          #+#    #+#             */
/*   Updated: 2025/06/09 17:23:26 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


size_t	double_array_len(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

bool	ft_atoc(const char *str, mini_int *dest)
{
	int	value;

	if (!str)
		return (0);
	value = 0;
	while (*str >= '0' && *str <= '9')
	{
		value = (value * 10) + *str - 48;
		if (value > 255)
			return (false);
		str++;
	}
	*dest = (mini_int)value;
	return (true);
}

bool ft_atod(const char *str, double *dest)
{
	long double value = 0.0, fraction = 0.0, division = 10.0;
	int negative = 1;
	bool decimal = false;

	if (!str || !dest)
		return false;
	if (*str == '-') {
		negative = -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
			decimal = true;
		else 
		{
			if (!decimal) 
			{
				value = value * 10.0 + (*str - '0');
				if (value > LDBL_MAX)
					return (false);
			}
			else 
			{
				fraction += (*str - '0') / division;
				division *= 10.0;
				if (fraction > LDBL_MAX)
					return false;
			}
		}
		str++;
	}
	value = negative * (value + fraction);
	if (value > DBL_MAX || value < -DBL_MAX)
		return false;
	*dest = (double)value;
	return true;
}
