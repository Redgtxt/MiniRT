/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/09/18 16:37:42 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	error_code(t_error *error_code, int flag_one, int flag_two)
{
	if (flag_one)
		*error_code |= flag_one;
	if (flag_two)
		*error_code |= flag_two;
	return ;
}

int	has_error(t_error error_code, int flag)
{
	return ((error_code & flag) != 0);
}
