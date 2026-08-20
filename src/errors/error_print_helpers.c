/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print_helpers.c                         	    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/09/18 16:37:42 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	print_range_error(t_error_log *error_log)
{
	ft_putstr_fd("Out of range -", 2);
	if (has_error(error_log->code_error, ERR_RGB))
		ft_putstr_fd(" (0-255)", 2);
	else if (has_error(error_log->code_error, ERR_VECTOR))
		ft_putstr_fd(" (-1.0 to 1.0)", 2);
	else if (has_error(error_log->code_error, ERR_FOV))
		ft_putstr_fd(" (0-180)", 2);
	else if (has_error(error_log->code_error, ERR_BRIGHT))
		ft_putstr_fd(" (0.0-1.0)", 2);
	else if (has_error(error_log->code_error, ERR_D)
		|| has_error(error_log->code_error, ERR_HEIGHT))
		ft_putstr_fd(" (>0)", 2);
}

void	print_file_error(t_error_log *error_log)
{
	ft_putstr_fd("File error - ", 2);
	if (has_error(error_log->code_error, ERR_FILE_NAME))
		ft_putstr_fd("Invalid file name (should end with .rt)", 2);
	else if (has_error(error_log->code_error, ERR_FILE_OPEN))
		ft_putstr_fd("Could not open file", 2);
	else if (has_error(error_log->code_error, ERR_IS_DIR))
		ft_putstr_fd("Is a directory", 2);
}

void	print_nbr_element_error(t_error_log *error_log)
{
	if (has_error(error_log->code_error, ERR_ELEM_A)
		|| has_error(error_log->code_error, ERR_ELEM_C)
		|| has_error(error_log->code_error, ERR_ELEM_L))
		ft_putstr_fd("Element not found - Needs one", 2);
	else if (has_error(error_log->code_error, ERR_ELEM_A)
		|| has_error(error_log->code_error, ERR_ELEM_C))
		ft_putstr_fd("Not the right number of elements - only one is allowed",
			2);
}

void	print_inv_char_error(t_error_log *error_log)
{
	ft_putstr_fd("Invalid character - '", 2);
	ft_putchar_fd(error_log->error_char_detail, 2);
	ft_putchar_fd('\'', 2);
}

void	print_inv_material_error(t_error_log *error_log)
{
	ft_putstr_fd("Unkown material - '", 2);
	ft_putstr_fd(error_log->error_str_detail, 2);
	ft_putchar_fd('\'', 2);
}
