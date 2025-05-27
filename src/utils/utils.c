#include "../../includes/miniRT.h"

double	ft_atod(const char *str)
{
	double long	value;
	double long	fraction;
	double		division;
	bool		negative;
	bool		decimal;

	if (!str)
		return (0);
	value = 0.0;
	fraction = 0.0;
	division = 10.0;
	negative = false;
	decimal = false;
	if (*str == '-')
		negative = true;
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
		{
			decimal = true;
			str++;
		}
		if (!decimal)
			value = (value * 10) + *str - 48;
		else
		{
			fraction += (*str - 48) / division; 
			division *= 10.0;
		}
		if ((negative && value > 2147483648.0) || (!negative && value > 2147483647.0))
			return (0);
		str++;
	}
 	if (negative)
		value *= -1;
	return ((double)value + fraction);
}
