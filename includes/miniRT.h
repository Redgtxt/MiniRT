/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/06/03 18:38:02 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../Library/ft_printf/ft_printf.h"
# include "../Library/get_next_line/get_next_line.h"
# include "../Library/libft/libft.h"
# include "../Library/minilibx-linux/mlx.h"
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
#include "vec3.h"
# define WINDOW_HEIGHT 360
# define WINDOW_WIDTH  640	
# define KEY_ESC 65307


typedef unsigned char	mini_int;
typedef double			cord;
typedef float			vec3;

#define TRANS 0
#define RED 1
#define	GREEN 2
#define BLUE 3
 


typedef struct s_mlx
{
    void    *mlx;           
    void    *win;           
    void    *img;          
    char    *addr;          
    int     bits_per_pixel; 
    int     line_length;   
    int     endian;        
    int     width;         
    int     height;  
} t_mlx;


typedef struct s_rgb
{
	
	float			RGB[4];
}						t_rgb;

typedef struct s_ray
{
	cord				origin[3];

	double				direction[3];

	//	struct s_ray *next;
	//	struct s_ray *prev;
}						t_ray;

typedef struct s_amb_light
{
	float				light_force;

	t_rgb				rgb;

}						t_amb_light;

typedef struct s_camera
{
	cord				cords[3];

	vec3				vec3[3];

	mini_int			fov;
}						t_camera;

typedef struct s_light
{
	cord				cords[3];
	float				brightness;
	t_rgb rgb; // nao e usado no mandatory

}						t_light;

typedef struct s_sphere
{
	// coordenadas do centro da esfera

	cord				cords[3];

	/*Diametro da Espera
	(E passado no subject)
	*/
	double				d;

	// Acho que e fixe ter para calculos (vamos ter de o calcular)
	double				radius;

	t_rgb				rgb;

	struct s_sphere		*next;
	struct s_sphere		*prev;

}						t_sphere;

typedef struct s_plane
{
	//    PODE NAO SER O CENTRO (PELOS VISTOS PLANOS SAO INFINITOS)

	cord				cords[3];

	vec3				vector[3];

	t_rgb				rgb;

	struct s_plane		*prev;
	struct s_plane		*next;

}						t_plane;

typedef struct s_cylinder
{
	//     coordenadas do centro do CILINDRO

	cord				cords[3];
	vec3				vector[3];

	/*
	Diametro do CILINDRO(E passado no subject)
	*/
	double				d;

	// Acho que e fixe ter para calculos (vamos ter de o calcular)
	double				radius;

	double				height;

	t_rgb				rgb;

	struct s_cylinder	*next;
	struct s_cylinder	*prev;

}						t_cylinder;

typedef struct s_control_panel
{
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
	t_amb_light			amb_light;
	t_camera			camera;
	t_light				light;
}						t_control_panel;

typedef struct s_hit_record
{
	double	position[3];
	double	normal[3];
	double	t;
}			t_hit_record;


typedef struct s_scene_objects {
    t_sphere    *spheres;      // Array de esferas
    int         sphere_count;  // Número de esferas
	//t_plane     *planes;       
	//int         plane_count;   
	//t_cylinder  *cylinders;    
	//int         cylinder_count; 
} t_scene_objects;


// MLX
void    my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int	close_window(t_mlx *mlx_data);
int	key_hook(int keycode, t_mlx *mlx_data);
void	game_hooks(t_mlx *mlx_data);
/*Ray functions*/
void init_ray(t_ray *ray);
void create_ray(t_ray *ray, const double origin[3], const double direction[3]);
void ray_origin(const t_ray *ray, double out[3]);
void ray_direction(const t_ray *ray, double out[3]);
void ray_at(double t, t_ray ray, double result[3]);

/*	sphere	*/

#endif
