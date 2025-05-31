/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/05/27 16:00:08 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <unistd.h>

bool	get_coord(t_coord *coord, char *info)
{
	char	**array;
	size_t	i;

	array = NULL;
	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-' && info[i] != ',')
			return (false);
		i++;
	}
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (ft_free_double_array(array), false);
	if (!ft_atofd(array[0], &coord->x, 'd') || !ft_atofd(array[1], &coord->y, 'd')
			|| !ft_atofd(array[2], &coord->z, 'd'))
		return (ft_free_double_array(array), false);
	ft_free_double_array(array);
	return (true);
}

//	NOTE: Melhorar precisao > 1.0
bool	get_vector(t_vector *vector, char *info)
{
	char	**array;
	size_t	i;

	array = NULL;
	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-' && info[i] != ',')
			return (false);
		i++;
	}
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (ft_free_double_array(array), false);
	if (!ft_atofd(array[0], &vector->x, 'f') || !ft_atofd(array[1], &vector->y, 'f')
			|| !ft_atofd(array[2], &vector->z, 'f'))
		return (ft_free_double_array(array), false);
	ft_free_double_array(array);
	if (vector->x > 1.0 || vector->y > 1.0 || vector->z > 1.0
		|| vector->x < -1.0 || vector->y < -1.0 || vector->z < -1.0) //	Melhorar precisao
		return (false);
	return (true);
}

//	RGB //
bool	parse_rgb_chars(char *info)
{
	size_t	nbr_len;

	nbr_len = 0;
	while(*info)
	{
		if (ft_isdigit(*info))
			nbr_len++;
		else if (*info == ',')
			nbr_len = 0;
		else
			return (false);
		if (nbr_len > 3)
			return (false);
		info++;
	}
	return (true);
}

bool	get_rgb(t_rgb *rgb, char *info)
{
	char	**array;

	array = NULL;
	if (parse_rgb_chars(info) == false)
		return (false);
	array = ft_split(info, ',');
	if (!array)
		return (false);
	if (double_array_len(array) != 3)
		return (ft_free_double_array(array), false);
	if (!ft_atoc(array[0], &rgb->r) || !ft_atoc(array[1], &rgb->g)
			|| !ft_atoc(array[2], &rgb->b))
		return (ft_free_double_array(array), false);
	ft_free_double_array(array);
	return (true);
}
//	---	//

bool	get_fov(mini_int *fov, char *info)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]))
			return (false);
		i++;
	}
	if (!ft_atoc(info, fov) || *fov > 180)
		return (false);
	return (true);
}

bool	get_light_force(float *light_force, char *info)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-')
			return (false);
		i++;
	}
	if (!ft_atofd(info, light_force, 'f'))
		return (false);
	return (true);
}

//	NOTE: Melhorar precisao > 1.0
bool	get_brightness(float *brightness, char *info)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.')
			return (false);
		i++;
	}
	if (!ft_atofd(info, brightness, 'f'))
		return (false);
	if (*brightness > 1.0) //	Melhorar precisao
		return (false);
	return (true);
}

bool	get_d(double *d, char *info)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.')
			return (false);
		i++;
	}
	if (!ft_atofd(info, d, 'd'))
		return (false);
	return (true);
}

bool	get_height(double *height, char *info)
{
	size_t	i;

	i = 0;
	while(info[i])
	{
		if (!ft_isdigit(info[i]) && info[i] != '.' && info[i] != '-')
			return (false);
		i++;
	}
	if (!ft_atofd(info, height, 'd'))
		return (false);
	return (true);
}

//	Parses the ambient_light input
bool	parse_amb_light(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	if (!get_light_force(&control_panel->amb_light.light_force, element_info[1]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_A, ERR_LIGHT_FORCE), false);
	if (!get_rgb(&control_panel->amb_light.rgb, element_info[2]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_A, ERR_RGB), false);
	control_panel->data.amb_light++;
	return (true);
}

//	Parses the camera input
bool	parse_camera(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	if (!get_coord(&control_panel->camera.coord, element_info[1]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_C, ERR_COORD), false);
	if (!get_vector(&control_panel->camera.vector, element_info[2]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_C, ERR_VECTOR), false);
	if (!get_fov(&control_panel->camera.fov, element_info[3]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_C, ERR_FOV), false);
	control_panel->data.camera++;
	return (true);
}

