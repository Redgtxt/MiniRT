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

typedef unsigned char			t_mini_int;
typedef double					t_vec3;

/* Forward declarations */
typedef struct s_cp				t_control_panel;
typedef struct s_mt				t_material;
typedef struct s_mlx			t_mlx;
typedef struct s_ray			t_ray;
typedef struct s_light			t_light;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_cylinder		t_cylinder;
typedef struct s_cone			t_cone;
typedef struct s_hit_record		t_hit_record;
typedef struct s_win_config		t_win_config;
typedef struct s_error_log		t_error_log;
typedef struct s_texture		t_texture;
typedef struct s_texture_node	t_texture_node;

/* Basic coordinate structure */
typedef struct s_coord
{
	int							x;
	int							y;
}								t_coord;

/* Material types enumeration */
typedef enum e_mt_t
{
	LAMBERTIAN,
	METAL,
	CHECKERPATTERN,
	GLASS,
	SOLID
}								t_material_type;

/* Data counting structure */
typedef struct s_data
{
	size_t						amb_light_count;
	size_t						camera_count;
	size_t						light_count;
	size_t						sphere_count;
	size_t						plane_count;
	size_t						cylinder_count;
	size_t						cone_count;
	size_t						texture_count;
	int							obj_type;
	int							idx_obj;
}								t_data;

/* Texture structure for bump maps */
typedef struct s_texture
{
	int							id;
	char						*filepath;
	void						*mlx_img;
	unsigned char				*data;
	int							width;
	int							height;
	int							bpp;
	int							line_length;
	int							endian;
}								t_texture;

typedef struct s_texture_node
{
	t_texture					*texture;
	struct s_texture_node		*next;
}								t_texture_node;

#endif