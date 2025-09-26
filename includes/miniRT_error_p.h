/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_error_p.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/09/18 16:37:42 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_ERROR_P_H
# define MINIRT_ERROR_P_H
# include "../Library/libft/libft.h"
# include <stdint.h>
# include <stdio.h>

#define OVERFLOW_MAX_LIMIT 2147483647
#define OVERFLOW_MIN_LIMIT -2147483648

typedef uint32_t t_error;

// ───── Element Flags (Bits 0–7) ─────
typedef enum u_element_flags
{
	INV_ELEM = (1 << 0),
	ERR_ELEM_A = (1 << 1),
	ERR_ELEM_C = (1 << 2),
	ERR_ELEM_L = (1 << 3),
	ERR_ELEM_SP = (1 << 4),
	ERR_ELEM_PL = (1 << 5),
	ERR_ELEM_CY = (1 << 6),
	ERR_ELEM_CN = (1 << 7)
}				t_element_flags;

// ───── Values Flags (Bits 8–15) ─────
typedef enum u_values_flags
{
	ERR_COORD = (1 << 8),
	ERR_VECTOR = (1 << 9),
	ERR_RGB = (1 << 10),
	ERR_FOV = (1 << 11),
	ERR_BRIGHT = (1 << 12),
	ERR_D = (1 << 13),
	ERR_HEIGHT = (1 << 14),
	ERR_MATERIAL = (1 << 15)
}				t_values_flags;

// ───── General Parsing Errors (Bits 16–23) ─────
typedef enum u_general_flags
{
	ERR_MALLOC = (1 << 16),
	ERR_OVERFLOW = (1 << 17),
	ERR_RANGE = (1 << 18),
	ERR_INV_CHAR = (1 << 19),
	ERR_INV_VALUE = (1 << 20),
	ERR_NO_ELEMENT = (1 << 21),
	ERR_NBR_ELEM = (1 << 22),
	ERR_NBR_VAL = (1 << 23)
}				t_general_flags;

// ───── General Parsing Errors II (Bits 24–32) ─────
typedef enum u_sec_general_flags
{
	ERR_FILE = (1 << 24),
	ERR_FILE_NAME = (1 << 25),
	ERR_FILE_OPEN = (1 << 26),
	ERR_IS_DIR = (1 << 27),
	ERR_INV_MATERIAL = (1 << 28)
}				t_sec_general_flags;

typedef struct s_error_log
{
	t_error		code_error;
	char		*element;
	char		error_char_detail;
	char		*error_str_detail;
	size_t		line_nbr;
}				t_error_log;

void	error_code(t_error *error_code, int flag_one, int flag_two);
int		has_error(t_error error_code, int flag);
void	print_range_error(t_error_log *error_log);
void	print_file_error(t_error_log *error_log);
void	print_nbr_element_error(t_error_log *error_log);
void	print_inv_char_error(t_error_log *error_log);
void	print_inv_material_error(t_error_log *error_log);
void	print_element_error(t_error error_code, char *element);
void	print_value_error(t_error error_code);
void	print_general_error(t_error_log *error_log);
void	print_parsing_error(t_error_log *error_log);

#endif
