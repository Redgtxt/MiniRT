/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:45:35 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/12 18:50:35 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void get_uv_sphere(t_hit_record *rec, t_sphere *sphere)
{
    double p[3];
    double out[3];

    vec3_zero(p);
    vec3_zero(out);
    vec3_sub(out, rec->position, sphere->cords);
    vec3_normalize(p, out);
    rec->u = 0.5 - atan2(p[2], p[0]) / (2 * PI);
    rec->v = 0.5 - asin(p[1]) / PI;
}

void get_uv_plane(t_hit_record *rec, t_plane *plane)
{
    double local[3];
    double right[3];
    double up[3];
    double temp[3];

    vec3_sub(local, rec->position, plane->cords);
    
    if (fabs(plane->vec3[0]) > 0.9)
    {
        vec3_set(temp, 0, 1, 0);
    }
    else
    {
        vec3_set(temp, 1, 0, 0);
    }
    
    vec3_cross(right, plane->vec3, temp);
    vec3_normalize(right, right);
    vec3_cross(up, right, plane->vec3);
    vec3_normalize(up, up);
    
    rec->u = vec3_dot(local, right);
    rec->v = vec3_dot(local, up);
    rec->u = rec->u - floor(rec->u);
    rec->v = rec->v - floor(rec->v);
}

void get_uv_cylinder(t_hit_record *rec, t_cylinder *cylinder)
{
    double local[3];
    double p[3];
    double axis_dist;

    vec3_sub(local, rec->position, cylinder->cords);
    axis_dist = vec3_dot(local, cylinder->vec3);
    
    vec3_scale(p, cylinder->vec3, axis_dist);
    vec3_sub(p, local, p);
    vec3_normalize(p, p);
    
    rec->u = 0.5 - atan2(p[2], p[0]) / (2 * PI);
    rec->v = (axis_dist / cylinder->height + 0.5);
    rec->v = rec->v - floor(rec->v);
}

void get_uv_cone(t_hit_record *rec, t_cone *cone)
{
    double local[3];
    double p[3];
    double axis_dist;

    vec3_sub(local, rec->position, cone->cords);
    axis_dist = vec3_dot(local, cone->vec3);
    
    vec3_scale(p, cone->vec3, axis_dist);
    vec3_sub(p, local, p);
    vec3_normalize(p, p);
    
    rec->u = 0.5 - atan2(p[2], p[0]) / (2 * PI);
    rec->v = (axis_dist / cone->height + 0.5);
    rec->v = rec->v - floor(rec->v);
}
