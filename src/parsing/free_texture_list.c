/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:00:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/12 18:00:01 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	free_texture_list(void **texture_list)
{
	t_texture_node	*current;
	t_texture_node	*next;
	t_texture		*texture;

	if (!texture_list || !*texture_list)
		return ;
	current = (t_texture_node *)*texture_list;
	while (current)
	{
		next = current->next;
		texture = current->texture;
		if (texture)
		{
			if (texture->filepath)
				free(texture->filepath);
			free(texture);
		}
		free(current);
		current = next;
	}
	*texture_list = NULL;
}
