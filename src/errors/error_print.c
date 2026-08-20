/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/09/18 16:37:42 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	print_general_error(t_error_log *error_log)
{
	if (has_error(error_log->code_error, ERR_MALLOC))
		ft_putstr_fd("Memory allocation", 2);
	else if (has_error(error_log->code_error, ERR_OVERFLOW))
		ft_putstr_fd("Overflow", 2);
	else if (has_error(error_log->code_error, ERR_RANGE))
		print_range_error(error_log);
	else if (has_error(error_log->code_error, ERR_INV_VALUE))
		ft_putstr_fd("Invalid value format", 2);
	else if (has_error(error_log->code_error, ERR_INV_CHAR))
		print_inv_char_error(error_log);
	else if (has_error(error_log->code_error, ERR_NBR_VAL))
		ft_putstr_fd("Not the right number of values", 2);
	else if (has_error(error_log->code_error, ERR_NO_ELEMENT))
		print_nbr_element_error(error_log);
	else if (has_error(error_log->code_error, ERR_NBR_ELEM))
		print_nbr_element_error(error_log);
	else if (has_error(error_log->code_error, ERR_INV_MATERIAL))
		print_inv_material_error(error_log);
	else if (has_error(error_log->code_error, ERR_FILE))
		print_file_error(error_log);
	else
		ft_putstr_fd("No details", 2);
}

void	print_parsing_error(t_error_log *error_log)
{
	ft_putstr_fd(REDHB "Error" RESET "\n", 2);
	ft_putstr_fd(BRED "\n* ---------------------- *\n" RESET, 2);
	if (has_error(error_log->code_error, ERR_FILE))
		print_general_error(error_log);
	else
	{
		ft_putstr_fd(BRED "Parsing file error:" RESET "\n", 2);
		ft_putstr_fd("\t" BHYEL "# line number: " RESET, 2);
		ft_putnbr_fd(error_log->line_nbr, 2);
		ft_putstr_fd(".\n", 2);
		ft_putstr_fd("\t" BHYEL "Element -> " RESET, 2);
		print_element_error(error_log->code_error, error_log->element);
		ft_putstr_fd(".\n", 2);
		ft_putstr_fd("\t" BHYEL "Value -> " RESET, 2);
		print_value_error(error_log->code_error);
		ft_putstr_fd(".\n", 2);
		ft_putstr_fd("\t" BHYEL "Error details -> " RESET, 2);
		print_general_error(error_log);
		ft_putchar_fd('.', 2);
	}
	ft_putstr_fd(BRED "\n* ---------------------- *\n" RESET, 2);
	ft_putchar_fd('\n', 2);
}
