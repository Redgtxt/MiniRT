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

t_coord	get_coord(char *info)
{
	(void)info;
}

t_vector	get_vector(char *info)
{
	(void)info;
}

t_rgb	get_rgb(char *info)
{
	(void)info;
}

mini_int	get_fov(char *info)
{
	(void)info;
}

float	get_light_force(char *info)
{
	(void)info;
}

double	get_d(char *info)
{
	(void)info;
}

double	get_radius(char *info)
{
	(void)info;
}

bool	parse_amb_light(t_control_panel *control_panel, char **element_info)
{
	control_panel->amb_light.light_force = get_light_force(element_info[1]);
	control_panel->amb_light.rgb = get_rgb(element_info[2]);
	return (true);
}

bool	parse_camera(t_control_panel *control_panel, char **element_info)
{
	control_panel->camera.coord = get_coord(element_info[1]);
	control_panel->camera.vector = get_vector(element_info[2]);
	control_panel->camera.fov = get_fov(element_info[3]);
	return (true);
}

bool	parse_light(t_control_panel *control_panel, char **element_info)
{
	control_panel->light.coord = get_coord(element_info[1]);
	control_panel->light.brightness = get_brightness(element_info[2]);
	control_panel->light.rgb = get_rgb(element_info[3]);
	return (true);
}

bool	parse_sphere(t_control_panel *control_panel, char **element_info)
{
	control_panel->sphere->coord = get_coord(element_info[1]);
	control_panel->sphere->d = get_d(element_info[2]);
	control_panel->sphere->radius = get_radius(element_info[3]);
	control_panel->sphere->rgb = get_rgb(element_info[4]);
	control_panel->sphere->next = NULL;
	control_panel->sphere->prev = NULL;
	return (true);
}

bool	parse_element_type(t_control_panel *control_panel, char **element_info)
{
	if (ft_strncmp(element_info[0], "A", ft_strlen(element_info[0])) == 0)
		parse_amb_light(control_panel, element_info);
	else if (ft_strncmp(element_info[0], "C", ft_strlen(element_info[0])) == 0)
		parse_camera(control_panel, element_info);
	else if (ft_strncmp(element_info[0], "L", ft_strlen(element_info[0])) == 0)
		parse_light(control_panel, element_info);
	else if (ft_strncmp(element_info[0], "sp", ft_strlen(element_info[0])) == 0)
		parse_sphere(control_panel, element_info);
	else if (ft_strncmp(element_info[0], "pl", ft_strlen(element_info[0])) == 0)
		parse_plane(control_panel, element_info);
	else if (ft_strncmp(element_info[0], "cy", ft_strlen(element_info[0])) == 0)
		parse_cylinder(control_panel, element_info);
	else if (ft_strncmp(element_info[0], "#", ft_strlen(element_info[0])) == 0) // REMOVE WHEN DELIVERING {?}
		return (true);
	else
		return (false);
	return (true);
}

bool	parsing(t_control_panel *control_panel, char *file_name)
{
	int		fd;
	char	*element;
	char	**element_info;

	fd = open(file_name, O_RDONLY);
	if (fd == -1) 
		return (false);
	while (1)
	{
		element = get_next_line(fd);
		if (!element)
			break ;
		element_info = split_spaces(element);
		if (!element_info)
		{
			free(element);
			close(fd);
			return (false);
		}
		if (parse_element_type(control_panel, element_info) == false)
		{
			ft_free_double_array(element_info);
			free(element);
			return (false);
		}
		ft_free_double_array(element_info);
		free(element);
	}
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