/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:10:48 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/02 15:05:08 by ruigoncalve      ###   ########.fr       */
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

bool	convert_to_double(char *str, long double *val,
					long double *frac, long double *div)
{
    bool decimal;

	decimal = false;
    while ((*str >= '0' && *str <= '9') || *str == '.')
	{
        if (*str == '.')
            decimal = true;
        else
		{
            if (!decimal)
			{
                *val = *val * 10.0 + (*str - '0');
                if (*val > 2147483648)
                    return (false);
            }
			else
			{
                *frac += (*str - '0') / *div;
                *div *= 10.0;
            }
		}
        str++;
    }
	return (true);
}

bool 	ft_atod(const char *str, double *dest)
{
    long double value;
	long double fraction;
	long double division;
	long double result;
    int negative = 1;

	value = 0.0;
	fraction = 0.0;
	division = 10.0;
	result = 0.0;
    if (!str || !dest)
        return (false);
    if (*str == '-')
	{
        negative = -1;
        str++;
    }
	if (!convert_to_double((char *)str, &value, &fraction, &division))
		return (false);
    result = negative * (value + fraction);
    if (result > OVERFLOW_MAX_LIMIT || result < OVERFLOW_MIN_LIMIT)
        return (false);
    *dest = (double)result;
    return (true);
}
