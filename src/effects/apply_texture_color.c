/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:00:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/10 15:54:46 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void apply_texture_color(t_control_panel *cp, t_hit_record *rec,
                         double color[3])
{
    t_texture *texture;
    int x;
    int y;
    int index;
    unsigned char r;
    unsigned char g;
    unsigned char b;

    if (!rec->material || !rec->material->has_bump)
        return;
    texture = get_texture_by_id(cp, rec->material->bump_texture_id);
    if (!texture || !texture->data)
        return;
    x = (int)(rec->u * texture->width) % texture->width;
    y = (int)(rec->v * texture->height) % texture->height;
    if (x < 0)
        x += texture->width;
    if (y < 0)
        y += texture->height;
    index = y * texture->line_length + x * (texture->bpp / 8);
    b = texture->data[index];
    g = texture->data[index + 1];
    r = texture->data[index + 2];
    color[0] = r / 255.0;
    color[1] = g / 255.0;
    color[2] = b / 255.0;
}
