#include "../../includes/miniRT.h"

void	error_code(t_error *error_code, int flag_one, int flag_two)
{
	if (flag_one)
		*error_code |= flag_one;
	if (flag_two)
		*error_code |= flag_two;
	return ;
}

// error_codes.c
int	has_error(t_error error_code, int flag)
{
	return ((error_code & flag) != 0);
}

static char	*get_element(t_error error_code)
{
	if (has_error(error_code, INV_ELEMENT))
		return ("Invalid type");
	else if (has_error(error_code, ERR_ELEMENT_A))
		return ("Ambient_light");
	else if (has_error(error_code, ERR_ELEMENT_C))
		return ("Camera");
	else if (has_error(error_code, ERR_ELEMENT_L))
		return ("Light");
	else if (has_error(error_code, ERR_ELEMENT_SP))
		return ("Sphere");
	else if (has_error(error_code, ERR_ELEMENT_PL))
		return ("Plane");
	else if (has_error(error_code, ERR_ELEMENT_CY))
		return ("Cylinder");
	return (NULL);
}

static char	*get_value(t_error error_code)
{
	if (has_error(error_code, ERR_COORD))
		return ("Coordenates");
	else if (has_error(error_code, ERR_VECTOR))
		return ("Vector");
	else if (has_error(error_code, ERR_RGB))
		return ("RGB");
	else if (has_error(error_code, ERR_FOV))
		return ("FOV");
	else if (has_error(error_code, ERR_LIGHT_FORCE))
		return ("Light force");
	else if (has_error(error_code, ERR_BRIGHTNESS))
		return ("Brightness");
	else if (has_error(error_code, ERR_D))
		return ("Diameter");
	else if (has_error(error_code, ERR_HEIGHT))
		return ("Height");
	return ("No value");
}

static char	*get_general_error(t_error error_code)
{
	if (has_error(error_code, ERR_MALLOC))
		return ("Memory allocation");
	else if (has_error(error_code, ERR_OVERFLOW))
		return ("Overflow");
	else if (has_error(error_code, ERR_NEGATIVE))
		return ("Negative number");
	else if (has_error(error_code, ERR_INVALID_CHAR))
		return ("Invalid char");
	else if (has_error(error_code, ERR_NBR_VALUES))
		return ("Not the right number of values");
	else if (has_error(error_code, ERR_NBR_ELEMENTS))
		return ("Not the right number of elements");
	return ("No details");
}

void	print_parsing_error(t_error_log error_log)
{
	char	*element;
	char	*value;

	element = get_element(error_log.code_error);
	value = get_value(error_log.code_error);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Parsing Error:\n", 2);
	ft_putstr_fd("\t# line number: ", 2);
	ft_putnbr_fd(error_log.line_nbr, 2);
	ft_putstr_fd(".\n", 2);
	ft_putstr_fd("\tElement -> ", 2);
	ft_putstr_fd(element, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(error_log.element, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(".\n", 2);
	ft_putstr_fd("\tValue -> ", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd(".\n", 2);
	ft_putstr_fd("\tError details -> ", 2);
	ft_putstr_fd(get_general_error(error_log.code_error), 2);
	ft_putstr_fd(".\n", 2);
}
