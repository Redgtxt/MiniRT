/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:20:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/10 15:54:46 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static bool validate_texture_id(char *id_str, int *id, t_error_log *error_log)
{
    int i;

    i = 0;
    if (!id_str || !id_str[0])
        return (error_code(&error_log->code_error, ERR_INV_VALUE, 0), false);
    while (id_str[i])
    {
        if (!ft_isdigit(id_str[i]))
            return (error_code(&error_log->code_error, ERR_INV_VALUE, 0),
                    false);
        i++;
    }
    *id = ft_atoi(id_str);
    if (*id < 0)
        return (error_code(&error_log->code_error, ERR_INV_VALUE, 0), false);
    return (true);
}

static bool validate_texture_file(char *filepath, t_error_log *error_log)
{
    size_t len;
    int fd;

    if (!filepath || !filepath[0])
        return (error_code(&error_log->code_error, ERR_INV_VALUE, 0), false);
    len = ft_strlen(filepath);
    if (len < 5 || ft_strncmp(&filepath[len - 4], ".xpm", 4) != 0)
        return (error_code(&error_log->code_error, ERR_FILE_NAME, 0), false);
    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return (error_code(&error_log->code_error, ERR_FILE_OPEN, 0), false);
    close(fd);
    return (true);
}

typedef struct s_texture_node
{
    t_texture *texture;
    struct s_texture_node *next;
} t_texture_node;

static bool add_texture_to_list(t_control_panel *cp, int id, char *filepath)
{
    t_texture_node *new_node;
    t_texture_node *current;
    t_texture *texture;

    texture = ft_calloc(1, sizeof(t_texture));
    if (!texture)
        return (false);
    texture->id = id;
    texture->filepath = ft_strdup(filepath);
    if (!texture->filepath)
        return (free(texture), false);
    new_node = ft_calloc(1, sizeof(t_texture_node));
    if (!new_node)
        return (free(texture->filepath), free(texture), false);
    new_node->texture = texture;
    new_node->next = NULL;
    if (!cp->texture_list)
        cp->texture_list = new_node;
    else
    {
        current = (t_texture_node *)cp->texture_list;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
    cp->data.texture_count++;
    return (true);
}

bool parse_texture(t_control_panel *cp, char **element_info,
                   t_error_log *error_log)
{
    int id;

    if (double_array_len(element_info) != 3)
        return (error_code(&error_log->code_error, ERR_NBR_VAL, 0), false);
    if (!validate_texture_id(element_info[1], &id, error_log))
        return (false);
    if (!validate_texture_file(element_info[2], error_log))
        return (false);
    if (!add_texture_to_list(cp, id, element_info[2]))
        return (error_code(&error_log->code_error, ERR_MALLOC, 0), false);
    return (true);
}
