/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../core/types.h"
# include "../math/vec3.h"
# include "errors.h"

/* Main parsing function */
bool	parsing(t_control_panel *control_panel, char *file_name);

/* Element parsing functions */
bool	parse_amb_light(t_control_panel *control_panel, char **element_info,
			t_error_log *error_log);
bool	parse_camera(t_control_panel *control_panel, char **element_info,
			t_error_log *error_log);
bool	parse_light(t_control_panel *control_panel, char **element_info,
			t_error_log *error_log);

/* Object parsing functions */
bool	parse_sphere(t_control_panel *control_panel, char **element_info,
			t_error_log *error_log);
bool	parse_plane(t_control_panel *control_panel, char **element_info,
			t_error_log *error_log);
bool	parse_cylinder(t_control_panel *control_panel, char **element_info,
			t_error_log *error_log);
bool	parse_cone(t_control_panel *control_panel, char **element_info,
			t_error_log *error_log);

/* Value parsing functions */
bool	get_coord(vec3 *coord, char *info, t_error_log *error_log);
bool	get_vector(vec3 *vector, char *info, t_error_log *error_log);
bool	get_rgb(double rgb[3], char *info, t_error_log *error_log);
bool	get_material(t_material *object_material, double rgb[3], char *info,
			t_error_log *error_log);
bool	get_fov(mini_int *fov, char *info, t_error_log *error_log);
bool	get_light_force(double *light_force, char *info,
			t_error_log *error_log);
bool	get_brightness(double *brightness, char *info, t_error_log *error_log);
bool	get_size(double *d, char *info, t_error_log *error_log);

/* Parsing utility functions */
bool	parse_numbers(char *info, size_t *nbr_dot, t_error_log *error_log,
			bool negative);
bool	parse_three_octet_values(char *info, t_error_log *error_log);
bool	parse_rgb_chars(char *info, t_error_log *error_log);
bool	parse_number_elements(t_data data, t_error_log *error_log);

/* Utility functions */
size_t	double_array_len(char **array);
bool	ft_atoc(const char *str, mini_int *dest);
bool	ft_atod(const char *str, double *dest);
char	**split_spaces(char const *s);

#endif