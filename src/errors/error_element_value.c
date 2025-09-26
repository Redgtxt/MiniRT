/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_element_value.c                         	    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/09/18 16:37:42 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	print_element_error(t_error error_code, char *element)
{
	if (has_error(error_code, INV_ELEM))
	{
		ft_putstr_fd("Invalid type ", 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd(element, 2);
		ft_putstr_fd("'", 2);
	}
	else if (has_error(error_code, ERR_ELEM_A))
		ft_putstr_fd("Ambient_light 'A'", 2);
	else if (has_error(error_code, ERR_ELEM_C))
		ft_putstr_fd("Camera 'C'", 2);
	else if (has_error(error_code, ERR_ELEM_L))
		ft_putstr_fd("Light 'L'", 2);
	else if (has_error(error_code, ERR_ELEM_SP))
		ft_putstr_fd("Sphere 'sp'", 2);
	else if (has_error(error_code, ERR_ELEM_PL))
		ft_putstr_fd("Plane 'pl'", 2);
	else if (has_error(error_code, ERR_ELEM_CY))
		ft_putstr_fd("Cylinder 'cy'", 2);
	else if (has_error(error_code, ERR_ELEM_CN))
		ft_putstr_fd("Cone 'cn'", 2);
	else
		ft_putstr_fd("No info", 2);
}

void	print_value_error(t_error error_code)
{
	if (has_error(error_code, ERR_COORD))
		ft_putstr_fd("Coordenates", 2);
	else if (has_error(error_code, ERR_VECTOR))
		ft_putstr_fd("Vector", 2);
	else if (has_error(error_code, ERR_RGB))
		ft_putstr_fd("RGB", 2);
	else if (has_error(error_code, ERR_FOV))
		ft_putstr_fd("FOV", 2);
	else if (has_error(error_code, ERR_BRIGHT))
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
