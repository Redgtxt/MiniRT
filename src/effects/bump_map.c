/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:40:00 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/10 15:54:46 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static double get_pixel_intensity(t_texture *texture, int x, int y)
{
    int index;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    double intensity;

    if (!texture || !texture->data)
        return (0.0);
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0.0);
    index = y * texture->line_length + x * (texture->bpp / 8);
    b = texture->data[index];
    g = texture->data[index + 1];
    r = texture->data[index + 2];
    intensity = (r + g + b) / (3.0 * 255.0);
    return (intensity);
}

void apply_bump_map(t_control_panel *cp, t_hit_record *rec)
{
    t_texture *texture;
    int x;
    int y;
    double height;
    double height_u;
    double height_v;
    double tangent[3];
    double bitangent[3];
    double new_normal[3];

    if (!rec->material || !rec->material->has_bump)
        return;
    texture = get_texture_by_id(cp, rec->material->bump_texture_id);
    if (!texture)
        return;
    x = (int)(rec->u * texture->width) % texture->width;
    y = (int)(rec->v * texture->height) % texture->height;
    if (x < 0)
        x += texture->width;
    if (y < 0)
        y += texture->height;
    height = get_pixel_intensity(texture, x, y);
    height_u = get_pixel_intensity(texture, (x + 1) % texture->width, y);
    height_v = get_pixel_intensity(texture, x, (y + 1) % texture->height);
    vec3_set(tangent, 1.0, 0.0, (height_u - height) * rec->material->bump_strength * 10.0);
    vec3_set(bitangent, 0.0, 1.0, (height_v - height) * rec->material->bump_strength * 10.0);
    vec3_cross(new_normal, tangent, bitangent);
    vec3_normalize(new_normal, new_normal);
    vec3_add(rec->normal, rec->normal, new_normal);
    vec3_scale(rec->normal, rec->normal, 0.5);
    vec3_normalize(rec->normal, rec->normal);
}
