/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/06/18 15:58:00 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//	Checks if the file as the right amount of elements for the program
static bool	parse_number_elements(t_data data, t_error_log *error_log)
{
	if (data.amb_light_count != 1)
		error_code(&error_log->code_error, ERR_ELEMENT_A, ERR_NBR_ELEMENTS);
	else if (data.camera_count != 1)
		error_code(&error_log->code_error, ERR_ELEMENT_C, ERR_NBR_ELEMENTS);
	else if (data.light_count != 1)
		error_code(&error_log->code_error, ERR_ELEMENT_L, ERR_NBR_ELEMENTS);
	// else if (data.sphere_count == 0)
	// 	error_code(&error_log->code_error, ERR_ELEMENT_SP, ERR_NBR_ELEMENTS);
	// else if (data.plane_count == 0)
	// 	error_code(&error_log->code_error, ERR_ELEMENT_PL, ERR_NBR_ELEMENTS);
	// else if (data.cylinder_count == 0)
	// 	error_code(&error_log->code_error, ERR_ELEMENT_CY, ERR_NBR_ELEMENTS);
	if (error_log->code_error != 0)
	{
		error_log->line_nbr = 0;
		return (false);
	}
	return (true);
}

//	Filters elements by identifier and takes it into the right parsing mode
static bool	parse_element_type(t_control_panel *control_panel, char **element_info)
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
		return (false);
	return (true);
}

//	Cleans new_line from Get_next_line.c
//	Splits string by spaces into double array
static char	**get_element_info(char *new_line)
{
	char	*element_str;
	char	**element_info;

	element_str = NULL;
	element_info = NULL;
	element_str = ft_strtrim(new_line, "\n"); // removes '\n' from the end of the line
	if (!element_str)
		return (NULL);
	element_info = split_spaces(element_str); // separates the new line into a double array
	if (!element_info)
		return (free(element_str), NULL);
	free(element_str);
	return (element_info);
}

//	Gets the new_line in a double array and parses it into the struct depending on the type
static bool	parse_new_line(t_control_panel *control_panel, char *new_line)
{
	char	**element_info;

	element_info = NULL;
	element_info = get_element_info(new_line); // Returns the elements separated in a double array
	if (!element_info)
		return (false);
	if (parse_element_type(control_panel, element_info) == false) // Parse the element_info(double array) depending on the type
		return (ft_free_double_array(element_info), false);
	ft_free_double_array(element_info);
	return (true);
}

//	Main parsing
// 		- opens file;
// 		- gets the full new_line;
// 		- removes the '\n' from the end of the line;
// 		- separates the values by ' ' into double array;
// 		- checks the type of element by the first value ([0][0]) and parses it;
// 		- checks if the number of elements its correct for the program;
//
bool	parsing(t_control_panel *control_panel, char *file_name)
{
	int		fd;
	char	*new_line;

	new_line = NULL;
	fd = open(file_name, O_RDONLY); // Open file
	if (fd == -1)
		return (false);
	while (1)
	{
		new_line = get_next_line(fd); // Read full line
		if (!new_line)
			break ;
		control_panel->error_log.line_nbr++; // Adds one to the nbr of lines
		if (new_line[0] != '\n') //	If line read doesnt have just a \n
		{
			if (!parse_new_line(control_panel, new_line))	//	Parse the new_line -> separates in double array and parses info into struct
				return (close(fd), free(new_line), false);
		}
		free(new_line);
	}
	if (!parse_number_elements(control_panel->data, &control_panel->error_log))
		return (close(fd), false);
	close(fd);
	if (control_panel->data.sphere_count)
		linked_list_to_sphere_array(&control_panel->sphere, control_panel->data.sphere_count); // create function to convert all objects
	if (control_panel->data.plane_count)
		linked_list_to_plane_array(&control_panel->plane, control_panel->data.plane_count);
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
