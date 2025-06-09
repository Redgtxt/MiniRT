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

bool	ft_atofd(const char *str, void *dest, char type)
{
	long double	value;
	long double	fraction;
	long double	division;
	double		negative;
	bool		decimal;

	if (!str || !dest || !type)
		return (false);
	value = 0.0;
	fraction = 0.0;
	division = 10.0;
	negative = 1.0;
	decimal = false;
	if (*str == '-')
	{
		negative = -1.0;
		str++;
	}
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
		{
			if (decimal)
				return (false);
			decimal = true;
		}
		else if (!decimal)
			value = (value * 10.0) + (*str - 48);
		else
		{
			fraction += (*str - 48) / division;
			division *= 10.0;
		}
		if ((type == 'd' && value + fraction > DBL_MAX)
			|| (type == 'f' && value + fraction > FLT_MAX))
			return (false);
		str++;
	}
	if (*str == '-')
		return (false);
	value = negative * (value + fraction);
	// Precision loss check if fraction is essentially zero (integer)
	if (fabsl(fraction) < 1e-15L)
	{
    	if (type == 'f')
     	{
        	if (fabsl(value) > 16777216.0L) // 2^24
            	return (false);
      	}
      	else if (type == 'd')
        {
        	if (fabsl(value) > 9007199254740992.0L) // 2^53
            	return (false);
        }
	}
	if (type == 'f')
		*(float *)dest = (float)value;
	else if (type == 'd')
		*(double *)dest = (double)value;
	return (true);
}
