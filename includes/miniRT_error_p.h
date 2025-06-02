/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/05/27 16:11:15 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_ERROR_P_H
# define MINIRT_ERROR_P_H
# include "../Library/libft/libft.h"
# include <stdint.h>
# include <stdio.h>

typedef uint32_t t_error;

// ───── Element Flags (Bits 0–7) ─────
typedef enum u_element_flags
{
	INV_ELEMENT = (1 << 0),
	ERR_ELEMENT_A = (1 << 1),
	ERR_ELEMENT_C = (1 << 2),
	ERR_ELEMENT_L = (1 << 3),
	ERR_ELEMENT_SP = (1 << 4),
	ERR_ELEMENT_PL = (1 << 5),
	ERR_ELEMENT_CY = (1 << 6)
}				t_element_flags;

// ───── Values Flags (Bits 8–15) ─────
typedef enum u_values_flags
{
	ERR_COORD = (1 << 8),
	ERR_VECTOR = (1 << 9),
	ERR_RGB = (1 << 10),
	ERR_FOV = (1 << 11),
	ERR_LIGHT_FORCE = (1 << 12),
	ERR_BRIGHTNESS = (1 << 13),
	ERR_D = (1 << 14),
	ERR_HEIGHT = (1 << 15)
}				t_values_flags;

// ───── General Parsing Errors (Bits 16–23) ─────
typedef enum u_general_flags
{
	ERR_MALLOC = (1 << 16),
	ERR_OVERFLOW = (1 << 17),
	ERR_NEGATIVE = (1 << 18),
	ERR_INVALID_CHAR = (1 << 19),
	ERR_NBR_ELEMENTS = (1 << 20),
	ERR_NBR_VALUES = (1 << 21)
}				t_general_flags;

typedef struct s_error_log
{
	t_error		code_error;
	char		*element;
	char		error_char_detail;
	size_t		line_nbr;
}				t_error_log;

void	error_code(t_error *error_code, int flag_one, int flag_two);
void	print_parsing_error(t_error_log error_log);

#endif