//	Parses the light input
bool	parse_light(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	if (!get_coord(&control_panel->light.coord, element_info[1]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_L, ERR_COORD), false);
	if (!get_brightness(&control_panel->light.brightness, element_info[2]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_L, ERR_BRIGHTNESS), false);
	if (!get_rgb(&control_panel->light.rgb, element_info[3]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_L, ERR_RGB), false);
	control_panel->data.light++;
	return (true);
}

//	Parses the sphere input
bool	parse_sphere(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	control_panel->sphere = ft_calloc(1, sizeof(t_sphere));
	if (!control_panel->sphere)
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_MALLOC), false);
	if (!get_coord(&control_panel->sphere->coord, element_info[1]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_COORD), false);
	if (!get_d(&control_panel->sphere->d, element_info[2]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_D), false);
	//	RADIUS
	if (!get_rgb(&control_panel->sphere->rgb, element_info[3]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_RGB), false);
	control_panel->sphere->next = NULL;
	control_panel->sphere->prev = NULL;
	control_panel->data.sphere++;
	return (true);
}

//	Parses the plane input
bool	parse_plane(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	control_panel->plane = ft_calloc(1, sizeof(t_plane));
	if (!control_panel->plane)
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_MALLOC), false);
	if (!get_coord(&control_panel->plane->coord, element_info[1]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_COORD), false);
	if (!get_vector(&control_panel->plane->vector, element_info[2]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_VECTOR), false);
	if (!get_rgb(&control_panel->plane->rgb, element_info[3]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_RGB), false);
	control_panel->plane->next = NULL;
	control_panel->plane->prev = NULL;
	control_panel->data.plane++;
	return (true);
}

//	Parses the cylinder input
bool	parse_cylinder(t_control_panel *control_panel, char **element_info, t_error_log *error_log)
{
	control_panel->cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!control_panel->cylinder)
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_MALLOC), false);
	if (!get_coord(&control_panel->cylinder->coord, element_info[1]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_COORD), false);
	if (!get_vector(&control_panel->cylinder->vector, element_info[2]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_VECTOR), false);
	if (!get_d(&control_panel->cylinder->d, element_info[3]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_D), false);
	//	Radius
	if (!get_height(&control_panel->cylinder->height, element_info[4]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_HEIGHT), false);
	if (!get_rgb(&control_panel->cylinder->rgb, element_info[5]))
		return (error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_RGB), false);
	control_panel->cylinder->next = NULL;
	control_panel->cylinder->prev = NULL;
	control_panel->data.cylinder++;
	return (true);
}

bool	parse_number_elements(t_data data, t_error_log *error_log)
{
	if (data.amb_light != 1)
		error_code(&error_log->code_error, ERR_ELEMENT_A, ERR_NBR_ELEMENTS);
	else if (data.camera != 1)
		error_code(&error_log->code_error, ERR_ELEMENT_C, ERR_NBR_ELEMENTS);
	else if (data.light != 1)
		error_code(&error_log->code_error, ERR_ELEMENT_L, ERR_NBR_ELEMENTS);
	else if (data.sphere == 0)
		error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_NBR_ELEMENTS);
	else if (data.plane == 0)
		error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_NBR_ELEMENTS);
	else if (data.cylinder == 0)
		error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_NBR_ELEMENTS);
	if (error_log->code_error != 0)
	{
		error_log->line_nbr = 0;
		return (false);
	}
	return (true);
}

//	Filters elements by identifier and takes it into the right parsing mode
bool	parse_element_type(t_control_panel *control_panel, char **element_info)
{
	control_panel->error_log.element = element_info[0];
	if (ft_strncmp(element_info[0], "A", 1) == 0)
		parse_amb_light(control_panel, element_info, &control_panel->error_log);
	else if (ft_strncmp(element_info[0], "C", 1) == 0)
		parse_camera(control_panel, element_info, &control_panel->error_log);
	else if (ft_strncmp(element_info[0], "L", 1) == 0)
		parse_light(control_panel, element_info, &control_panel->error_log);
	else if (ft_strncmp(element_info[0], "sp", 2) == 0)
		parse_sphere(control_panel, element_info, &control_panel->error_log);
	else if (ft_strncmp(element_info[0], "pl", 2) == 0)
		parse_plane(control_panel, element_info, &control_panel->error_log);
	else if (ft_strncmp(element_info[0], "cy", 2) == 0)
		parse_cylinder(control_panel, element_info, &control_panel->error_log);
	else if (ft_strncmp(element_info[0], "#", 1) == 0) // REMOVE WHEN DELIVERING {?}
		return (true);
	else
		error_code(&control_panel->error_log.code_error, INV_ELEMENT, 0);
	if (control_panel->error_log.code_error != 0)
		return (print_parsing_error(control_panel->error_log), false);
	return (true);
}

