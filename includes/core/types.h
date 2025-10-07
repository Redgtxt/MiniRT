/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <stdint.h>

typedef unsigned char	mini_int;
typedef double			vec3;

/* Forward declarations */
typedef struct s_cp			t_control_panel;
typedef struct s_mt			t_material;
typedef struct s_mlx		t_mlx;
typedef struct s_ray		t_ray;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_cone		t_cone;
typedef struct s_hit_record	t_hit_record;
typedef struct s_win_config	t_win_config;
typedef struct s_error_log	t_error_log;

/* Basic coordinate structure */
typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

/* Material types enumeration */
typedef enum e_mt_t
{
	LAMBERTIAN,
	METAL,
	CHECKERPATTERN,
	GLASS,
	SOLID
}	t_material_type;

/* Data counting structure */
typedef struct s_data
{
	size_t	amb_light_count;
	size_t	camera_count;
	size_t	light_count;
	size_t	sphere_count;
	size_t	plane_count;
	size_t	cylinder_count;
	size_t	cone_count;
	int		obj_type;
	int		idx_obj;
}	t_data;

#endif