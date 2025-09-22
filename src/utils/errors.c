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

static void	print_element_error(t_error error_code, char *element)
{
	if (has_error(error_code, INV_ELEMENT))
	{
		ft_putstr_fd("Invalid type ", 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd("'", 2);
	}
	else if (has_error(error_code, ERR_ELEMENT_A))
		ft_putstr_fd("Ambient_light 'A'", 2);
	else if (has_error(error_code, ERR_ELEMENT_C))
		ft_putstr_fd("Camera 'C'", 2);
	else if (has_error(error_code, ERR_ELEMENT_L))
		ft_putstr_fd("Light 'L'", 2);
	else if (has_error(error_code, ERR_ELEMENT_SP))
		ft_putstr_fd("Sphere 'sp'", 2);
	else if (has_error(error_code, ERR_ELEMENT_PL))
		ft_putstr_fd("Plane 'pl'", 2);
	else if (has_error(error_code, ERR_ELEMENT_CY))
		ft_putstr_fd("Cylinder 'cy'", 2);
}

static void	print_value_error(t_error error_code)
{
	if (has_error(error_code, ERR_COORD))
		ft_putstr_fd("Coordenates", 2);
	else if (has_error(error_code, ERR_VECTOR))
		ft_putstr_fd("Vector", 2);
	else if (has_error(error_code, ERR_RGB))
		ft_putstr_fd("RGB", 2);
	else if (has_error(error_code, ERR_FOV))
		ft_putstr_fd("FOV", 2);
	else if (has_error(error_code, ERR_LIGHT_FORCE))
		ft_putstr_fd("Light force", 2);
	else if (has_error(error_code, ERR_BRIGHTNESS))
		ft_putstr_fd("Brightness", 2);
	else if (has_error(error_code, ERR_D))
		ft_putstr_fd("Diameter", 2);
	else if (has_error(error_code, ERR_HEIGHT))
		ft_putstr_fd("Height", 2);
	else if (has_error(error_code, ERR_MATERIAL))
		ft_putstr_fd("Material", 2);
	else
		ft_putstr_fd("No info", 2);
}

static void	print_general_error(t_error_log *error_log)
{
	if (has_error(error_log->code_error, ERR_MALLOC))
		ft_putstr_fd("Memory allocation", 2);
	else if (has_error(error_log->code_error, ERR_OVERFLOW))
		ft_putstr_fd("Overflow", 2);
	else if (has_error(error_log->code_error, ERR_RANGE))
	{
		ft_putstr_fd("Out of range -", 2);
		if (has_error(error_log->code_error, ERR_RGB))
			ft_putstr_fd(" (0-255)", 2);
		else if (has_error(error_log->code_error, ERR_VECTOR))
			ft_putstr_fd(" (-1.0 to 1.0)", 2);
		else if (has_error(error_log->code_error, ERR_FOV))
			ft_putstr_fd(" (0-180)", 2);
		else if (has_error(error_log->code_error, ERR_LIGHT_FORCE) || has_error(error_log->code_error, ERR_BRIGHTNESS))
			ft_putstr_fd(" (0.0-1.0)", 2);
		else if (has_error(error_log->code_error, ERR_D) || has_error(error_log->code_error, ERR_HEIGHT))
			ft_putstr_fd(" (>0)", 2);

	}
	else if (has_error(error_log->code_error, ERR_INVALID_VALUE))
		ft_putstr_fd("Invalid value format", 2);
	else if (has_error(error_log->code_error, ERR_INVALID_CHAR))
	{
		ft_putstr_fd("Invalid character - '", 2);
		ft_putchar_fd(error_log->error_char_detail, 2);
		ft_putchar_fd('\'', 2);
	}
	else if (has_error(error_log->code_error, ERR_NBR_VALUES))
		ft_putstr_fd("Not the right number of values", 2);
	else if (has_error(error_log->code_error, ERR_NO_ELEMENT))
	{
		if (has_error(error_log->code_error, ERR_ELEMENT_A) || has_error(error_log->code_error, ERR_ELEMENT_C)
				|| has_error(error_log->code_error, ERR_ELEMENT_L))
			ft_putstr_fd("Element not found - Needs one", 2);
	}
	else if (has_error(error_log->code_error, ERR_NBR_ELEMENTS))
	{
		if (has_error(error_log->code_error, ERR_ELEMENT_A) || has_error(error_log->code_error, ERR_ELEMENT_C))
			ft_putstr_fd("Not the right number of elements - only one is allowed", 2);
	}
	else if (has_error(error_log->code_error, ERR_MATERIAL))
	{
		ft_putstr_fd("Unkown material - '", 2);
		ft_putstr_fd(error_log->error_str_detail, 2);
		ft_putchar_fd('\'', 2);
	}
	else
		ft_putstr_fd("No details", 2);
}

void	print_parsing_error(t_error_log *error_log)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Parsing Error:\n", 2);
	ft_putstr_fd("\t# line number: ", 2);
	ft_putnbr_fd(error_log->line_nbr, 2);
	ft_putstr_fd(".\n", 2);
	ft_putstr_fd("\tElement -> ", 2);
	print_element_error(error_log->code_error, error_log->element);
	ft_putstr_fd(".\n", 2);
	ft_putstr_fd("\tValue -> ", 2);
	print_value_error(error_log->code_error);
	ft_putstr_fd(".\n", 2);
	ft_putstr_fd("\tError details -> ", 2);
	print_general_error(error_log);
	ft_putstr_fd(".\n", 2);
}
