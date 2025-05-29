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
#include <stdbool.h>
#include <unistd.h>

// bool	get_coord(coord **coord, char *info)
// {
// 	(void)coord;
// 	(void)info;
// 	return (true);
// }

// bool	get_vector(vector **vector, char *info)
// {
// 	(void)vector;
// 	(void)info;
// 	return (true);
// }

bool	get_coord(t_coord *coord, char *info)
{
	(void)coord;
	(void)info;
	return (true);
}

bool	get_vector(t_vector *vector, char *info)
{
	(void)vector;
	(void)info;
	return (true);
}

//	RGB //
bool	parse_rgb_chars(char *info)
{
	size_t	nbr_len;

	nbr_len = 0;
	while(*info)
	{
		if (ft_isalnum(*info))
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
	(void)fov;
	(void)info;
	return (true);
}

bool	get_light_force(float *light_force, char *info)
{
	(void)light_force;
	(void)info;
	return (true);
}

bool	get_brightness(float *brightness, char *info)
{
	(void)brightness;
	(void)info;
	return (true);
}

bool	get_d(double *d, char *info)
{
	(void)d;
	(void)info;
	return (true);
}

bool	get_radius(double *radius, char *info)
{
	(void)radius;
	(void)info;
	return (true);
}

bool	get_height(double *height, char *info)
{
	(void)height;
	(void)info;
	return (true);
}

//	Parses the ambient_light input
void	parse_amb_light(t_control_panel *control_panel, char **element_info, bool *error)
{
	get_light_force(&control_panel->amb_light.light_force, element_info[1]);
	if (!get_rgb(&control_panel->amb_light.rgb, element_info[2]))
}

//	Parses the camera input
bool	parse_camera(t_control_panel *control_panel, char **element_info, bool *error)
{
	// get_coord(&control_panel->camera.coord, element_info[1]);
	// get_vector(&control_panel->camera.coord, element_info[2]);
	get_coord(&control_panel->camera.coord, element_info[1]);
	get_vector(&control_panel->camera.vector, element_info[2]);
	get_fov(&control_panel->camera.fov, element_info[3]);
	return (true);
}

//	Parses the light input
bool	parse_light(t_control_panel *control_panel, char **element_info, bool *error)
{
	// get_coord(control_panel, element_info[1]);
	get_coord(&control_panel->light.coord, element_info[1]);
	get_brightness(&control_panel->light.brightness, element_info[2]);
	if (!get_rgb(&control_panel->light.rgb, element_info[3]))
		return (false);
	return (true);
}

//	Parses the sphere input
bool	parse_sphere(t_control_panel *control_panel, char **element_info, bool *error)
{
	// get_coord(control_panel, element_info[1]);
	get_coord(&control_panel->sphere->coord, element_info[1]);
	get_d(&control_panel->sphere->d, element_info[2]);
	get_radius(&control_panel->sphere->radius, element_info[3]);
	if (!get_rgb(&control_panel->sphere->rgb, element_info[4]))
		return (false);
	control_panel->sphere->next = NULL;
	control_panel->sphere->prev = NULL;
	return (true);
}

//	Parses the plane input
bool	parse_plane(t_control_panel *control_panel, char **element_info, bool *error)
{
	// get_coord(control_panel, element_info[1]);
	// get_vector(control_panel, element_info[2]);
	get_coord(&control_panel->plane->coord, element_info[1]);
	get_vector(&control_panel->plane->vector, element_info[2]);
	if (!get_rgb(&control_panel->plane->rgb, element_info[3]))
		return (false);
	control_panel->plane->next = NULL;
	control_panel->plane->prev = NULL;
	return (true);
}

//	Parses the cylinder input
bool	parse_cylinder(t_control_panel *control_panel, char **element_info, bool *error)
{
	// get_coord(control_panel, element_info[1]);
	// get_vector(control_panel, element_info[2]);
	get_coord(&control_panel->cylinder->coord, element_info[1]);
	get_vector(&control_panel->cylinder->vector, element_info[2]);
	get_d(&control_panel->cylinder->d, element_info[3]);
	get_radius(&control_panel->cylinder->radius, element_info[4]);
	get_height(&control_panel->cylinder->height, element_info[5]);
	if (!get_rgb(&control_panel->cylinder->rgb, element_info[6]))
		return (false);
	control_panel->cylinder->next = NULL;
	control_panel->cylinder->prev = NULL;
	return (true);
}

//	Filters elements by identifier and takes it into the right parsing mode
bool	parse_element_type(t_control_panel *control_panel, char **element_info)
{
	bool	error_flag;
	size_t	element_type_len;

	error_flag = false;
	element_type_len = ft_strlen(element_info[0]);
	if (ft_strncmp(element_info[0], "A", element_type_len) == 0)
		parse_amb_light(control_panel, element_info, &error_flag);
	else if (ft_strncmp(element_info[0], "C", element_type_len) == 0)
		parse_camera(control_panel, element_info, &error_flag);
	else if (ft_strncmp(element_info[0], "L", element_type_len) == 0)
		parse_light(control_panel, element_info, &error_flag);
	else if (ft_strncmp(element_info[0], "sp", element_type_len) == 0)
		parse_sphere(control_panel, element_info, &error_flag);
	else if (ft_strncmp(element_info[0], "pl", element_type_len) == 0)
		parse_plane(control_panel, element_info, &error_flag);
	else if (ft_strncmp(element_info[0], "cy", element_type_len) == 0)
		parse_cylinder(control_panel, element_info, &error_flag);
	else if (ft_strncmp(element_info[0], "#", element_type_len) == 0) // REMOVE WHEN DELIVERING {?}
		return (true);
	else
		return (false);
	if (error_flag == true)
		return (false);
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
		return (free(new_line), NULL);
	free(new_line);
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
		element_info = get_element_info(new_line);
		if (!element_info)
			return (close(fd), false);
		if (element_info[0][0] == '\0'
			|| parse_element_type(control_panel, element_info) == false)
			return (ft_free_double_array(element_info), false);
		ft_free_double_array(element_info);
	}
	close(fd);
	// printf("%d\n", control_panel->amb_light.rgb.r);
	// printf("%d\n", control_panel->amb_light.rgb.g);
	// printf("%d\n", control_panel->amb_light.rgb.b);
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
