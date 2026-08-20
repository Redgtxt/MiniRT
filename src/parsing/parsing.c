/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:18 by randrade          #+#    #+#             */
/*   Updated: 2025/09/18 16:18:28 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static bool	parse_element(t_control_panel *control_panel, char **element_info)
{
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
	else if (ft_strncmp(element_info[0], "cn", 2) == 0)
		parse_cone(control_panel, element_info, &control_panel->error_log);
	else if (ft_strncmp(element_info[0], "#", 1) == 0)
		return (true);
	else
	{
		control_panel->error_log.element = ft_strdup(element_info[0]);
		error_code(&control_panel->error_log.code_error, INV_ELEM, 0);
	}
	if (control_panel->error_log.code_error != 0)
		return (false);
	return (true);
}

static char	**get_element_info(char *new_line)
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

static bool	parse_new_line(t_control_panel *control_panel, char *new_line)
{
	char	**element_info;

	element_info = NULL;
	element_info = get_element_info(new_line);
	if (!element_info)
		return (false);
	if (parse_element(control_panel, element_info) == false)
		return (ft_free_double_array(element_info), false);
	ft_free_double_array(element_info);
	return (true);
}

int	parse_file_name(char *file_name, t_error_log *error_log)
{
	int		fd;
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 3 || ft_strncmp(&file_name[len - 3], ".rt", 3) != 0)
		return (error_code(&error_log->code_error, ERR_FILE_NAME, 0), -1);
	fd = open (file_name, O_RDONLY | O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (error_code(&error_log->code_error, ERR_IS_DIR, 0), -1);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (error_code(&error_log->code_error, ERR_FILE_OPEN, 0), -1);
	return (fd);
}

bool	parsing(t_control_panel *cp, char *file_name)
{
	int		fd;
	char	*new_line;

	new_line = NULL;
	fd = parse_file_name(file_name, &cp->error_log);
	if (fd == -1)
		return (error_code(&cp->error_log.code_error, ERR_FILE, 0), false);
	while (1)
	{
		new_line = get_next_line(fd);
		if (!new_line)
			break ;
		cp->error_log.line_nbr++;
		if (new_line[0] != '\n')
		{
			if (!parse_new_line(cp, new_line))
				return (close(fd), free(new_line), false);
		}
		free(new_line);
	}
	close(fd);
	if (!parse_number_elements(cp->data, &cp->error_log))
		return (false);
	ft_memset(&cp->error_log, 0, sizeof(t_error_log));
	return (true);
}