//	Cleans new_line from Get_next_line.c
//	Splits string by spaces into double array
char	**get_element_info(char *new_line)
{
	char	*element_str;
	char	**element_info;

	element_str = NULL;
	element_info = NULL;
	element_str = ft_strtrim(new_line, "\n");
	if (!element_str)
		return (NULL);
	element_info = split_spaces(element_str);
	if (!element_info)
		return (free(element_str), NULL);
	free(element_str);
	return (element_info);
}

bool	parsing(t_control_panel *control_panel, char *file_name)
{
	int		fd;
	char	*new_line;
	char	**element_info;

	new_line = NULL;
	element_info = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (false);
	while (1)
	{
		new_line = get_next_line(fd);
		if (!new_line)
			break ;
		control_panel->error_log.line_nbr++;
		if (new_line[0] != '\n')
		{
			element_info = get_element_info(new_line);
			if (!element_info)
				return (close(fd), free(new_line), false);
			if (element_info[0][0] == '\0'
				|| parse_element_type(control_panel, element_info) == false)
				return (close(fd), free(new_line), ft_free_double_array(element_info), false);
			ft_free_double_array(element_info);
		}
		free(new_line);
	}
	if (!parse_number_elements(control_panel->data, &control_panel->error_log))
		return (close(fd), print_parsing_error(control_panel->error_log), false);
	close(fd);
	return (true);
}



/*
- Each type of element can be separated by one or more line breaks.
- Each type of information from an element can be separated by one or morespaces.
- Each type of element can be set in any order in the file.
- Elements defined by a capital letter can only be declared once in the scene.

*.rt format:

Ambient light = A 0.2 255,255,255

        identifier - A
        ambient lighting ratio in the range [0.0,1.0]: 0.2
        R, G, B colors in the range [0-255]: 255, 255, 255

Camera = C -50.0,0,20 0,0,1 70

        identifier - C
        x, y, z coordinates of the viewpoint: -50.0,0,20
        3D normalized orientation vector, in the range [-1,1] for each x, y, z axis: 0.0,0.0,1.0
        FOV: Horizontal field of view in degrees in the range [0,180]: 70

Light = L -40.0,50.0,0.0 0.6 10,0,255

        identifier: L
        x, y, z coordinates of the light point: -40.0,50.0,0.0
        the light brightness ratio in the range [0.0,1.0]: 0.6
        (unused in mandatory part) R, G, B colors in the range [0-255]: 10, 0,255

Sphere = sp 0.0,0.0,20.6 12.6 10,0,255

        identifier: sp
        x, y, z coordinates of the sphere center: 0.0,0.0,20.6
        the sphere diameter: 12.6
        R,G,B colors in the range [0-255]: 10, 0, 255

Plane = pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225

        identifier: pl
        x, y, z coordinates of a point in the plane: 0.0,0.0,-10.0
        3D normalized normal vector, in the range [-1,1] for each x, y, z axis:0.0,1.0,0.0
        R,G,B colors in the range [0-255]: 0,0,225

Cylinder = cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255

        identifier: cy
        x, y, z coordinates of the center of the cylinder: 50.0,0.0,20.6
        3D normalized vector of axis of cylinder, in the range [-1,1] for each x, y,z axis: 0.0,0.0,1.0
        the cylinder diameter: 14.2
        the cylinder height: 21.42
        R, G, B colors in the range [0,255]: 10, 0, 255


 - If any misconfiguration of any kind is encountered in the file, the program must exit
 properly and return "Error\n" followed by an explicit error message of your choice.

*/
