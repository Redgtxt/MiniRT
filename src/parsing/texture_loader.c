/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:30:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/13 11:17:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static bool	load_texture_image(t_control_panel *cp, t_texture *texture)
{
	texture->mlx_img = mlx_xpm_file_to_image(cp->mlx->mlx, texture->filepath,
			&texture->width, &texture->height);
	if (!texture->mlx_img)
		return (false);
	texture->data = (unsigned char *)mlx_get_data_addr(texture->mlx_img,
			&texture->bpp, &texture->line_length, &texture->endian);
	if (!texture->data)
	{
		mlx_destroy_image(cp->mlx->mlx, texture->mlx_img);
		texture->mlx_img = NULL;
		return (false);
	}
	return (true);
}

static bool	init_texture_values(t_texture *tx_ref, t_texture *texture)
{
	texture->id = tx_ref->id;
	texture->filepath = ft_strdup(tx_ref->filepath);
	texture->mlx_img = NULL;
	texture->data = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bpp = 0;
	texture->line_length = 0;
	texture->endian = 0;
	if (!texture->filepath)
		return (false);
	return (true);
}

static bool	convert_texture_list_to_array(t_control_panel *cp)
{
	t_texture_node	*current;
	t_texture		*texture;
	size_t			i;

	if (cp->data.texture_count == 0)
		return (true);
	cp->textures = ft_calloc(cp->data.texture_count, sizeof(t_texture));
	if (!cp->textures)
		return (false);
	current = (t_texture_node *)cp->texture_list;
	i = -1;
	while (current && ++i < cp->data.texture_count)
	{
		texture = current->texture;
		if (!init_texture_values(texture, &cp->textures[i]))
			return (false);
		if (!load_texture_image(cp, &cp->textures[i]))
		{
			ft_printf("Error: Failed to load texture: %s\n",
				cp->textures[i].filepath);
			return (false);
		}
		current = current->next;
	}
	return (true);
}

bool	load_all_textures(t_control_panel *cp)
{
	if (!convert_texture_list_to_array(cp))
		return (false);
	if (cp->texture_list)
	{
		free_texture_list(&cp->texture_list);
		cp->texture_list = NULL;
	}
	return (true);
}

t_texture	*get_texture_by_id(t_control_panel *cp, int id)
{
	size_t	i;

	if (!cp->textures || id < 0)
		return (NULL);
	i = 0;
	while (i < cp->data.texture_count)
	{
		if (cp->textures[i].id == id)
			return (&cp->textures[i]);
		i++;
	}
	return (NULL);
}
