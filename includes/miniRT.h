/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/06/06 13:39:57 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../Library/ft_printf/ft_printf.h"
# include "../Library/get_next_line/get_next_line.h"
# include "../Library/libft/libft.h"
# include "../Library/minilibx-linux/mlx.h"
# include "miniRT_error_p.h"
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include "vec3.h"
# include <float.h>
# include <unistd.h>


#define PI 3.1415926535897932385
#define D_INFINITY ((double)INFINITY)

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

typedef struct s_data
{
	size_t		amb_light_count;
	size_t		camera_count;
	size_t		light_count;
	size_t		sphere_count;
	size_t		plane_count;
	size_t		cylinder_count;
}				t_data;

typedef struct s_rgb
{
	float			r;
	float			g;
	float			b;
}						t_rgb;


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
	t_rgb				rgb; // nao e usado no mandatory
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
	struct s_sphere		*prev;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_plane
{
	//    PODE NAO SER O CENTRO (PELOS VISTOS PLANOS SAO INFINITOS)

	cord				cords[3];

	vec3				vec3[3];

	t_rgb				rgb;
	struct s_plane		*prev;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	//     coordenadas do centro do CILINDRO

	cord				cords[3];
	vec3				vec3[3];

	/*
	Diametro do CILINDRO(E passado no subject)
	*/
	double				d;
	// Acho que e fixe ter para calculos (vamos ter de o calcular)
	double				radius;
	double				height;
	t_rgb				rgb;
	struct s_cylinder	*prev;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_control_panel
{
	t_amb_light			amb_light;
	t_camera			camera;
	t_light				light;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
	t_data				data;
	t_error_log			error_log;
}						t_control_panel;

typedef struct s_ray
{
	cord				origin[3];

	double				direction[3];

}						t_ray;

typedef struct s_hit_record
{
	double	position[3];
	double	normal[3];
	double	t;
	bool	front_face;
}			t_hit_record;



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
void ray_color(t_control_panel *control_panel, const t_ray *ray, double out_color[3]);
void	vec3_normalize(double out[3], const double v[3]);
		/*	sphere	*/

	/*	Init	Sphere array	*/
bool    linked_list_to_sphere_array(t_sphere **sphere_list, int size_array);

	/*Sphere Collision*/
bool hit_spheres(t_control_panel *scene, const t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *record);
bool hit_world(t_control_panel *scene, const t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *record);
double degrees_to_radians(double degrees);

























//	Parsing.c
bool	parsing(t_control_panel *control_panel, char *file_name);

//	Parse_elements.c
bool	parse_amb_light(t_control_panel *control_panel, char **element_info, t_error_log *error_log);
bool	parse_camera(t_control_panel *control_panel, char **element_info, t_error_log *error_log);
bool	parse_light(t_control_panel *control_panel, char **element_info, t_error_log *error_log);

//	Parse_objects.c
bool	parse_sphere(t_control_panel *control_panel, char **element_info, t_error_log *error_log);
bool	parse_plane(t_control_panel *control_panel, char **element_info, t_error_log *error_log);
bool	parse_cylinder(t_control_panel *control_panel, char **element_info, t_error_log *error_log);

//	Parse_values_1.c
bool	get_coord(cord *coord, char *info, t_error_log *error_log);
bool	get_vector(vec3 *vector, char *info, t_error_log *error_log);
bool	get_rgb(t_rgb *rgb, char *info, t_error_log *error_log);

//	Parse_values_2.c
bool	get_fov(mini_int *fov, char *info, t_error_log *error_log);
bool	get_light_force(float *light_force, char *info, t_error_log *error_log);
bool	get_brightness(float *brightness, char *info, t_error_log *error_log);
bool	get_d(double *d, char *info, t_error_log *error_log);
bool	get_height(double *height, char *info, t_error_log *error_log);

//	List_handler.c
void	lstadd_last_sphere(t_control_panel *control_panel, t_sphere *new_sphere);
void	lstadd_last_plane(t_control_panel *control_panel, t_plane *new_plane);
void	lstadd_last_cylinder(t_control_panel *control_panel, t_cylinder *new_cylinder);

//	Free.c
void	free_sphere(t_sphere *sphere);
void	free_plane(t_plane *plane);
void	free_cylinder(t_cylinder *cylinder);
void	free_control_panel(t_control_panel *control_panel);

//	Utils.c
size_t	double_array_len(char **array);
bool	ft_atoc(const char *str, mini_int *dest);
bool	ft_atofd(const char *str, void *dest, char type);
char	**split_spaces(char const *s);

//	Extra -> Tests
void	print_elements(t_control_panel *control_panel);

#endif
