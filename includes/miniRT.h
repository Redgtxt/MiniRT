/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/05/27 16:11:15 by randrade         ###   ########.fr       */
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
# include <float.h>
# include <unistd.h>

# define WINDOW_HEIGHT 800
# define WINDOW_WIDTH 600

typedef unsigned char	mini_int;
// typedef double			coord;
// typedef float			vector;

typedef struct s_data
{
	size_t		amb_light;
	size_t		camera;
	size_t		light;
	size_t		sphere;
	size_t		plane;
	size_t		cylinder;
}				t_data;

typedef struct s_coord
{
	double				x;
	double				y;
	double				z;
}						t_coord;

typedef struct s_vector
{
	float				x;
	float				y;
	float				z;
}						t_vector;

typedef struct s_rgb
{
	mini_int			r;
	mini_int			g;
	mini_int			b;
}						t_rgb;

typedef struct s_amb_light
{
	float				light_force;
	t_rgb				rgb;
}						t_amb_light;

typedef struct s_camera
{
	t_coord				coord;
	t_vector			vector;
	mini_int			fov;
}						t_camera;

typedef struct s_light
{
	t_coord				coord;
	float				brightness;
	t_rgb				rgb; // nao e usado no mandatory
}						t_light;

typedef struct s_sphere
{
	// coordenadas do centro da esfera
	t_coord				coord;
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
	t_coord				coord;
	t_vector				vector;
	t_rgb				rgb;
	struct s_plane		*prev;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	//     coordenadas do centro do CILINDRO
	t_coord				coord;
	t_vector			vector;
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


//	Parsing.c
bool	parsing(t_control_panel *control_panel, char *file_name);

//	Utils.c
size_t	double_array_len(char **array);
bool	ft_atoc(const char *str, mini_int *dest);
bool	ft_atofd(const char *str, void *dest, char type);
char	**split_spaces(char const *s);

//	Extra -> Tests
void	print_elements(t_control_panel *control_panel);

#endif
