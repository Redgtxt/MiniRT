/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:01:17 by hguerrei          #+#    #+#             */
/*   Updated: 2025/10/01 13:34:38 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/// @brief Will store the values of the ray
/// @param cords
/// @param vector3
/// @return
void	init_ray(t_ray *ray)
{
    ray->origin[0] = 0;
    ray->origin[1] = 0;
    ray->origin[2] = 0;

    ray->direction[0] = 0;
    ray->direction[1] = 1;
    ray->direction[2] = 0;
}

// vou dar a informacao para criar um novo raio
/// @brief Create a ray with specific origin and direction
//(constructor with parameters)
/// @param ray pointer to ray structure
/// @param origin origin point coordinates
/// @param direction direction vector
void	create_ray(t_ray *ray, const double origin[3],
				const double direction[3])
{
    vec3_copy(ray->origin, origin);
    vec3_copy(ray->direction, direction);
}

/// @brief Get ray origin (equivalent to origin() method)
/// @param ray pointer to ray structure
/// @param out output array to store origin
void	ray_origin(const t_ray *ray, double out[3])
{
    vec3_copy(out, ray->origin);
}

/// @brief Get ray direction (equivalent to direction() method)
/// @param ray pointer to ray structure
/// @param out output array to store direction
void	ray_direction(const t_ray *ray, double out[3])
{
    vec3_copy(out, ray->direction);
}
